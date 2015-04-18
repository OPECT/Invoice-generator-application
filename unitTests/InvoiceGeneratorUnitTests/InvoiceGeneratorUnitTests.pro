#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T22:07:32
#
#-------------------------------------------------

QT       += core xlsx

QT       -= gui

TARGET = InvoiceGeneratorInvoice
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix|win32: LIBS += -lcppunit

INCLUDEPATH += $$PWD/../../src/InvoiceGenerator

SOURCES += main.cpp \
    invoicedatasuite.cpp \
    documentwrappertestsuite.cpp \
    xlsinvoicevalidatortestsuite.cpp \
    xlsdocumentbuildertestsuite.cpp \
    initialsettingstestsuite.cpp \
    unittestpurposeerrorreport.cpp

HEADERS += invoicedatasuite.h \
    documentwrappertestsuite.h \
    xlsinvoicevalidatortestsuite.h \
    xlsdocumentbuildertestsuite.h \
    unittestpurposeerrorreport.h \
    initialsettingstestsuite.h \
    unittestpurposeinitialsettings.h


SOURCES += ../../src/InvoiceGenerator/invoicedata.cpp \
    ../../src/InvoiceGenerator/invoiceitem.cpp \
    ../../src/InvoiceGenerator/xlsdocumentwrapper.cpp \
    ../../src/InvoiceGenerator/xlsstandardinvoicevalidator.cpp \
    ../../src/InvoiceGenerator/xlstandardinvoiceformatbuilder.cpp \
    ../../src/InvoiceGenerator/docinvoicebuilder.cpp \
    ../../src/InvoiceGenerator/initialsettings.cpp \
    ../../src/InvoiceGenerator/generalinvoicedata.cpp \
    ../../src/InvoiceGenerator/databasedata.cpp

HEADERS +=  ../../src/InvoiceGenerator/invoicedata.h \
    ../../src/InvoiceGenerator/invoiceitem.h \
    ../../src/InvoiceGenerator/xlsdocumentwrapper.h \
    ../../src/InvoiceGenerator/xlsstandardinvoicevalidator.h \
    ../../src/InvoiceGenerator/xlstandardinvoiceformatbuilder.h \
    ../../src/InvoiceGenerator/docinvoicebuilder.h \
    ../../src/InvoiceGenerator/initialsettings.h
