#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T22:05:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xlsx

TARGET = InvoiceGenerator
TEMPLATE = app


SOURCES += main.cpp\
    invoiceitem.cpp \
    invoicedata.cpp \
    generalinvoicedata.cpp \
    databasedata.cpp \
    messageboxerrorreport.cpp \
    qtadddatadialog.cpp \
    qtaddcategorydialog.cpp \
    qteditboxline.cpp \
    xlsdocumentwrapper.cpp \
    xlsstandardinvoicevalidator.cpp \
    standardxlsformatinvoicehandlercreator.cpp \
    xlstandardinvoiceformatbuilder.cpp \
    docinvoicebuilder.cpp \
    qsqlgoodsmodel.cpp \
    qsqlcustomermodel.cpp \
    initialsettings.cpp \
    tablehandler.cpp \
    databasemanager.cpp \
    pricecalculation.cpp \
    pricecalculationwithdiscount.cpp

HEADERS  += invoiceitem.h \
    invoicedata.h \
    generalinvoicedata.h \
    databasedata.h \
    errorreport.h \
    messageboxerrorreport.h \
    invoicedatalimitations.h \
    qtadddatadialog.h \
    qtaddcategorydialog.h \
    qteditboxline.h \
    invoicehandlercreator.h \
    standardxlsformatinvoicehandlercreator.h \
    docinvoicebuilder.h \
    xlstandardinvoiceformatbuilder.h \
    xlsdocumentwrapper.h \
    invoicedocumentwrapper.h \
    invoicetemplatevalidator.h \
    xlsstandardinvoicevalidator.h \
    qsqlgoodsmodel.h \
    qsqlcustomermodel.h \
    initialsettings.h \
    tablehandler.h \
    databasemanager.h \
    pricecalculation.h \
    pricecalculationwithdiscount.h
