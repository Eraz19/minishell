#include "expander_.h"

bool    flag_is_active(uint bitset, uint flag)
{
    return ((bitset & flag) != 0);
}
