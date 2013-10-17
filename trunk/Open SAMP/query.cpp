#include "main.h"

// #define _USE_BITSTREAMS

uint32_t lastQueryTick = 0;
uint32_t lastBinAddr = 0;

bool bRconReply;
uint16_t RconUser = INVALID_PLAYER_ID;

void RconReply(in_addr clientAddr, SOCKET clientSocket, char* clientData, int clientDataLen, char* reply)
{
	if (bRconReply)
	{
		char* replyData = new char[clientDataLen + sizeof(uint8_t) + strlen(reply)];
		char* replyDataPtr = replyData;

		memcpy(replyDataPtr, clientData, clientDataLen);
		replyData += clientDataLen;
		*(uint16_t*)replyData = strlen(reply);
		replyData += sizeof(uint16_t);
		memcpy(replyData, reply, strlen(reply));
		replyData += strlen(reply);
		sendto(clientSocket, replyDataPtr, (int)(replyData - replyDataPtr), 0, (sockaddr*)&clientAddr, sizeof(clientAddr));
		
		delete [] replyData;
	}
}

bool FloodCheck(uint32_t binAddr)
{
	uint32_t currentTick = __NetGame->GetTime();
	if(!lastQueryTick) 
	{
		lastQueryTick = currentTick;
		lastBinAddr = binAddr;
		return false;
	}

	if(lastBinAddr == binAddr)
		return false;
	if((currentTick - lastQueryTick) < 25)
		return true;

	lastQueryTick = currentTick;
	lastBinAddr = binAddr;

	return false;
}

char* DecodeStr(uint8_t key, char a, char b, char c)
{
	char buf[3];
	buf[0] = a ^ key;
	buf[1] = b ^ key;
	buf[2] = c ^ key;
	return buf;
}

