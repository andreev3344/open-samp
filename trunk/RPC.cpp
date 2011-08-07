#include "main.h"

uint32_t RPC_SetPlayerArmedWeapon = 0x0A;

uint32_t RPC_SetPlayerSkin = 0x0D;
uint32_t RPC_SetPlayerName = 0x0E;
uint32_t RPC_SetPlayerPosition = 0x0F;
uint32_t RPC_SetPlayerPositionFindZ = 0x10;
uint32_t RPC_SetPlayerHealth = 0x11;
uint32_t RPC_PutPlayerInVehicle = 0x12;
uint32_t RPC_RemovePlayerFromVehicle = 0x13;
uint32_t RPC_SetPlayerColor = 0x14;

uint32_t RPC_SetPlayerInterior = 0x16;
uint32_t RPC_SetPlayerCameraPos = 0x17;
uint32_t RPC_SetPlayerCameralookAt = 0x18;


uint32_t RPC_SetPlayerCameraBehindPlayer = 0x1C;
uint32_t RPC_TogglePlayerControllable = 0x1D;
uint32_t RPC_PlayerPlaySound = 0x1E;

uint32_t RPC_GivePlayerMoney = 0x20;
uint32_t RPC_SetPlayerFacingAngle = 0x21;
uint32_t RPC_ResetPlayerMoney = 0x22;
uint32_t RPC_ResetPlayerWeapons = 0x23;
uint32_t RPC_GivePlayerWeapon = 0x24;

uint32_t RPC_SetPlayerArmour = 0x27;

uint32_t RPC_SetPlayerMapIcon = 0x29;
uint32_t RPC_RemovePlayerMapIcon = 0x2A;
uint32_t RPC_SetPlayerAmmo = 0x2B;

uint32_t RPC_SpawnObject = 0x30;
uint32_t RPC_SetObjectPosition = 0x31;
uint32_t RPC_SetObjectRotation = 0x32;
uint32_t RPC_DestroyObject = 0x33;
uint32_t RPC_ShowPlayerNameTagForPlayer = 0x37;
uint32_t RPC_MoveObject = 0x38;
uint32_t RPC_TogglePlayerSpectating = 0x3B;
uint32_t RPC_StopObject = 0x39;


uint32_t RPC_SetPlayerSpectatingPlayer = 0x3D;
uint32_t RPC_SetPlayerSpectatingVehicle = 0x3E;

uint32_t RPC_ForceClassSelection = 0x40;
uint32_t RPC_AttachObjectToPlayer = 0x41;
uint32_t RPC_Menu_InitForPlayer = 0x42;
uint32_t RPC_Menu_ShowForPlayer = 0x43;
uint32_t RPC_Menu_HideForPlayer = 0x44;
uint32_t RPC_SetPlayerWantedLevel = 0x45;
uint32_t RPC_ShowTextDraw = 0x46;
uint32_t RPC_HideTextDraw = 0x47;
uint32_t RPC_EnableStuntBonus = 0x48;
uint32_t RPC_TextDraw_SetString = 0x49;
uint32_t RPC_AddGangZone = 0x4A;
uint32_t RPC_RemoveGangZone = 0x4B;
uint32_t RPC_FlashGangZone = 0x4C;
uint32_t RPC_StopFlashGangZone = 0x4D;
uint32_t RPC_ApplyAnimation = 0x4E;
uint32_t RPC_ClearAnimation = 0x4F;
uint32_t RPC_SetPlayerSpecialAction = 0x50;
uint32_t RPC_SetPlayerFightingStyle = 0x51;
uint32_t RPC_SetPlayerVelocity = 0x52;

uint32_t RPC_PlayCrimeReportForPlayer = 0x5A;
uint32_t RPC_AttachAttachedObject = 0x5B;

uint32_t RPC_NewPlayer = 0x62;
uint32_t RPC_PlayerLeave = 0x63;

uint32_t RPC_spawnPlayerForPlayer = 0x65;

uint32_t RPC_ShowCheckpoint = 0x6D;
uint32_t RPC_HideCheckpoint = 0x6E;
uint32_t RPC_ShowRaceCheckpoint = 0x6F;
uint32_t RPC_HideRaceCheckpoint = 0x70;

uint32_t RPC_AddPlayerMessage = 0x7D;

uint32_t RPC_SetPlayerShopName = 0x8E;
uint32_t RPC_SetSkillLevel = 0x8F;

uint32_t RPC_SetPlayerDrunkLevel = 0x90;
uint32_t RPC_ShowText3DLabels = 0x91;
uint32_t RPC_HideText3DLabel = 0x92;

uint32_t RPC_SendTime = 0x94;