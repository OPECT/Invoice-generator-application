#include "bautils.h"

namespace Utils
{
    GoodTypeList goodTypes()
    {
        GoodTypeList types;

        types[GT_NUM] = "num.";
        types[GT_KG] = "kg";

        return types;
    }
}
