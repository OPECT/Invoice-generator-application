#include "baengine.h"
#include "bastartupstate.h"

#include <QMapIterator>

BAEngine::BAEngine()
{
    m_settings.propagateGeneralInfo(m_invoiceData);

    m_states[BAS_START_UP] = new BAStartUpState(*this, m_window);
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
    m_states[BAS_START_UP]->start(m_window);
    m_window.show();
}

void BAEngine::swithcState(BUSSINESS_APPLICATION_STATE state)
{

}
