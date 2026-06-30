#include "expander_.h"

bool    flag_is_active(int bitset, int flag)
{
    return ((bitset & flag) != 0);
}
