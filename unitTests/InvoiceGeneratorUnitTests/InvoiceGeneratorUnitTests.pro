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

INCLUDEPATH += $$PWD/../../src/InvoiceGenerator

SOURCES += main.cpp

unix|win32: LIBS += -lcppunit
