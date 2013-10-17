#include "../main.h"

CText3DLabels::CText3DLabels( )
{
	
	for( _Text3DID i = 0; i < MAX_TEXT_LABELS; i++ )
	{
		this->TextLabels[i].posX = 0.f;
		this->TextLabels[i].posY = 0.f;
		this->TextLabels[i].posZ = 0.f;
		this->TextLabels[i].virtualWorld = 0;
		this->TextLabels[i].useLineOfSight = true;
		this->TextLabels[i].color = 0;
		this->TextLabels[i].drawDistance = 0.f;
		this->TextLabels[i].attachedToPlayerID = 
			this->TextLabels[i].attachedToVehicleID = 0xFFFF;
		this->TextLabels[i].text = 0;

		this->isCreated[i] = 0;
	}
}

CText3DLabels::~CText3DLabels( )
{
	for(_Text3DID i = 0; i < MAX_TEXT_LABELS; i++) 
	{
		if(this->isCreated[i])
			this->Delete3DTextLabel(i);
	}
}

/**
 *	Reference:
 *		[CALL] 0x00489280
 *



.text:0047ABE0 ; int __stdcall C3DTextLabels__Create3DTextLabel(char *text,int color,float x,float y,float z,float drawdistance,int virtualworld,char useLOS)
.text:0047ABE0 C3DTextLabels__Create3DTextLabel proc near ; CODE XREF: sub_489280+9Fp
.text:0047ABE0
.text:0047ABE0 text            = uint32_t ptr  0Ch
.text:0047ABE0 color           = uint32_t ptr  10h
.text:0047ABE0 x               = uint32_t ptr  14h
.text:0047ABE0 y               = uint32_t ptr  18h
.text:0047ABE0 z               = uint32_t ptr  1Ch
.text:0047ABE0 drawdistance    = uint32_t ptr  20h
.text:0047ABE0 virtualworld    = uint32_t ptr  24h
.text:0047ABE0 useLOS          = uint8_t ptr  28h
.text:0047ABE0
.text:0047ABE0                 push    ebx
.text:0047ABE1                 push    ebp
.text:0047ABE2                 mov     ebx, ecx
.text:0047ABE4                 xor     ebp, ebp
.text:0047ABE6                 jmp     short loc_47ABF0
.text:0047ABE6 ; ---------------------------------------------------------------------------
.text:0047ABE8                 align 10h
.text:0047ABF0
.text:0047ABF0 loc_47ABF0:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+6j
.text:0047ABF0                                         ; C3DTextLabels__Create3DTextLabel+24j
.text:0047ABF0                 movzx   eax, bp
.text:0047ABF3                 mov     ecx, [ebx+eax*4+8400h] <-- Mettre dans ecx, this->isCreated[ eax ]
.text:0047ABFA                 test    ecx, ecx <-- Tester si ecx vaut zero
.text:0047ABFC                 jz      short loc_47AC06 
.text:0047ABFE                 inc     ebp <-- incrémenter ebp pour la boucle de test
.text:0047ABFF                 cmp     bp, 400h <-- comparer bp avec 1024 la limite
.text:0047AC04                 jb      short loc_47ABF0
.text:0047AC06
.text:0047AC06 loc_47AC06:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+1Cj
.text:0047AC06                 cmp     bp, 400h
.text:0047AC0B                 jnz     short loc_47AC16
.text:0047AC0D                 pop     ebp
.text:0047AC0E                 or      ax, 0FFFFh
.text:0047AC12                 pop     ebx
.text:0047AC13                 retn    20h
.text:0047AC16 ; ---------------------------------------------------------------------------
.text:0047AC16
.text:0047AC16 loc_47AC16:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+2Bj
.text:0047AC16                 push    esi
.text:0047AC17                 mov     esi, [esp+4+text]
.text:0047AC1B                 mov     eax, esi
.text:0047AC1D                 push    edi
.text:0047AC1E                 lea     edx, [eax+1]
.text:0047AC21
.text:0047AC21 loc_47AC21:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+46j
.text:0047AC21                 mov     cl, [eax]
.text:0047AC23                 inc     eax
.text:0047AC24                 test    cl, cl
.text:0047AC26                 jnz     short loc_47AC21
.text:0047AC28                 sub     eax, edx
.text:0047AC2A                 inc     eax
.text:0047AC2B                 push    eax             ; size_t
.text:0047AC2C                 push    1               ; size_t
.text:0047AC2E                 call    _calloc
.text:0047AC33                 movzx   edi, bp
.text:0047AC36                 mov     ecx, edi
.text:0047AC38                 imul    ecx, 21h
.text:0047AC3B                 add     esp, 8
.text:0047AC3E                 add     ecx, ebx
.text:0047AC40                 mov     edx, esi
.text:0047AC42                 mov     [ecx], eax
.text:0047AC44                 mov     esi, eax
.text:0047AC46
.text:0047AC46 loc_47AC46:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+6Ej
.text:0047AC46                 mov     al, [edx]
.text:0047AC48                 inc     edx
.text:0047AC49                 mov     [esi], al
.text:0047AC4B                 inc     esi
.text:0047AC4C                 test    al, al
.text:0047AC4E                 jnz     short loc_47AC46
.text:0047AC50                 mov     edx, [esp+8+color]
.text:0047AC54                 mov     eax, [esp+8+x]
.text:0047AC58                 mov     [ecx+4], edx
.text:0047AC5B                 mov     edx, [esp+8+y]
.text:0047AC5F                 mov     [ecx+8], eax
.text:0047AC62                 mov     eax, [esp+8+z]
.text:0047AC66                 mov     [ecx+0Ch], edx
.text:0047AC69                 mov     edx, [esp+8+drawdistance]
.text:0047AC6D                 mov     [ecx+10h], eax
.text:0047AC70                 mov     eax, [esp+8+virtualworld]
.text:0047AC74                 mov     [ecx+14h], edx
.text:0047AC77                 mov     dl, [esp+8+useLOS]
.text:0047AC7B                 mov     [ecx+19h], eax
.text:0047AC7E                 mov     eax, 0FFFFh
.text:0047AC83                 mov     [ecx+18h], dl
.text:0047AC86                 mov     [ecx+1Dh], ax
.text:0047AC8A                 mov     [ecx+1Fh], ax
.text:0047AC8E                 mov     uint32_t ptr [ebx+edi*4+8400h], 1 <-- this->isCreated[ edi ] = 1
.text:0047AC99                 mov     eax, CNetGame		
.text:0047AC9E                 mov     edi, [eax+4]	<-- On fout PlayerPool dans edi
.text:0047ACA1                 test    edi, edi 
.text:0047ACA3                 jz      short loc_47AD02
.text:0047ACA5                 xor     ebx, ebx
.text:0047ACA7
.text:0047ACA7 loc_47ACA7:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+120j
.text:0047ACA7                 cmp     bx, 1F4h			<-- Ici on va faire une boucle pour tester tout les joueurs
.text:0047ACAC                 jnb     short loc_47ACF9
.text:0047ACAE                 movzx   eax, bx
.text:0047ACB1                 cmp     uint32_t ptr [edi+eax*4], 0
.text:0047ACB5                 jz      short loc_47ACF9
.text:0047ACB7                 mov     esi, [edi+eax*4+7D0h]
.text:0047ACBE                 test    esi, esi
.text:0047ACC0                 jz      short loc_47ACF9
.text:0047ACC2                 mov     al, [esi+281h]
.text:0047ACC8                 test    al, al
.text:0047ACCA                 jz      short loc_47ACF9
.text:0047ACCC                 cmp     al, 9
.text:0047ACCE                 jz      short loc_47ACF9
.text:0047ACD0                 mov     ecx, [esp+8+z]
.text:0047ACD4                 mov     edx, [esp+8+y]
.text:0047ACD8                 mov     eax, [esp+8+x]
.text:0047ACDC                 push    ecx
.text:0047ACDD                 push    edx
.text:0047ACDE                 push    eax
.text:0047ACDF                 mov     ecx, esi
.text:0047ACE1                 call    sub_491890
.text:0047ACE6                 fcomp   [esp+8+drawdistance]
.text:0047ACEA                 fnstsw  ax
.text:0047ACEC                 test    ah, 41h
.text:0047ACEF                 jp      short loc_47ACF9
.text:0047ACF1                 push    ebp
.text:0047ACF2                 mov     ecx, esi
.text:0047ACF4                 call    sub_491500
.text:0047ACF9
.text:0047ACF9 loc_47ACF9:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+CCj
.text:0047ACF9                                         ; C3DTextLabels__Create3DTextLabel+D5j ...
.text:0047ACF9                 inc     ebx
.text:0047ACFA                 cmp     ebx, 1F4h
.text:0047AD00                 jnz     short loc_47ACA7
.text:0047AD02
.text:0047AD02 loc_47AD02:                             ; CODE XREF: C3DTextLabels__Create3DTextLabel+C3j
.text:0047AD02                 pop     edi
.text:0047AD03                 pop     esi
.text:0047AD04                 mov     ax, bp
.text:0047AD07                 pop     ebp
.text:0047AD08                 pop     ebx
.text:0047AD09                 retn    20h
.text:0047AD09 C3DTextLabels__Create3DTextLabel endp

*/

