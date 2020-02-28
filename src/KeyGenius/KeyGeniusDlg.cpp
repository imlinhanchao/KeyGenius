// KeyGeniusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeyGenius.h"
#include "KeyGeniusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyGeniusDlg dialog
#define  WM_SHOWTASK  (WM_USER + 100)
#define VK_X					0x58
#define VK_Y					0x59

CKeyGeniusDlg::CKeyGeniusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyGeniusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyGeniusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyGeniusDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CKeyGeniusDlg message handlers

BOOL CKeyGeniusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if(!LockMutex(_T("HANCEL_KEYGENIUS_RUNNING_INSTANCE")))
		return 0;

	TCHAR szVersion[64] = {0};
	TCHAR szModuleName[MAX_PATH] = {0};
	CString sTitle = _T("按键精灵 Design by Hancel Lin.");

	GetModuleFileName(NULL, szModuleName, sizeof(szModuleName));
	if(ERROR_SUCCESS == GetFixedFileVersion(szModuleName, szVersion))
	{
		sTitle.Format(_T("按键精灵 Ver%s Design by Hancel Lin."), szVersion);
	}

	SetWindowText(sTitle);

	m_config.GetConfig(m_hotkey);

	m_vkLoop = m_hotkey.vkKey1;
	m_bLoop = false;
	m_hThread = NULL;

	m_pTime = (CEdit*)GetDlgItem(IDC_EDIT_TIME);
	m_pNextHotKey = (CHotKeyCtrl*)GetDlgItem(IDC_HOTKEY_NEXT);
	m_pStopHotKey = (CHotKeyCtrl*)GetDlgItem(IDC_HOTKEY_STOP);
	m_pKey1HotKey = (CHotKeyCtrl*)GetDlgItem(IDC_HOTKEY_KEY1);
	m_pKey2HotKey = (CHotKeyCtrl*)GetDlgItem(IDC_HOTKEY_KEY2);

	m_pTime->SetWindowText(ToString(m_hotkey.nTimeInterval));
	m_pNextHotKey->SetHotKey(m_hotkey.vkNext & 0xff, m_hotkey.vkNext >> 0x08);
	m_pStopHotKey->SetHotKey(m_hotkey.vkStop & 0xff, m_hotkey.vkStop >> 0x08);
	m_pKey1HotKey->SetHotKey(m_hotkey.vkKey1 & 0xff, m_hotkey.vkKey1 >> 0x08);
	m_pKey2HotKey->SetHotKey(m_hotkey.vkKey2 & 0xff, m_hotkey.vkKey2 >> 0x08);

	RegisterHotKey(m_hWnd, IDH_HOTKEY_NEXT, GetModifiers(m_hotkey.vkNext), m_hotkey.vkNext & 0xff);
	RegisterHotKey(m_hWnd, IDH_HOTKEY_PAUSE, GetModifiers(m_hotkey.vkStop), m_hotkey.vkStop & 0xff);
	MinRun();
	SetTimer(TIMER_LOADHOTKEY, 1000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyGeniusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyGeniusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CKeyGeniusDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_HOTKEY)    
	{     
		switch(pMsg->wParam)  
		{  
		case IDH_HOTKEY_NEXT:  
			m_vkLoop = m_hotkey.vkKey1 == m_vkLoop ? m_hotkey.vkKey2 : m_hotkey.vkKey1;

			return TRUE;  
		case IDH_HOTKEY_PAUSE:  
			m_bLoop = !m_bLoop;
			if (m_bLoop) CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ThreadProc), (LPVOID)this, 0, NULL);
			return TRUE;  
		}  
	}     
	return CDialog::PreTranslateMessage(pMsg);
}

void CKeyGeniusDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(nType == SIZE_MINIMIZED)
	{ 
		ShowWindow(SW_HIDE); 
	}
}

int CKeyGeniusDlg::MinRun()
{
	m_nd.cbSize = sizeof (NOTIFYICONDATA);
	m_nd.hWnd = m_hWnd;
	m_nd.uID = IDR_MAINFRAME; 
	m_nd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;;
	m_nd.uCallbackMessage = WM_SHOWTASK;   
	m_nd.hIcon =LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	_tcscpy(m_nd.szTip, _T("Speed Shot Screen")); 
	Shell_NotifyIcon(NIM_ADD, &m_nd); 
	return 0;
}

