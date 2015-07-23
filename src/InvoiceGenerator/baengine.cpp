#include "baengine.h"
#include "bastartupstate.h"
#include "messageboxerrorreport.h"
#include "qtcustomerdatabasewindow.h"
#include "qtgoodsdatabasewindow.h"
#include "qsqlcustomermodel.h"
#include "qsqlgoodsmodel.h"
#include "bamodifydbstate.h"
#include "bainvoiceliststate.h"

#include <QMapIterator>
#include <QApplication>

BAEngine::BAEngine() : m_dbType("QSQLITE"), m_dbHost("localhost")
{
    m_settings.propagateGeneralInfo(m_invoiceData);
    m_settings.propagateDBInfo(m_dataBaseData);
    prepareDataBase();

    if (!m_dbManager.isDataBaseReady())
    {
        return;
    }

    m_states[BAS_START_UP] = new BAStartUpState(*this, m_window);
    m_states[BAS_CUSTOMERS_DB] = new BAModifyDBState<QTCustomerDataBaseWindow, QSQLCustomerModel,
        TN_CUSTOMERS>(*this, m_window);
    m_states[BAS_GOODS_DB] = new BAModifyDBState<QTGoodsDataBaseWindow, QSQLGoodsModel, TN_GOODS>(*this, m_window);
    m_states[BAS_INVOICE_LIST] = new BAInvoiceListState(*this, m_window);
}

BAEngine::~BAEngine()
{
    QMapIterator<BUSSINESS_APPLICATION_STATE, BAState*> iter(m_states);
    while(iter.hasNext())
    {
        delete iter.next().value();
    }
}

void BAEngine::run()
{
    if (!m_dbManager.isDataBaseReady() || !m_dbManager.isTableExist(Utils::tableNames()[TN_GOODS]) ||
        !m_dbManager.isTableExist(Utils::tableNames()[TN_CUSTOMERS]))
    {
        QApplication::exit();
    }
    m_states[BAS_START_UP]->start(m_window);
    m_window.show();
}

void BAEngine::switchState(BUSSINESS_APPLICATION_STATE state)
{
    m_states[state]->start(m_window);
}

void BAEngine::reopenDataBase()
{
    if (!m_dbManager.reopenDB(m_dbType, m_dbHost, m_dataBaseData.dataBaseFile(), m_dataBaseData.userName(),
        m_dataBaseData.password()))
    {
        MessageBoxErrorReport report;
        report.reportError("Can't reopen data base");
        return;
    }
    prepareDataBaseTables();
    notifyAll(ASE_DATA_BASE_REOPENED);
}

void BAEngine::notifyAll(ALL_STATES_EVENTS event)
{
    QMapIterator<BUSSINESS_APPLICATION_STATE, BAState*> iter(m_states);
    while(iter.hasNext())
    {
        iter.next().value()->notify(event);
    }
}

void BAEngine::prepareDataBase()
{
    if (!m_dbManager.openDB(m_dbType, m_dbHost, m_dataBaseData.dataBaseFile(), m_dataBaseData.userName(),
                       m_dataBaseData.password()))
    {
        MessageBoxErrorReport report;
        report.reportError("Can't open database");
        return;
    }
    prepareDataBaseTables();
}

void BAEngine::prepareDataBaseTables()
{
    if (!m_dbManager.isTableExist(Utils::tableNames()[TN_GOODS]))
    {
        QStringList attributes;
        attributes << m_dataBaseData.idColumn() << m_dataBaseData.goodNameColumn() << m_dataBaseData.goodTypeColumn()
                   << m_dataBaseData.goodCategoryColumn() << m_dataBaseData.goodPriceColumn();
        if (!m_dbManager.createTable(Utils::tableNames()[TN_GOODS], attributes))
        {
            MessageBoxErrorReport report;
            report.reportError("Can't create goods table");
            return;
        }
    }
    if (!m_dbManager.isTableExist(Utils::tableNames()[TN_CUSTOMERS]))
    {
        QStringList attributes;
        attributes << m_dataBaseData.idColumn() << m_dataBaseData.customerNameColumn() <<
                      m_dataBaseData.customerRegionColumn() << m_dataBaseData.customerMultiplierColumn();
        if (!m_dbManager.createTable(Utils::tableNames()[TN_CUSTOMERS], attributes))
        {
            MessageBoxErrorReport report;
            report.reportError("Can't create customer table");
            return;
        }
    }
}
