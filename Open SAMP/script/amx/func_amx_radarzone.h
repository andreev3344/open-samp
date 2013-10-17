#ifndef __FUNC_AMX_RADAR_ZONE_H_
#define __FUNC_AMX_RADAR_ZONE_H_

cell AMX_NATIVE_CALL funcRadarZoneCreate ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarZoneDestroy ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcRadarZoneIsValid ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcRadarZoneSetSize ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarZoneGetSize ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcRadarZoneGetCenter ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcRadarZoneSetColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarZoneGetColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarZoneSetFlashingColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarZoneGetFlashingColor ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcRadarZoneSetFlashing ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRadarZoneIsFlashing ( AMX* a_AmxInterface, cell* a_Params );

// __FUNC_AMX_RADAR_ZONE_H_
#endif