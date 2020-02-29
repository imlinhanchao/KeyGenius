#ifndef KEYTHREAD_H
#define KEYTHREAD_H

#include <QtCore>
#include "inc/config.h"

class KeyThread : public QThread
{
public:
    KeyThread();

    void reset(HOTKEY_CFG cfg);
    void stop();
    void run() override;

    inline void switchKey() { m_bKey1 = !m_bKey1; };

private:
    HOTKEY_CFG m_config;
    bool m_bKey1;
    bool m_bRun;
};

#endif // KEYTHREAD_H