bool GvKmSimulateHotKey(BYTE vk, bool bAlt, bool bShift, bool bCtrl)
{
	if(0 == vk)
	{
		return false;
	}

	if(bAlt)   { keybd_event(VK_MENU,    MapVirtualKey(VK_MENU,    0), 0, 0); }
	if(bShift) { keybd_event(VK_SHIFT,   MapVirtualKey(VK_SHIFT,   0), 0, 0); }
	if(bCtrl)  { keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0); }

	keybd_event(vk, MapVirtualKey(vk, 0), 0, 0);
	Sleep(100);
	keybd_event(vk, MapVirtualKey(vk, 0), KEYEVENTF_KEYUP, 0);

	if(bAlt)   { keybd_event(VK_MENU,    MapVirtualKey(VK_MENU,    0), KEYEVENTF_KEYUP, 0); }
	if(bShift) { keybd_event(VK_SHIFT,   MapVirtualKey(VK_SHIFT,   0), KEYEVENTF_KEYUP, 0); }
	if(bCtrl)  { keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0); }

	return true;
}
void CKeyGeniusDlg::OnDestroy()
{
	m_bThread = false;
	CString sValue;
	m_pTime->GetWindowText(sValue);
	m_hotkey.nTimeInterval = _ttoi(sValue);
	m_config.SetConfig(m_hotkey);

	UnregisterHotKey(m_hWnd, IDH_HOTKEY_NEXT);
	UnregisterHotKey(m_hWnd, IDH_HOTKEY_PAUSE);
	CDialog::OnDestroy();
	Shell_NotifyIcon(NIM_DELETE, &m_nd); 
}

LRESULT CKeyGeniusDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME) 
		return 1;
	switch(lParam) 
	{ 
	case WM_RBUTTONUP: 
		{ 
			LPPOINT lpoint = new tagPOINT; 
			::GetCursorPos(lpoint); 
			CMenu menu;
			menu.CreatePopupMenu(); 
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("Quit(&Q)"));
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);

			HMENU hmenu = menu.Detach(); 
			menu.DestroyMenu();
			delete lpoint;
		} 
		break; 
		case WM_LBUTTONDBLCLK: 
			{ 
				this->ShowWindow(SW_SHOWNORMAL); 
				this->SetForegroundWindow(); 
			}
			break;
	}
	return 0;
}

DWORD CKeyGeniusDlg::ThreadProc(LPVOID lpParameter)
{
	CKeyGeniusDlg* pMain = (CKeyGeniusDlg*)lpParameter;
	while(pMain->m_bLoop)
	{
		CString sTimeInterval;
		pMain->m_pTime->GetWindowText(sTimeInterval);
		GvKmSimulateHotKey(pMain->m_vkLoop & 0xff, 
			pMain->GetModifiers(pMain->m_vkLoop) & MOD_ALT, 
			pMain->GetModifiers(pMain->m_vkLoop) & MOD_SHIFT, 
			pMain->GetModifiers(pMain->m_vkLoop) & MOD_CONTROL);
		Sleep(_ttol(sTimeInterval));
	}
	return 0;
}

void CKeyGeniusDlg::LoadHotKey()
{
	DWORD dwNext = m_pNextHotKey->GetHotKey();
	DWORD dwStop = m_pStopHotKey->GetHotKey();
	DWORD dwKey1 = m_pKey1HotKey->GetHotKey();
	DWORD dwKey2 = m_pKey2HotKey->GetHotKey();

	bool bSaveIni = false;

	if(m_hotkey.vkNext != dwNext)
	{
		BOOL b = UnregisterHotKey(m_hWnd, IDH_HOTKEY_NEXT);
		b = RegisterHotKey(m_hWnd, IDH_HOTKEY_NEXT, GetModifiers(dwNext), dwNext & 0xff);
		m_hotkey.vkNext = dwNext;
		bSaveIni = true;
	}

	if(m_hotkey.vkStop != dwStop)
	{
		BOOL b = UnregisterHotKey(m_hWnd, IDH_HOTKEY_PAUSE);
		b = RegisterHotKey(m_hWnd, IDH_HOTKEY_PAUSE, GetModifiers(dwStop), dwStop & 0xff);
		int e = GetLastError();
		m_hotkey.vkStop = dwStop;
		bSaveIni = true;
	}

	if(m_hotkey.vkKey1 != dwKey1)
	{
		m_hotkey.vkKey1 = dwKey1;
		bSaveIni = true;
	}

	if(m_hotkey.vkKey2 != dwKey2)
	{
		m_hotkey.vkKey2 = dwKey2;
		bSaveIni = true;
	}

	if(bSaveIni) m_config.SetConfig(m_hotkey);
}

UINT CKeyGeniusDlg::GetModifiers(DWORD dwHotKey)
{
	UINT uModifiers = 0;
	dwHotKey >>= 0x08;
	if(dwHotKey & HOTKEYF_ALT)		uModifiers |= MOD_ALT;
	if(dwHotKey & HOTKEYF_SHIFT)	uModifiers |= MOD_SHIFT;
	if(dwHotKey & HOTKEYF_CONTROL)	uModifiers |= MOD_CONTROL;
	return uModifiers;
}

void CKeyGeniusDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (TIMER_LOADHOTKEY == nIDEvent)
	{
		if(IsWindowVisible()) LoadHotKey();
	}

	CDialog::OnTimer(nIDEvent);
}
