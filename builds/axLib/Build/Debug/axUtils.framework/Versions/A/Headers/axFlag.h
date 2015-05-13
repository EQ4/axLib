#ifndef __axUtils__axFlag__
#define __axUtils__axFlag__

#include <stdint.h>

namespace ax
{
    // Flag.
    typedef uint16_t Flag;
    
    bool IsFlag(const Flag& FLAG, Flag flags);
    
    namespace FlagValue
    {
        extern const Flag NO_FLAG;
        extern const Flag FLAG_1;
        extern const Flag FLAG_2;
        extern const Flag FLAG_3;
        extern const Flag FLAG_4;
        extern const Flag FLAG_5;
        extern const Flag FLAG_6;
        extern const Flag FLAG_7;
        extern const Flag FLAG_8;
        extern const Flag FLAG_9;
        extern const Flag FLAG_10;
        extern const Flag FLAG_11;
        extern const Flag FLAG_12;
        extern const Flag FLAG_13;
        extern const Flag FLAG_14;
        extern const Flag FLAG_15;
        extern const Flag FLAG_16;
    }
}

#endif /* defined(__axUtils__axFlag__) */
