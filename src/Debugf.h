
#ifndef WKTESTSTUFF_DEBUGF_H
#define WKTESTSTUFF_DEBUGF_H

#include "Config.h"
#define debugf(fmt, ...) if(Config::isDevConsoleEnabled()) printf("%s:%d: " fmt, __FUNCTION__ , __LINE__, __VA_ARGS__);

#endif //WKTESTSTUFF_DEBUGF_H
