#include "stdafx.h"
#include "common.h"

#pragma comment(lib, "version")

CString s_sServer;
CString s_sDatabase;
CString s_sUser;
CString s_sPassword;


CString GetCurDirectory()
{
	static CString s_str = _T("");
	if(_T("") == s_str)
	{
		GetModuleFileName(NULL, s_str.GetBuffer(MAX_PATH), MAX_PATH);
		s_str.ReleaseBuffer();
		s_str = s_str.Mid(0, s_str.ReverseFind(_T('\\')) + 1);
	}

	return s_str;
}

// Get tool version
DWORD GetFixedFileVersion(const TCHAR* szModuleName, TCHAR* szFileVersion)
{
	LPBYTE lpVersionData = NULL; 
	DWORD  dwLangCharset = 0; 
	
	// Get the version information size for allocate the buffer
	DWORD dwHandle = 0;     
	DWORD dwDataSize = ::GetFileVersionInfoSize((LPTSTR)szModuleName, &dwHandle); 
	if ( dwDataSize == 0 ) 
	{
		return GetLastError();
	}

	// Allocate buffer and retrieve version information
	lpVersionData = new BYTE[dwDataSize + 1]; 
	if (!::GetFileVersionInfo((LPTSTR)szModuleName, dwHandle, dwDataSize, (void**)lpVersionData) )
	{
		delete[] lpVersionData;
		return GetLastError();
	}

	// Retrieve the first language and character-set identifier
	UINT   nQuerySize = 0;
	DWORD* pTransTable = NULL;
	if (!::VerQueryValue(lpVersionData, _T("\\VarFileInfo\\Translation"), (void **)&pTransTable, &nQuerySize) )
	{
		delete[] lpVersionData;
		return ERROR_INVALID_DATA;
	}

	// Swap the words to have lang-charset in the correct format
	dwLangCharset = MAKELONG(HIWORD(pTransTable[0]), LOWORD(pTransTable[0]));

	// Get fixed file information
	VS_FIXEDFILEINFO* pVsffi;
	if ( !::VerQueryValue((void **)lpVersionData, _T("\\"), (void**)&pVsffi, &nQuerySize) )
	{
		return ERROR_INVALID_DATA;
	}

	_stprintf(szFileVersion, _T("%u.%u.%u"), HIWORD(pVsffi->dwFileVersionMS), LOWORD(pVsffi->dwFileVersionMS), 
			HIWORD(pVsffi->dwFileVersionLS));

	return ERROR_SUCCESS;
}

bool IsNumber(LPCTSTR pszText)
{
	for( int i = 0; i < lstrlen( pszText ); i++ )
		if(!_istdigit(pszText[ i ]))
			return false;
	return true;
}

CString DateToString(COleDateTime date)
{
	CString sDate;
	sDate.Format(_T("%d-%02d-%02d %02d:%02d:%02d"), 
		date.GetYear(), 
		date.GetMonth(), 
		date.GetDay(), 
		date.GetHour(), 
		date.GetMinute(), 
		date.GetSecond());
	return sDate;
}

CString ToString(int nValue)
{
	CString sValue;
	sValue.Format(_T("%d"), nValue);
	return sValue;
}

bool LockMutex(CString sName)
{
	HANDLE hInstance = NULL;
	hInstance = CreateMutex(NULL, TRUE, sName);
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hInstance);
		hInstance = NULL;
		::PostQuitMessage(0);
		return false;
	}
	return true;
}