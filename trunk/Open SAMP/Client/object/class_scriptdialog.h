#ifndef __CLASS_SCRIPTDIALOG_H__
#define __CLASS_SCRIPTDIALOG_H__

#define DIALOG_STYLE_MSGBOX		0
#define DIALOG_STYLE_INPUT		1
#define DIALOG_STYLE_LIST		2
#define DIALOG_STYLE_PASSWORD	3	// je m'y colle pas :p


#define FUNC_CSCRIPTDIALOG_ShowDialog	0x63E90
#define FUNC_CSCRIPTDIALOG_AddListItems	0x63CE0
#define FUNC_CSCRIPTDIALOG_Disable		0x63B90

class CScriptDialog
{
private:
	IDirect3DDevice9	*m_pDevice;				// + 0x0000

	int					m_iScreenOffsetX;		// + 0x0004
	int					m_iScreenOffsetY;		// + 0x0008
	int					m_iWidth;				// + 0x000C
	int					m_iHeight;				// + 0x0010
	int					m_iButtonWidth;			// + 0x0014
	int					m_iButtonHeight;		// + 0x0018

 	CDXUTDialog			*m_pScriptDialogUI;		// + 0x001C
	// controls
	CDXUTListBox		*m_pListBox;			// + 0x0020
    CDXUTEditBox		*m_pInputEdit;			// + 0x0024

	BOOL				m_bShowing;				// + 0x0028
	int					m_iDialogStyle;			// + 0x002C
	int					m_iCurrentId;			// + 0x0030
	char				*m_szInformation;		// + 0x0034
	SIZE				m_sizeText;				// + 0x0038
    char				m_szCaption[64+1];		// + 0x0040

public:
	CScriptDialog(IDirect3DDevice9* pDevice);
	~CScriptDialog(){};

	BOOL IsShowing() { return m_bShowing; };

	void AddListItemsFromString(char *szString);
	void ShowDialog(int iID, int iDialogStyle, char *szCaption, char *szInformation, char *szButtonText1, char *szButtonText2);
	void Disable(); // 0x63B90

	void GetScreenRect(RECT *rect);		
	void ResetDialogControls(CDXUTDialog *pScriptDialogUI);
	void Draw();

	void UpdateRects();

	void ProcessInput(int iResponse); // 0x64140

	int  GetStyle() { return m_iDialogStyle; };
	int  GetID()	{ return m_iCurrentId; };

};

#endif