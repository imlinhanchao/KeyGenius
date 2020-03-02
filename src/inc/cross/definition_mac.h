#pragma once
#include <qglobal.h>

#ifdef Q_OS_MAC

#define ICON_RES ":/icon/KeyGenius.icns"


#include <QSettings>
#include <QKeySequence>
#include <Carbon/Carbon.h>
#include <ApplicationServices/ApplicationServices.h>

unsigned int Sleep(unsigned int m);
void KeybdEvent(CGKeyCode key, bool bkeydown);


CGKeyCode toCGKeyCode(Qt::Key k);


typedef struct _HOTKEY_CFG
{
    int vkNext;
    int vkStop;
    int vkKey1;
    int vkKey2;

    int	nTimeInterval;

    enum { next=0, stop, key1, key2, interval, qty };

    _HOTKEY_CFG()
    {
        vkNext = Qt::Key_N + Qt::ALT;
        vkStop = Qt::Key_S+ Qt::ALT;
        vkKey1 = Qt::Key_S + Qt::CTRL;
        vkKey2 = Qt::Key_F7;
        nTimeInterval = 5000;
    }

    _HOTKEY_CFG(QVariant vars[5])
    {
        vkNext = vars[next].toULongLong();
        vkStop = vars[stop].toULongLong();
        vkKey1 = vars[key1].toULongLong();
        vkKey2 = vars[key2].toULongLong();
        nTimeInterval = vars[interval].toInt();
    }

    QKeySequence toKey(int key)
    {
        int* pKeys[] = { &vkNext, &vkStop, &vkKey1, &vkKey2 };
        return QKeySequence(*pKeys[key]);
    }

    bool press(int key)
    {
        int* pKeys[] = { &vkNext, &vkStop, &vkKey1, &vkKey2 };

        CGKeyCode vk; bool bAlt, bShift, bCtrl, bCommand;

        vk = toCGKeyCode((Qt::Key)(*pKeys[key] & 0xff));
        bAlt = *pKeys[key] & Qt::ALT;
        bShift = *pKeys[key] & Qt::SHIFT;
        bCtrl = *pKeys[key] & Qt::MetaModifier;
        bCommand = *pKeys[key] & Qt::CTRL;

        if(0 == vk)
        {
            return false;
        }

        if(bAlt)      { KeybdEvent(kVK_Option,  true); }
        if(bShift)    { KeybdEvent(kVK_Shift,   true); }
        if(bCtrl)     { KeybdEvent(kVK_Control, true); }
        if(bCommand)  { KeybdEvent(kVK_Command, true); }

        Sleep(100);
        KeybdEvent(vk, true);
        Sleep(100);
        KeybdEvent(vk, false);
        Sleep(100);

        if(bAlt)      { KeybdEvent(kVK_Option,  false); }
        if(bShift)    { KeybdEvent(kVK_Shift,   false); }
        if(bCtrl)     { KeybdEvent(kVK_Control, false); }
        if(bCommand)  { KeybdEvent(kVK_Command, false); }

        return true;
    }
}HOTKEY_CFG, *PHOTKEY_CFG;

#endif
