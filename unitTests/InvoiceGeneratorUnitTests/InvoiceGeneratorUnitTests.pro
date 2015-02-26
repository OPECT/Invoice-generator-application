#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T22:07:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = InvoiceGeneratorInvoice
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix|win32: LIBS += -lcppunit

INCLUDEPATH += $$PWD/../../src/InvoiceGenerator

SOURCES += main.cpp \
    invoicedatasuite.cpp

HEADERS += invoicedatasuite.h


SOURCES += ../../src/InvoiceGenerator/invoicedata.cpp \
    ../../src/InvoiceGenerator/invoiceitem.cpp

HEADERS +=  ../../src/InvoiceGenerator/invoicedata.h \
    ../../src/InvoiceGenerator/invoiceitem.h
