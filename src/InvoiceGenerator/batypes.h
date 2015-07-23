#ifndef BATYPES_H
#define BATYPES_H

#include <QMap>
#include <QList>
#include <QString>

class BAState;
class InvoiceData;
class InvoiceItem;
class InvoiceHandlerCreator;

enum GOOT_TYPE { GT_KG = 0, GT_NUM  = 1 };
enum INVOICE_TYPE { IT_NONE = 0, IT_SimpleInvoice = 1 };

enum BUSSINESS_APPLICATION_STATE { BAS_START_UP = 0, BAS_CUSTOMERS_DB, BAS_GOODS_DB, BAS_INVOICE_LIST,
    BAS_INVOICE_GENERATION };
enum UI_EVENTS { UIE_EXIT = 0, UIE_BACK, UIE_STARTUP_PROCEED, UIE_OPEN_CUSTOMERS_DB, UIE_OPEN_GOODS_DB,
                 UIE_NEW_DATABASE_LOADED, UIE_DATA_BASE_SAVED, UIE_GENERATE_INVOICE, UIE_ADD_NEW_INVOICE,
                 UIE_EDIT_INVOICE };
enum ALL_STATES_EVENTS { ASE_DATA_BASE_REOPENED = 0 };

enum TABLE_NAMES { TN_CUSTOMERS = 0, TN_GOODS };

typedef QMap<GOOT_TYPE, QString> GoodTypeList;
typedef QMap<INVOICE_TYPE, QString> InvoiceTypeList;
typedef QMap<INVOICE_TYPE, QString> InvoiceTypeFileList;
typedef QMap<INVOICE_TYPE, InvoiceHandlerCreator*> InvoiceHandlerCreators;
typedef QMap<TABLE_NAMES, QString> TableNamesList;

typedef QMap<BUSSINESS_APPLICATION_STATE, BAState*>  ApplicationStates;

typedef QList<InvoiceData> InvoiceList;
typedef QList<InvoiceItem> InvoiceDataList;

typedef QListIterator<InvoiceData> InvoiceListIterator;
typedef QListIterator<InvoiceItem> InvoiceItemsIterator;

#endif // BATYPES_H
