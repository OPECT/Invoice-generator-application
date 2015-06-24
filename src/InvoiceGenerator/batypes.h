#ifndef BATYPES_H
#define BATYPES_H

#include <QMap>
#include <QString>

class BAState;

enum GOOT_TYPE { GT_KG = 0, GT_NUM  = 1 };
enum INVOICE_TYPE { IT_NONE = 0, IT_SimpleInvoice = 1 };

enum BUSSINESS_APPLICATION_STATE { BAS_START_UP = 0, BAS_CUSTOMERS_DB, BAS_GOODS_DB, BAS_INVOICE_LIST,
    BAS_INVOICE_GENERATION };
enum UI_EVENTS { UIE_EXIT = 0, UIE_BACK, UIE_STARTUP_PROCEED, UIE_OPEN_CUSTOMERS_DB, UIE_OPEN_GOODS_DB };

typedef QMap<GOOT_TYPE, QString> GoodTypeList;
typedef QMap<INVOICE_TYPE, QString> InvoiceTypeList;
typedef QMap<INVOICE_TYPE, QString> InvoiceTypeFileList;

typedef QMap<BUSSINESS_APPLICATION_STATE, BAState*>  ApplicationStates;

#endif // BATYPES_H
