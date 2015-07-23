#include "bainvoiceliststate.h"
#include "baengine.h"
#include "bautils.h"
#include "mainwindow.h"
#include "qtinvoicelistwindow.h"
#include "invoicedata.h"
#include "messageboxerrorreport.h"
#include "invoicehandlercreator.h"
#include "docinvoicebuilder.h"

BAInvoiceListState::BAInvoiceListState(BAEngine& engine, MainWindow& wnd) : BAState(engine)
{
    m_window = new QTInvoiceListWindow(m_windowTitle, m_invoiceList);
    wnd.addWindow(m_window);

    connect(m_window, SIGNAL(invoiceListEvents(UI_EVENTS, QVariant)), this, SLOT(handle(UI_EVENTS, QVariant)));
}

BAInvoiceListState::~BAInvoiceListState()
{
    delete m_window;
}

void BAInvoiceListState::start(MainWindow& wnd)
{
    m_window->show();
    wnd.showWindow(m_window);
}

void BAInvoiceListState::notify(ALL_STATES_EVENTS event)
{
    switch(event)
    {
    case ASE_DATA_BASE_REOPENED:
        m_invoiceList.clear();
        break;
    default:
        break;
    }
}

void BAInvoiceListState::handle(UI_EVENTS event, QVariant data)
{
    MessageBoxErrorReport report;

    switch(event)
    {
    case UIE_BACK:
        m_engine.switchState(BAS_START_UP);
        break;
    case UIE_GENERATE_INVOICE:
        generateDocument(data.toString());
        break;
    case UIE_ADD_NEW_INVOICE:
    case UIE_EDIT_INVOICE:
    default:
        report.reportError("Error in InvoiceList state");
    }
}

void BAInvoiceListState::generateDocument(const QString& file)
{
    const GeneralInvoiceData& generalData = m_engine.invoiceData();
    InvoiceHandlerCreators creator = Utils::invoiceCreators();
    DocInvoiceBuilder& builder = creator[generalData.invoiceType()]->createHandler();

    if (!builder.createDocument(file))
    {
        return;
    }
    InvoiceListIterator iter(m_invoiceList);
    while (iter.hasNext())
    {
        const InvoiceData& data = iter.next();
        if (!builder.addInvoicePage(data.customerName(), data.invoiceID(), generalData.date()))
        {
            continue;
        }
        InvoiceItemsIterator itemIter(data.getGoodsList());
        while(itemIter.hasNext())
        {
            const InvoiceItem& item = itemIter.next();
            builder.addInvoiceItem(item.name(), tr(Utils::invoiceGoodTypes().value(item.quantityType())
                                                   .toStdString().c_str()),
                                   item.quantity(), item.goodPrice(), item.totalPrice());
        }
        builder.addInvoideSummary();
    }
    builder.saveDocument(true);
}
