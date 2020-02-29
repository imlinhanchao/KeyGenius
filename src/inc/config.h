#ifndef CONFIG_H
#define CONFIG_H
#include "cross/cross.h"

class Config
{
public:
    Config();

    static HOTKEY_CFG GetConfig(void);
    static void SetConfig(HOTKEY_CFG cfg);

};



#endif // CONFIG_H