//bool HandleQueryPacket(SOCKET sock, char* data, int len, in_addr clientAddr, uint16_t port)
int HandleQueryPacket(in_addr clientAddr, uint16_t port, char* data, int len, SOCKET sock)
{
#ifdef _USE_BITSTREAMS
	RakNet::BitStream bs(data, len + 1, false);
	uint32_t packetId;

	bs.Read(packetId);

	if(len > 4 && packetId == 0x504D4153)
#else
	if(len > 4 && *(uint32_t*)data == 0x504D4153)
#endif
	{
		uint32_t binAddr = clientAddr.s_addr;

		in_addr inaddr;
		inaddr.s_addr = binAddr;

		if(!__NetGame || __NetGame->gameState != 1) return false;
		
		if (len < 11) return true;

		if(__Console->GetBoolVar("logqueries"))
		   logprintf("[query:%c] from %s", data[10], inet_ntoa(clientAddr));

		sockaddr_in client;
		client.sin_family = AF_INET;
		client.sin_port = htons(port);
		client.sin_addr.s_addr = binAddr;

		if(data[10] == 'p')
		{
			if(len == 15) 
			{
				/*
				uint8_t decKey = data[11];
				char* str = DecodeStr(decKey, data[12], data[13], data[14]);
				if(!strcmp(str, "SAM")) strncpy((char*)data[11], "OPEN", 4);
				*/

				if(*(uint32_t*)(&data[11]) == 0x504D4153) strncpy((char*)&data[11], "OPEN", 4);
				sendto(sock, data, 15, 0, (sockaddr*)&client, sizeof(client));
			}
		}
		else if(data[10] == 'i')
		{
			if(!__Console->GetBoolVar("query")) return true;
			if(FloodCheck(binAddr)) return true;

			char* svrHostname = __Console->GetStringVar("hostname");
			uint32_t svrHostnameLen = strlen(svrHostname);
			if (svrHostnameLen > 50) svrHostnameLen = 50;

			char* svrGamemode = __Console->GetStringVar("gamemodetext");
			uint32_t svrGamemodeLen = strlen(svrGamemode);
			if (svrGamemodeLen > 30) svrGamemodeLen = 30;
			
			char* svrMapname = __Console->GetStringVar("mapname");
			uint32_t svrMapnameLen = strlen(svrMapname);
			if (svrMapnameLen > 30) svrMapnameLen = 30;

			uint16_t svrPlayerCount = 0;
			CPlayerPool* playerPool = __NetGame->playerPool;
			if (playerPool)
				svrPlayerCount = (uint16_t)playerPool->playersCount;
			else
				return true;

			uint16_t npcCount = 0;
			for(uint16_t i = 0; i < MAX_PLAYERS; i++)
				if(playerPool->GetSlotState(i) && playerPool->bIsNPC[i]) npcCount++;


			uint16_t svrMaxPlayers = __Console->GetIntVar("maxplayers") - npcCount;
			uint8_t svrHasPassword = __Console->GetStringVar("password")[0] != NULL;

			uint32_t responseLen = 28 + svrHostnameLen + svrGamemodeLen + svrMapnameLen;
#ifdef _USE_BITSTREAMS
			RakNet::BitStream bs;
#else

			char* responseData = new char[responseLen];
			char* responsePtr = responseData;

			memcpy(responseData, data, 11);
			responseData += 11;
#endif
#ifdef _USE_BITSTREAMS
			bs.Write(data, 11);
#else

			memcpy(responseData, &svrHasPassword, sizeof(uint8_t));
			responseData += sizeof(uint8_t);

			memcpy(responseData, &svrPlayerCount, sizeof(uint16_t));
			responseData += sizeof(uint16_t);

			memcpy(responseData, &svrMaxPlayers, sizeof(uint16_t));
			responseData += sizeof(uint16_t);
#endif
#ifdef _USE_BITSTREAMS
			bs.Write(svrHasPassword);
			bs.Write(svrPlayerCount);
			bs.Write(svrMaxPlayers);
#else
			memcpy(responseData, &svrHostnameLen, sizeof(uint32_t));
			responseData += sizeof(uint32_t);
			memcpy(responseData, svrHostname, svrHostnameLen);
			responseData += svrHostnameLen;

			memcpy(responseData, &svrGamemodeLen, sizeof(uint32_t));
			responseData += sizeof(uint32_t);
			memcpy(responseData, svrGamemode, svrGamemodeLen);
			responseData += svrGamemodeLen;

			memcpy(responseData, &svrMapnameLen, sizeof(uint32_t));
			responseData += sizeof(uint32_t);
			memcpy(responseData, svrMapname, svrMapnameLen);
			responseData += svrMapnameLen;
#endif
#ifdef _USE_BITSTREAMS
			bs.Write(svrHostnameLen);
			bs.Write(svrHostname, svrHostnameLen);
			bs.Write(svrGamemodeLen);
			bs.Write(svrGamemode, svrGamemodeLen);
			bs.Write(svrMapnameLen);
			bs.Write(svrMapname, svrMapnameLen);
			sendto(sock, (char*)bs.GetData(), bs.GetNumberOfBytesUsed(), 0, (sockaddr*)&client, sizeof(client));
#else
			sendto(sock, responsePtr, responseLen, 0, (sockaddr*)&client, sizeof(client));
			delete [] responsePtr;
#endif
		}
		else if(data[10] == 'c')
		{
			if(!__Console->GetBoolVar("query")) return true;
			if(FloodCheck(binAddr)) return true;

			_PlayerID svrPlayerCount = 0;
			CPlayerPool* playerPool = __NetGame->playerPool;
			if (playerPool)
				svrPlayerCount = ( _PlayerID )( playerPool->playersCount );
			else
				return true;

			if(svrPlayerCount > 100) return true;
#ifdef _USE_BITSTREAMS
			RakNet::BitStream bs;
#else
			char* responseData = new char[13 + (svrPlayerCount * (MAX_PLAYER_NAME + 5))];
			char* responsePtr = responseData;

			memcpy(responseData, data, 11);
			responseData += 11;
#endif
#ifdef _USE_BITSTREAMS
			bs.Write(data, 11);
#else
			memcpy(responseData, &svrPlayerCount, sizeof(uint16_t));
			responseData += sizeof(uint16_t);
#endif
#ifdef _USE_BITSTREAMS
			bs.Write(svrPlayerCount);
#endif

			if(playerPool)
			{
				char* playerName;
				uint8_t playerNameLen;
				uint32_t playerScore;

				for(uint16_t i = 0; i < MAX_PLAYERS; i++)
				{
					if(playerPool->GetSlotState(i) && !playerPool->bIsNPC[i])
					{
						playerName = playerPool->getPlayerNick(i);
						playerNameLen = strlen(playerName);
						playerScore = playerPool->getScore(i);
#ifndef _USE_BITSTREAMS
						memcpy(responseData, &playerNameLen, sizeof(uint8_t));
						responseData += sizeof(uint8_t);

						memcpy(responseData, playerName, playerNameLen);
						responseData += playerNameLen;

						memcpy(responseData, &playerScore, sizeof(uint32_t));
						responseData += sizeof(uint32_t);
#else
						bs.Write(playerNameLen);
						bs.Write(playerName, playerNameLen);
						bs.Write(playerScore);
#endif
					}
				}
			}
#ifdef _USE_BITSTREAMS
			sendto(sock, (char*)bs.GetData(), bs.GetNumberOfBytesUsed(), 0, (sockaddr*)&client, sizeof(client));
#else
			sendto(sock, responsePtr, (uint32_t)(responseData - responsePtr), 0, (sockaddr*)&client, sizeof(client));
			delete [] responsePtr;
#endif
		}
		else if(data[10] == 'd')
		{
			if(!__Console->GetBoolVar("query")) return true;
			if(FloodCheck(binAddr)) return true;

			uint16_t svrPlayerCount = 0;
			CPlayerPool* playerPool = __NetGame->playerPool;
			if (playerPool)
				svrPlayerCount = playerPool->playersCount;
			else
				return true;

			if(svrPlayerCount > 100) return true;
#ifdef _USE_BITSTREAMS
			RakNet::BitStream bs;
#else
			char* responseData = new char[13 + (svrPlayerCount * (MAX_PLAYER_NAME + 10))];
			char* responsePtr = responseData;

			memcpy(responseData, data, 11);
			responseData += 11;
#endif
#ifdef _USE_BITSTREAMS
			bs.Write(data, 11);
#else
			memcpy(responseData, &svrPlayerCount, sizeof(uint16_t));
			responseData += sizeof(uint16_t);
#endif
#ifdef _USE_BITSTREAMS
			bs.Write(svrPlayerCount);
#endif
			if(playerPool)
			{
				char* playerName;
				uint8_t playerNameLen;
				uint32_t playerScore;
				uint32_t playerPing;

				for(uint16_t i = 0; i < MAX_PLAYERS; i++)
				{
					if(playerPool->GetSlotState(i) && !playerPool->bIsNPC[i])
					{
						playerName = playerPool->getPlayerNick(i);
						playerNameLen = strlen(playerName);
						playerScore = playerPool->getScore(i);
						playerPing = __NetGame->rakServerInterface->GetLastPing(__NetGame->rakServerInterface->GetPlayerIDFromIndex(i));
#ifndef _USE_BITSTREAMS
						memcpy(responseData, &playerNameLen, sizeof(uint8_t));
						responseData += sizeof(uint8_t);

						memcpy(responseData, playerName, playerNameLen);
						responseData += playerNameLen;

						memcpy(responseData, &playerScore, sizeof(uint32_t));
						responseData += sizeof(uint32_t);

						memcpy(responseData, &playerPing, sizeof(uint32_t));
						responseData += sizeof(uint32_t);
#else
						bs.Write(playerNameLen);
						bs.Write(playerName, playerNameLen);
						bs.Write(playerScore);
						bs.Write(playerPing);
#endif
					}
				}
			}
#ifdef _USE_BITSTREAMS
			sendto(sock, (char*)bs.GetData(), bs.GetNumberOfBytesUsed(), 0, (sockaddr*)&client, sizeof(client));
#else
			sendto(sock, responsePtr, (uint32_t)(responseData - responsePtr), 0, (sockaddr*)&client, sizeof(client));
			delete [] responsePtr;
#endif
		}
		else if(data[10] == 'r')
		{
			if(!__Console->GetBoolVar("query")) return true;
			if(FloodCheck(binAddr)) return true;

			 __Console->SendRules(data, sock, &client, sizeof(client));
		}
		else if(data[10] == 'x')
		{
			if(!__Console->GetBoolVar("query")) return true;
			if(!__Console->GetBoolVar("rcon")) return true;
			if(FloodCheck(binAddr)) return true;

			if(len < 13) return true;

			uint16_t rconPassLen;
			char* rconPass;

			RakNet::BitStream bsRcon(data, strlen(data), false);

			bsRcon.SetReadOffset(11);
			bsRcon.Read(rconPassLen);

			if(rconPassLen > 100) return true;
			rconPass = new char[rconPassLen+1];
			bsRcon.Read(rconPass, rconPassLen);
			rconPass[rconPassLen] = 0;

			if (!strcmp(rconPass, __Console->GetStringVar("rcon_password")))
			{
				delete [] rconPass;

				uint16_t rconCmdLen;
				bsRcon.Read(rconCmdLen);

				if(rconCmdLen > 100) return true;

				char* rconCmd;
				rconCmd = new char[rconCmdLen+1];
				bsRcon.Read(rconCmd, rconCmdLen);
				rconCmd[rconCmdLen] = 0;
				if (__Console)
				{
					bRconReply = TRUE;
					__Console->Execute(rconCmd);
					bRconReply = FALSE;
				}

				delete [] rconCmd;
			}
			else
			{				
				delete [] rconPass;

				logprintf("BAD RCON ATTEMPT BY: %s", inet_ntoa(clientAddr));
				bRconReply = true;
				RconReply(clientAddr, sock, data, 11, "Invalid RCON password.");
				bRconReply = false;
			}
		}
		return true;
	}
	else return false;
}
