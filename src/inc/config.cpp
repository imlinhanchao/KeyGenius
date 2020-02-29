#include "config.h"
#include <QSettings>
#include <QApplication>

#define SETTING_FS "cfg.ini"

Config::Config()
{

}

HOTKEY_CFG Config::GetConfig(void)
{
    QString sPath = QApplication::applicationDirPath() + "/" + SETTING_FS;
    QSettings setting(sPath, QSettings::IniFormat);

    HOTKEY_CFG cfg;
    QVariant vars[HOTKEY_CFG::qty];
    vars[HOTKEY_CFG::next] = setting.value("next", cfg.vkNext);
    vars[HOTKEY_CFG::stop] = setting.value("stop", cfg.vkStop);
    vars[HOTKEY_CFG::key1] = setting.value("key1", cfg.vkKey1);
    vars[HOTKEY_CFG::key2] = setting.value("key2", cfg.vkKey2);
    vars[HOTKEY_CFG::interval] = setting.value("interval", cfg.nTimeInterval);
    cfg = HOTKEY_CFG(vars);
    return cfg;
}

void Config::SetConfig(HOTKEY_CFG cfg)
{
    QString sPath = QApplication::applicationDirPath() + "/" + SETTING_FS;
    QSettings setting(sPath, QSettings::IniFormat);
    setting.setValue("next", cfg.vkNext);
    setting.setValue("stop", cfg.vkStop);
    setting.setValue("key1", cfg.vkKey1);
    setting.setValue("key2", cfg.vkKey2);
    setting.setValue("interval", cfg.nTimeInterval);
}
