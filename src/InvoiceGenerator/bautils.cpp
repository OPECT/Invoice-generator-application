#include "bautils.h"

namespace Utils
{
    GoodTypeList goodTypes()
    {
        GoodTypeList types;

        types[GT_KG] = "kg";
        types[GT_NUM] = "num.";

        return types;
    }

    InvoiceTypeList invoiceTypes()
    {
        InvoiceTypeList types;

        types[IT_NONE] = "None";
        types[IT_SimpleInvoice] = "Standard Invoice";

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
