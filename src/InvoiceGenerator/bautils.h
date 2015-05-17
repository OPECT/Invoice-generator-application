#ifndef BAUTILS_H
#define BAUTILS_H

#include <QString>
#include <QHash>

namespace Utils
{
    enum GOOT_TYPE { GT_KG = 0, GT_NUM  = 1 };
    typedef QHash<GOOT_TYPE, QString> GoodTypeList;

    GoodTypeList goodTypes();
}

#endif // BAUTILS_H
