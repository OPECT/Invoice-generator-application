#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T22:05:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xlsx

TARGET = InvoiceGenerator
TEMPLATE = app

TRANSLATIONS = InvoiceGenerator_ua.ts

SOURCES += main.cpp \
    invoiceitem.cpp \
    invoicedata.cpp \
    generalinvoicedata.cpp \
    databasedata.cpp \
    messageboxerrorreport.cpp \
    qtadddatadialog.cpp \
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
    pricecalculationwithdiscount.cpp \
    qtaddgooditemdialog.cpp \
    bautils.cpp \
    qtaddcustomerdialog.cpp \
    qtwindowbase.cpp \
    qtstartupwindow.cpp \
    qtdatabasewindow.cpp \
    qtcustomerdatabasewindow.cpp \
    qtgoodsdatabasewindow.cpp \
    mainwindow.cpp \
    baengine.cpp \
    bastate.cpp \
    bastartupstate.cpp \
    bamodifydbbasestate.cpp \
    qtinvoicelistwindow.cpp \
    bainvoiceliststate.cpp

HEADERS  += invoiceitem.h \
    invoicedata.h \
    generalinvoicedata.h \
    databasedata.h \
    errorreport.h \
    messageboxerrorreport.h \
    qtadddatadialog.h \
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
    pricecalculationwithdiscount.h \
    qtaddgooditemdialog.h \
    bautils.h \
    badefines.h \
    qtaddcustomerdialog.h \
    qtwindowbase.h \
    qtstartupwindow.h \
    batypes.h \
    qtdatabasewindow.h \
    qtcustomerdatabasewindow.h \
    qtgoodsdatabasewindow.h \
    mainwindow.h \
    baengine.h \
    bastate.h \
    bastartupstate.h \
    bamodifydbstate.h \
    bamodifydbbasestate.h \
    qtinvoicelistwindow.h \
    bainvoiceliststate.h

FORMS += \
    mainwindow.ui
