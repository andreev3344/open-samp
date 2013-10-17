

class CHttpClient // size 0x7330
{
#pragma pack( 1 )
public:

	SOCKET		httpSocket;			// + 0x0 0
	uint32_t	response;			// + 0x4 4

	char		unkBuffer001[0x7208];// + 0x8 8 // ?

	uint16_t	unkWord001;			// + 0x7210 29200
	uint8_t		unkByte001;			// + 0x7212 29202
	uint32_t	unkDword001;		// + 0x7213 29203
	uint32_t	unkDword002;		// + 0x7217 29207
	uint32_t	unkDword003;		// + 0x721B 29211
	uint32_t	unkDword004;		// + 0x721F 29215
	uint32_t	unkDword005;		// + 0x7223 29219
	uint32_t	unkDword006;		// + 0x7227 29223

	char		unkBuffer002[0x100];// + 0x722B 29227

	uint32_t	unkDword007;		// + 0x732C 29484


	CHttpClient(char* unk);
	~CHttpClient();

};
