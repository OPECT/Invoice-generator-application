#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T22:05:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InvoiceGenerator
TEMPLATE = app


SOURCES += main.cpp\
    invoiceitem.cpp \
    invoicedata.cpp \
    generalinvoicedata.cpp \
    databasedata.cpp \
    messageboxerrorreport.cpp

HEADERS  += invoiceitem.h \
    invoicedata.h \
    generalinvoicedata.h \
    databasedata.h \
    errorreport.h \
    messageboxerrorreport.h
