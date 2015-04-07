#ifndef DOCSTANDARDXLFORMATHANDLER_H
#define DOCSTANDARDXLFORMATHANDLER_H

class XLStandardInvoiceFormatBuilder
{
public:
    enum ItemColumnValue { ICV_GOOD_ID = 1, ICV_GOOD_NAME = 2, ICV_GOOD_TYPE = 6, ICV_GOOD_QUANTITY = 7,
                           ICV_GOOD_PRICE = 8, ICV_GOOD_TOTAL = 9 };
    enum GeneralDataRow { GDR_SUPPLIER = 1, GDR_RECIPIENT = 8, GDR_PAYER = 10, GDR_INVOICE_ID = 12,
                           GDR_DATE = 14 };
    enum GeneralDataColumn { GDC_GENERAL = 4, GDC_INVOICE_ID = 7, GDC_DATE = 4 };
};

#endif // DOCSTANDARDXLFORMATHANDLER_H
