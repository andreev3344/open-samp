#ifndef _CPLUGINS_HEADER_
#define _CPLUGINS_HEADER_

#include "plugincommon.h"
#include "plugininternal.h"

#include <vector>

#ifdef LINUX
	#include <dlfcn.h>

	#define PLUGIN_LOAD(p) dlopen(p, RTLD_LAZY)
	#define PLUGIN_UNLOAD dlclose
	#define PLUGIN_GETFUNCTION dlsym
	#define PLUGIN_GETERROR dlerror
#else
#ifdef UNICODE
	#define PLUGIN_LOAD LoadLibraryA
#else
	#define PLUGIN_LOAD LoadLibrary
#endif
	#define PLUGIN_UNLOAD FreeLibrary
	#define PLUGIN_GETFUNCTION GetProcAddress
#endif

typedef bool (PLUGIN_CALL *ServerPluginLoad_t)(void **data);
typedef void (PLUGIN_CALL *ServerPluginUnload_t)();
typedef unsigned int (PLUGIN_CALL *ServerPluginSupports_t)();
typedef void (PLUGIN_CALL *ServerPluginProcessTick_t)();

typedef int (PLUGIN_CALL *ServerPluginAmxLoad_t)(AMX *amx);
typedef int (PLUGIN_CALL *ServerPluginAmxUnload_t)(AMX *amx);

struct pluginData 
{
#ifdef LINUX
	void *hModule;
#else
	HMODULE hModule;
#endif
	SUPPORTS_FLAGS dwSupportFlags;
	
	ServerPluginLoad_t		Load;
	ServerPluginUnload_t	Unload;
	ServerPluginSupports_t	Supports;
	ServerPluginProcessTick_t	ProcessTick;

	ServerPluginAmxLoad_t	AmxLoad;
	ServerPluginAmxUnload_t AmxUnload;
};

class CPlugins 
{
private:
	void* pPluginData[MAX_PLUGIN_DATA];
	void* amxExports[MAX_PLUGIN_AMX_EXPORT];
	
	std::vector<pluginData*> pluginsVector;

	BOOL LoadPlugin(char* szPluginPath);

public:
	CPlugins();
	~CPlugins();

	void LoadPlugins(char* szSearchPath);
	void LoadPluginsSearch(char *szSearchPath);
	uint32_t GetPluginCount() { return (uint32_t)pluginsVector.size(); };
	pluginData* GetPlugin(DWORD index);

	void DoProcessTick();

	void DoAmxLoad(AMX *amx);
	void DoAmxUnload(AMX *amx);

};

#endif