#include "StdAfx.h"
#include "Config.h"

CConfig::CConfig(void)
{
}

CConfig::~CConfig(void)
{
}

void CConfig::GetConfig(HOTKEY_CFG& cfg)
{
	CIniFile ini;
	CString sPath = GetCurDirectory() + _T("cfg.ini"); 

	if (!::PathFileExists(sPath))
	{
		return;
	}

	ini.SetIniFile(sPath);

	ini.GetIniInfo(_T("setting"), _T("next"), &cfg.vkNext);
	ini.GetIniInfo(_T("setting"), _T("stop"), &cfg.vkStop);
	ini.GetIniInfo(_T("setting"), _T("key1"), &cfg.vkKey1);
	ini.GetIniInfo(_T("setting"), _T("key2"), &cfg.vkKey2);

	ini.GetIniInfo(_T("setting"), _T("interval"), &cfg.nTimeInterval);

}

void CConfig::SetConfig(HOTKEY_CFG cfg)
{
	CIniFile ini;
	CString sPath = GetCurDirectory() + _T("cfg.ini"); 

	ini.SetIniFile(sPath);

	ini.SetIniInfo(_T("setting"), _T("next"), cfg.vkNext);
	ini.SetIniInfo(_T("setting"), _T("stop"), cfg.vkStop);
	ini.SetIniInfo(_T("setting"), _T("key1"), cfg.vkKey1);
	ini.SetIniInfo(_T("setting"), _T("key2"), cfg.vkKey2);

	ini.SetIniInfo(_T("setting"), _T("interval"), cfg.nTimeInterval);
}
