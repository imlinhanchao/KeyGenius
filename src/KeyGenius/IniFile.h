#ifndef _INIFILE_H_
#define _INIFILE_H_

class CIniFile
{
public:
	 CIniFile();
	~CIniFile();

	void SetIniFile(CString strIniFile);

	BOOL GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, UINT* pValue);
	BOOL SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, UINT dwValue);

	BOOL GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, DWORD* pValue);
	BOOL SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, DWORD dwValue);

	BOOL GetIniInfo(CString sAppName, CString strKeyName, DWORD* pValue);
	BOOL SetIniInfo(CString sAppName, CString strKeyName, DWORD dwValue);

	BOOL GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, INT* pValue);
	BOOL SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, INT  iValue);

	BOOL GetIniInfo(CString sAppName, CString strKeyName, INT* pValue);
	BOOL SetIniInfo(CString sAppName, CString strKeyName, INT  iValue);

	BOOL GetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, TCHAR szValue[MAX_PATH]);
	BOOL SetIniInfo(TCHAR *pszAppName, TCHAR* pszKeyName, TCHAR szValue[MAX_PATH]);

	BOOL GetIniInfo(CString sAppName, CString strKeyName, CString& strValue);
	BOOL SetIniInfo(CString sAppName, CString strKeyName, CString  strValue);


private:
	TCHAR m_szIniFile[MAX_PATH];
};

#endif

