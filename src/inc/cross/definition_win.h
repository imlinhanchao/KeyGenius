#pragma once

#include <QSettings>
#include <QKeySequence>

#include <windows.h>
#include <commctrl.h>


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
        vkNext = Qt::Key_C + Qt::ALT;
        vkStop = Qt::Key_F2 + Qt::CTRL;
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

        BYTE vk; bool bAlt, bShift, bCtrl;

        vk = *pKeys[key] & 0xff;
        bAlt = *pKeys[key] & Qt::ALT;
        bShift = *pKeys[key] & Qt::SHIFT;
        bCtrl = *pKeys[key] & Qt::CTRL;

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
}HOTKEY_CFG, *PHOTKEY_CFG;
