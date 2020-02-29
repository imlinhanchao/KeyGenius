#include "KeyThread.h"

KeyThread::KeyThread()
{
    m_bKey1 = true;
}

void KeyThread::reset(HOTKEY_CFG cfg)
{
    m_config = cfg;
}

void KeyThread::stop()
{
    m_bRun = false;
}

void KeyThread::run()
{
    m_bRun = true;
    while (m_bRun)
    {
        qDebug() << "Hotkey Activated" << (m_bKey1 ? "key1" : "key2");
        m_config.press(m_bKey1 ? HOTKEY_CFG::key1 : HOTKEY_CFG::key2);
        Sleep(m_config.nTimeInterval);
    }
}
