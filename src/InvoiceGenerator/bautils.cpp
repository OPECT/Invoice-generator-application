#include "bautils.h"

namespace Utils
{
    GoodTypeList goodTypes()
    {
        GoodTypeList types;

        types[GT_KG] = QT_TRANSLATE_NOOP("QTAddGoodItemDialog", "kg");
        types[GT_NUM] = QT_TRANSLATE_NOOP("QTAddGoodItemDialog", "num.");

        return types;
    }

    InvoiceTypeList invoiceTypes()
    {
        InvoiceTypeList types;

        types[IT_NONE] = QT_TRANSLATE_NOOP("QTStartUpWindow", "None");
        types[IT_SimpleInvoice] = QT_TRANSLATE_NOOP("QTStartUpWindow", "Standard Invoice");

        return types;
    }

    InvoiceTypeFileList invoiceTypeFiles()
    {
        InvoiceTypeFileList files;

        files[IT_NONE] = "";
        files[IT_SimpleInvoice] = "standardInvoice.xlsx";

        return files;
    }
    QStringList dataBaseExtensions()
    {
        QStringList extenstionList;
        extenstionList.append(".badb");
        return extenstionList;
    }
    TableNamesList tableNames()
    {
        TableNamesList list;
        list[TN_CUSTOMERS] = "Customers";
        list[TN_GOODS] = "Goods";
        return list;
    }
}
