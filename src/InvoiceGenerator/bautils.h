#ifndef BAUTILS_H
#define BAUTILS_H

#include "batypes.h"
#include <QStringList>

namespace Utils
{
    GoodTypeList goodTypes();
    InvoiceTypeList invoiceTypes();
    InvoiceTypeFileList invoiceTypeFiles();
    QStringList dataBaseExtensions();
    TableNamesList tableNames();
}

#endif // BAUTILS_H
