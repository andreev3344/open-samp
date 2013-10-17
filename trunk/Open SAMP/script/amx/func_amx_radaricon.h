#ifndef __FUNC_AMX_RADAR_ICON_H_
#define __FUNC_AMX_RADAR_ICON_H_

cell AMX_NATIVE_CALL funcRadarIconCreate ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarIconDestroy ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcRadarIconIsValid ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcRadarIconSetColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarIconGetColor ( AMX* a_AmxInterface, cell* a_Params );

// __FUNC_AMX_RADAR_ICON_H_
#endif