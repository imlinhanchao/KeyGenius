#ifndef _STOCKDATA_COMMON_H__
#define _STOCKDATA_COMMON_H__

#include "shlwapi.h"
#include "IniFile.h"

CString GetCurDirectory();
DWORD GetFixedFileVersion(const TCHAR* szModuleName, TCHAR* szFileVersion);

bool IsNumber(LPCTSTR pszText);
CString DateToString(COleDateTime date);
CString ToString(int nValue);
bool LockMutex(CString sName);

#endif