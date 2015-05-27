#ifndef BATYPES_H
#define BATYPES_H

#include <QMap>
#include <QString>

enum GOOT_TYPE { GT_KG = 0, GT_NUM  = 1 };
enum INVOICE_TYPE { IT_NONE = 0, IT_SimpleInvoice = 1 };

typedef QMap<GOOT_TYPE, QString> GoodTypeList;
typedef QMap<INVOICE_TYPE, QString> InvoiceTypeList;
typedef QMap<INVOICE_TYPE, QString> InvoiceTypeFileList;

#endif // BATYPES_H