_Text3DID	CText3DLabels::Create3DTextLabel( char* text, uint32_t color, float x, float y, float z, float drawDistance, uint32_t virtualWorld, bool useLOS )
{
	int id = 0;
	while( id < MAX_TEXT_LABELS )
	{
		if( this->isCreated[ id ] == 0 ) break;
		id++;
	}
	if( id >= MAX_TEXT_LABELS ) return 0x0000FFFF;

	this->TextLabels[id].posX = x;
	this->TextLabels[id].posY = y;
	this->TextLabels[id].posZ = z;
	this->TextLabels[id].virtualWorld = virtualWorld;
	this->TextLabels[id].useLineOfSight = useLOS;
	this->TextLabels[id].color = color;
	this->TextLabels[id].drawDistance = drawDistance;
	this->TextLabels[id].attachedToPlayerID = 
		this->TextLabels[id].attachedToVehicleID = 0xFFFF;
	this->TextLabels[id].text = new char[ strlen( text ) + 1 ];
	memset( this->TextLabels[id].text, 0x00, strlen( text ) + 1 );
	strcpy( this->TextLabels[id].text, text );

	this->isCreated[id] = 1;

	

	for( _PlayerID i = 0; i < MAX_PLAYERS; i++ )
	{

		if( __NetGame->playerPool->GetSlotState( i ) == true )
		{
			CPlayer* player = 0;
			if( ( player = __NetGame->playerPool->GetPlayer( i ) ) > 0 )
			{

				if( player->isSpectating( ) == false )
				{

					if( player->GetDistanceFrom3DPoint( x, y, z ) <= drawDistance ) 
					{
						showForPlayer( ( uint16_t )id, i );
					}

				}

			}
		}



	}
	
	return id;
}


