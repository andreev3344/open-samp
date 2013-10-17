#include "../main.h"


CScriptDialog::CScriptDialog(IDirect3DDevice9* pDevice)
{

}

void CScriptDialog::Disable()
{
	uint32_t returned = 0;
	_asm 
	{
		pushad
		mov edx, FUNC_CSCRIPTDIALOG_Disable
		add edx, sampBaseAddr
		mov ecx, this
		call edx
		mov returned, eax
		popad
	}
}

void CScriptDialog::AddListItemsFromString(char *szString)
{
	uint32_t returned = 0;
	_asm 
	{
		pushad
		mov edx, FUNC_CSCRIPTDIALOG_AddListItems
		add edx, sampBaseAddr
		mov ecx, this
		push szString
		call edx
		mov returned, eax
		popad
	}
}

void CScriptDialog::ShowDialog(int iID, int iDialogStyle, char *szCaption, char *szInformation, char *szButtonText1, char *szButtonText2)
{
	uint32_t returned = 0;
	_asm
	{
		pushad
		mov ecx, this
		mov edx, FUNC_CSCRIPTDIALOG_ShowDialog
		add edx, sampBaseAddr

		push szButtonText2
		push szButtonText1
		push szInformation
		push szCaption
		push iDialogStyle
		push iID

		call edx
		mov returned, eax
		popad
	}

}