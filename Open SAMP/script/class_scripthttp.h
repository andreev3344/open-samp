
struct httpWorkers // size 0x284A
{
#pragma pack( 1 )

	CHttpClient*httpClient;		// + 0x0	0
	uint32_t	responseCode;	// + 0x4	4
	uint32_t	threadId;		// + 0x8	8
	uint32_t	type;			// + 0xC	12

	char		url[0x800];		// + 0x10	16

	char		data[0x2000];	// + 0x811	2065

	uint32_t	unk_noCallback;	// + 0x2812 10258
	AMX*		httpAMX;		// + 0x2816	10262
	char*		amxCallback;	// + 0x281A 10266

	uint32_t	lastTick;		// + 0x2842 10306
	uint32_t	unkdword;		// + 0x2846 10310 | ou 2x word ?
};

class CScriptHttp // size 0x1F79D0 wtf
{
#pragma pack( 1 )		
public:

	httpWorkers workers[200];

	int		Start(uint32_t threadID, uint32_t type, char* url, char* data, char* unk, uint32_t hasCallback, AMX* pAMX, char* callback);
	void	Process();

	CScriptHttp();
	~CScriptHttp();
};
