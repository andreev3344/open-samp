#ifndef __FUNC_AMX_ELEMENT_H_
#define __FUNC_AMX_ELEMENT_H_

cell AMX_NATIVE_CALL funcElementCreate ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementClone ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementDestroy ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementSetModel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementGetModel ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementIsValid ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementGetType ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementSetParent ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementGetParent ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementSetOwner ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementGetOwner ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementSetPosition ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementGetPosition ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementSetAbsolutePosition ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementGetAbsolutePosition ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementGetDistanceFromPoint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcElementGetDistanceFromElement ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcElementMove ( AMX* a_AmxInterface, cell* a_Params );

// __FUNC_AMX_ELEMENT_H_
#endif