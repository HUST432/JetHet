#include "PreDefinations.h"
#include <algorithm>
string& PreDefinations::toLowerCase(string& tgt)
{
    transform(tgt.begin(), tgt.end(), tgt.begin(), ::tolower);
    return tgt;
}