void CText3DLabels::showForPlayer( _Text3DID labelID, _PlayerID playerID )
{
	if( 0 > labelID || labelID > MAX_TEXT_LABELS ) return; 

	if( this->isCreated[labelID] == 0 ) return;


	RakNet::BitStream bStream;
		
	bStream.Write( ( _Text3DID )labelID );
	bStream.Write( ( uint32_t )this->TextLabels[ labelID ].color );
	bStream.Write( (float)this->TextLabels[ labelID ].posX );
	bStream.Write( (float)this->TextLabels[ labelID ].posY );
	bStream.Write( (float)this->TextLabels[ labelID ].posZ );
	bStream.Write( (float)this->TextLabels[ labelID ].drawDistance );
	bStream.Write( ( uint8_t )this->TextLabels[ labelID ].useLineOfSight );
	bStream.Write( (uint16_t)this->TextLabels[ labelID ].attachedToPlayerID );
	bStream.Write( (uint16_t)this->TextLabels[ labelID ].attachedToVehicleID );
	stringCompressor->EncodeString( this->TextLabels[ labelID ].text, strlen( this->TextLabels[ labelID ].text ) + 1, &bStream, 0 );
	__NetGame->PlayerRPC( RPC_ShowText3DLabels, &bStream, playerID, 2 );
}

int CText3DLabels::Delete3DTextLabel( _Text3DID labelID )
{
	if( 0 > labelID || labelID > MAX_TEXT_LABELS ) return 0; 

	if( this->isCreated[labelID] == 0 ) return 0;

	this->TextLabels[labelID].posX = 0.f;
	this->TextLabels[labelID].posY = 0.f;
	this->TextLabels[labelID].posZ = 0.f;
	this->TextLabels[labelID].virtualWorld = 0;
	this->TextLabels[labelID].useLineOfSight = true;
	this->TextLabels[labelID].color = 0;
	this->TextLabels[labelID].drawDistance = 0.f;
	this->TextLabels[labelID].attachedToPlayerID = 
		this->TextLabels[labelID].attachedToVehicleID = 0xFFFF;
	
	if( this->TextLabels[labelID].text > 0 )
	{
		delete this->TextLabels[labelID].text;
		this->TextLabels[labelID].text = 0;
	}

	this->isCreated[labelID] = 0;
	
	hideForAll( ( uint16_t )labelID );

	return 1;
}

