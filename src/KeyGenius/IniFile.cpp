#include "stdafx.h"
#include "IniFile.h"


//---------------------------------------------------------------------------------------------------------------
CIniFile::CIniFile()
{
	ZeroMemory(m_szIniFile, sizeof(TCHAR) * MAX_PATH);
}
//---------------------------------------------------------------------------------------------------------------
CIniFile::~CIniFile()
{
}
//---------------------------------------------------------------------------------------------------------------
void CIniFile::SetIniFile(CString strIniFile)
{
	memcpy(m_szIniFile, strIniFile.GetBuffer(MAX_PATH), sizeof(TCHAR) * MAX_PATH);
	strIniFile.ReleaseBuffer();
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, DWORD* pValue)
{
	TCHAR szValue[MAX_PATH];

	*pValue = 0;
	if(0 != GetPrivateProfileString(pszAppName, pszKeyName, NULL, szValue, MAX_PATH, m_szIniFile))
	{
		*pValue = (DWORD)_ttol(szValue);
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, DWORD dwValue)
{
	TCHAR szValue[MAX_PATH];
	_ltot(dwValue, szValue, 10);

	return WritePrivateProfileString(pszAppName, pszKeyName, szValue, m_szIniFile);
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, UINT* pValue)
{
	TCHAR szValue[MAX_PATH];

	*pValue = 0;
	if(0 != GetPrivateProfileString(pszAppName, pszKeyName, NULL, szValue, MAX_PATH, m_szIniFile))
	{
		*pValue = (UINT)_ttol(szValue);
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, UINT dwValue)
{
	TCHAR szValue[MAX_PATH];
	_ltot(dwValue, szValue, 10);

	return WritePrivateProfileString(pszAppName, pszKeyName, szValue, m_szIniFile);
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString sAppName, CString strKeyName, DWORD* pValue)
{
	BOOL bDone = FALSE;
	TCHAR szValue[MAX_PATH];

	*pValue = 0;
	if(0 != GetPrivateProfileString(sAppName.GetBuffer(), strKeyName.GetBuffer(), NULL, szValue, MAX_PATH, m_szIniFile))
	{
		bDone = TRUE;
		*pValue = (DWORD)_ttoi(szValue);
	}

	sAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	return bDone;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString sAppName, CString strKeyName, DWORD dwValue)
{
	TCHAR szValue[MAX_PATH];
	_itot(dwValue, szValue, 10);

	BOOL bDone = WritePrivateProfileString(sAppName.GetBuffer(), strKeyName.GetBuffer(), szValue, m_szIniFile);
	sAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	return bDone;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, INT* pValue)
{
	TCHAR szValue[MAX_PATH];

	*pValue = 0;
	if(0 != GetPrivateProfileString(pszAppName, pszKeyName, NULL, szValue, MAX_PATH, m_szIniFile))
	{
		*pValue = (INT)_ttoi(szValue);
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, INT iValue)
{
	TCHAR szValue[MAX_PATH];
	_itot(iValue, szValue, 10);

	return WritePrivateProfileString(pszAppName, pszKeyName, szValue, m_szIniFile);
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString sAppName, CString strKeyName, INT* pValue)
{
	BOOL bDone = FALSE;
	TCHAR szValue[MAX_PATH];

	*pValue = 0;
	if(0 != GetPrivateProfileString(sAppName.GetBuffer(), strKeyName.GetBuffer(), NULL, szValue, MAX_PATH, m_szIniFile))
	{
		bDone = TRUE;
		*pValue = (INT)_ttoi(szValue);
	}

	sAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	return bDone;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString sAppName, CString strKeyName, INT  iValue)
{
	TCHAR szValue[MAX_PATH];
	_itot(iValue, szValue, 10);

	BOOL bDone = WritePrivateProfileString(sAppName.GetBuffer(), strKeyName.GetBuffer(), szValue, m_szIniFile);
	sAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();

	return bDone;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, TCHAR szValue[MAX_PATH])
{
	return GetPrivateProfileString(pszAppName, pszKeyName, NULL, szValue, MAX_PATH, m_szIniFile);
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, TCHAR szValue[MAX_PATH])
{
	return WritePrivateProfileString(pszAppName, pszKeyName, szValue, m_szIniFile);
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::GetIniInfo(CString sAppName, CString strKeyName, CString& strValue)
{	

	BOOL bDone = GetPrivateProfileString(sAppName.GetBuffer(), strKeyName.GetBuffer(), NULL, strValue.GetBuffer(2048), 2048, m_szIniFile);
	sAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();
	strValue.ReleaseBuffer();

	return bDone;
}
//---------------------------------------------------------------------------------------------------------------
BOOL CIniFile::SetIniInfo(CString sAppName, CString strKeyName, CString  strValue)
{
	BOOL bDone = WritePrivateProfileString(sAppName.GetBuffer(), strKeyName.GetBuffer(), strValue.GetBuffer(), m_szIniFile);
	sAppName.ReleaseBuffer();
	strKeyName.ReleaseBuffer();
	strValue.ReleaseBuffer();

	return bDone;
}
//---------------------------------------------------------------------------------------------------------------