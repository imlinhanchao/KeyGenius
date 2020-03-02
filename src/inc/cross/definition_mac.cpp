#include "definition_mac.h"

#ifdef Q_OS_MAC
CGKeyCode toCGKeyCode(Qt::Key k){
    switch(k){
        case Qt::Key_0:
            return kVK_ANSI_0;
        case Qt::Key_1:
            return kVK_ANSI_1;
        case Qt::Key_2:
            return kVK_ANSI_2;
        case Qt::Key_3:
            return kVK_ANSI_3;
        case Qt::Key_4:
            return kVK_ANSI_4;
        case Qt::Key_5:
            return kVK_ANSI_5;
        case Qt::Key_6:
            return kVK_ANSI_6;
        case Qt::Key_7:
            return kVK_ANSI_7;
        case Qt::Key_8:
            return kVK_ANSI_8;
        case Qt::Key_9:
            return kVK_ANSI_9;
        case Qt::Key_Q:
            return kVK_ANSI_Q;
        case Qt::Key_W:
            return kVK_ANSI_W;
        case Qt::Key_E:
            return kVK_ANSI_E;
        case Qt::Key_R:
            return kVK_ANSI_R;
        case Qt::Key_T:
            return kVK_ANSI_T;
        case Qt::Key_Y:
            return kVK_ANSI_Y;
        case Qt::Key_U:
            return kVK_ANSI_U;
        case Qt::Key_I:
            return kVK_ANSI_I;
        case Qt::Key_O:
            return kVK_ANSI_O;
        case Qt::Key_P:
            return kVK_ANSI_P;
        case Qt::Key_A:
            return kVK_ANSI_A;
        case Qt::Key_S:
            return kVK_ANSI_S;
        case Qt::Key_D:
            return kVK_ANSI_D;
        case Qt::Key_F:
            return kVK_ANSI_F;
        case Qt::Key_G:
            return kVK_ANSI_G;
        case Qt::Key_H:
            return kVK_ANSI_H;
        case Qt::Key_J:
            return kVK_ANSI_J;
        case Qt::Key_K:
            return kVK_ANSI_K;
        case Qt::Key_L:
            return kVK_ANSI_L;
        case Qt::Key_Z:
            return kVK_ANSI_Z;
        case Qt::Key_X:
            return kVK_ANSI_X;
        case Qt::Key_C:
            return kVK_ANSI_C;
        case Qt::Key_V:
            return kVK_ANSI_V;
        case Qt::Key_B:
            return kVK_ANSI_B;
        case Qt::Key_N:
            return kVK_ANSI_N;
        case Qt::Key_M:
            return kVK_ANSI_M;
        case Qt::Key_F1:
            return kVK_F1;
        case Qt::Key_F2:
            return kVK_F2;
        case Qt::Key_F3:
            return kVK_F3;
        case Qt::Key_F4:
            return kVK_F4;
        case Qt::Key_F5:
            return kVK_F5;
        case Qt::Key_F6:
            return kVK_F6;
        case Qt::Key_F7:
            return kVK_F7;
        case Qt::Key_F8:
            return kVK_F8;
        case Qt::Key_F9:
            return kVK_F9;
        case Qt::Key_F10:
            return kVK_F10;
        case Qt::Key_F11:
            return kVK_F11;
        case Qt::Key_F12:
            return kVK_F12;
        case Qt::Key_Left:
            return kVK_LeftArrow;
        case Qt::Key_Right:
            return kVK_RightArrow;
        case Qt::Key_Down:
            return kVK_DownArrow;
        case Qt::Key_Up:
            return kVK_UpArrow;
        case Qt::Key_Return:
            return kVK_Return;
        case Qt::Key_Tab:
            return kVK_Tab;
        case Qt::Key_Space:
            return kVK_Space;
        case Qt::Key_Delete:
            return kVK_Delete;
        case Qt::Key_Escape:
            return kVK_Escape;
        case Qt::Key_Shift:
            return kVK_Shift;
        case Qt::Key_Control:
            return kVK_Control;
        case Qt::Key_CapsLock:
            return kVK_CapsLock;
        default:
            return kVK_Escape;
     }
}

unsigned int Sleep(unsigned int m) { return usleep(m * 1000); }

void KeybdEvent(CGKeyCode key, bool bkeydown)
{
    CGEventRef mkey = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)key, bkeydown);
    CGEventPost(kCGHIDEventTap, mkey);
    CFRelease(mkey);
}
#endif