int CText3DLabels::Update3DTextLabelText( _Text3DID labelID, uint32_t color, char* text )
{
	if( 0 > labelID || labelID > MAX_TEXT_LABELS ) return 0; 
	if( this->isCreated[ labelID ] == 0 ) return 0;

	this->TextLabels[ labelID ].color = color;
	delete this->TextLabels[ labelID ].text;
	this->TextLabels[ labelID ].text = new char[ strlen( text ) + 1 ];
	memset( this->TextLabels[ labelID ].text, 0x00, strlen( text ) + 1 );
	strcpy( this->TextLabels[ labelID ].text, text );

	

	updateForAll( ( uint16_t )labelID );


	return 1;
}

int CText3DLabels::Attach3DTextLabelToVehicle( _Text3DID labelID, uint16_t vehicleID, float offsetX, float offsetY, float offsetZ )
{
	if( 0 > labelID || labelID > MAX_TEXT_LABELS ) return 0; 
	if( this->isCreated[ labelID ] == 0 ) return 0;

	if( __NetGame->vehiclePool->GetSlotState( vehicleID ) == false ) return 0;

	this->TextLabels[labelID].attachedToVehicleID = vehicleID;
	this->TextLabels[labelID].posX = offsetX;
	this->TextLabels[labelID].posY = offsetY;
	this->TextLabels[labelID].posZ = offsetZ;

	updateForAll( ( uint16_t )labelID );

	return 1;
}

int CText3DLabels::Attach3DTextLabelPlayer( _Text3DID labelID, _PlayerID playerID, float offsetX, float offsetY, float offsetZ )
{
	if( 0 > labelID || labelID > MAX_TEXT_LABELS ) return 0; 
	if( this->isCreated[ labelID ] == 0 ) return 0;

	if( __NetGame->playerPool->GetSlotState( playerID ) == false ) return 0;


	this->TextLabels[labelID].attachedToPlayerID = playerID;
	this->TextLabels[labelID].posX = offsetX;
	this->TextLabels[labelID].posY = offsetY;
	this->TextLabels[labelID].posZ = offsetZ;

	updateForAll( ( uint16_t )labelID );


	return 1;
}

void CText3DLabels::hideForPlayer( _Text3DID labelID, _PlayerID playerID )
{
	if( 0 > labelID || labelID >= MAX_TEXT_LABELS ) return;
	RakNet::BitStream bStream;
	
	bStream.Write( ( uint16_t )labelID );
	__NetGame->PlayerRPC( RPC_HideText3DLabel, &bStream, playerID, 2 );

}

void CText3DLabels::hideForAll( _Text3DID labelID )
{
	if( 0 > labelID || labelID >= MAX_TEXT_LABELS ) return;

	for( _PlayerID i = 0; i < MAX_PLAYERS; i++ )
	{
		CPlayer* player = __NetGame->playerPool->GetPlayer( i );
		if( player )
		{
			player->hideText3DLabel( labelID );
		}
	}
}

void CText3DLabels::updateForAll( _Text3DID labelID )
{

	if( __NetGame->playerPool > 0 )
	{

		for( _PlayerID playerID = 0; playerID < MAX_PLAYERS; playerID++ )
		{
			if( __NetGame->playerPool->GetSlotState( playerID ) )
			{
				CPlayer* player = 0;
				if( ( player = __NetGame->playerPool->GetPlayer( playerID ) ) > 0 )
				{
					
					if( player->isText3DLabelStreamedIn( labelID ) )
					{
						player->hideText3DLabel( labelID );
						player->showText3DLabel( labelID );
					}

				}

			}
		}

	}


}

bool CText3DLabels::GetSlotState( _Text3DID labelID )
{
	if( 0 > labelID || labelID >= MAX_TEXT_LABELS ) return false;

	if( isCreated[labelID] == TRUE )
	{
		return true;	
	}
	return false;
}