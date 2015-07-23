#ifndef BAUTILS_H
#define BAUTILS_H

#include "batypes.h"
#include <QStringList>

namespace Utils
{
    GoodTypeList goodTypes();
    GoodTypeList invoiceGoodTypes();
    InvoiceTypeList invoiceTypes();
    InvoiceTypeFileList invoiceTypeFiles();
    QStringList dataBaseExtensions();
    TableNamesList tableNames();
    InvoiceHandlerCreators invoiceCreators();
}

#endif // BAUTILS_H
