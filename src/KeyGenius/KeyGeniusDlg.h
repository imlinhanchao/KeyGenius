// KeyGeniusDlg.h : header file
//

#pragma once

#define TIMER_LOADHOTKEY 0

// CKeyGeniusDlg dialog
class CKeyGeniusDlg : public CDialog
{
// Construction
public:
	CKeyGeniusDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KEYGENIUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	static DWORD ThreadProc(LPVOID lpParameter);
	UINT GetModifiers(DWORD dwHotKey);
	void LoadHotKey();

	int MinRun();

	NOTIFYICONDATA	m_nd; //定义托盘图标结构体
	DWORD m_vkLoop;
	HANDLE m_hThread;
	bool m_bLoop;
	bool m_bThread;

	CEdit* m_pTime;
	CConfig m_config;
	HOTKEY_CFG m_hotkey;
	CHotKeyCtrl* m_pNextHotKey;
	CHotKeyCtrl* m_pStopHotKey;
	CHotKeyCtrl* m_pKey1HotKey;
	CHotKeyCtrl* m_pKey2HotKey;
};
