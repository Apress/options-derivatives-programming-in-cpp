//
//  Observer.cpp

#include "Observer.hpp"

using std::shared_ptr;

typedef shared_ptr<Observer> PObserver;
typedef shared_ptr<TradeObserver> PTradeObserver;

Observer::Observer()
{
}

Observer::Observer(const Observer &p)
{
}

Observer::~Observer()
{
}

void Observer::notify()
{
}

TradeObserver::TradeObserver(TradingLedger *t)
: m_ledger(t)
{
}

TradeObserver::TradeObserver(const TradeObserver &p)
: m_trade(p.m_trade),
  m_ledger(p.m_ledger)
{
}

TradeObserver::~TradeObserver()
{
}

TradeObserver &TradeObserver::operator=(const TradeObserver &p)
{
    if (this != &p)
    {
        m_trade = p.m_trade;
        m_ledger = p.m_ledger;
    }
    return *this;
}

void TradeObserver::notify()
{
    this->processNewTrade();
}

void TradeObserver::processNewTrade()
{
    m_trade = m_ledger->getLastTrade();
    // do trading processing here
}


//

TradingLedger::TradingLedger()
{
}

TradingLedger::TradingLedger(const TradingLedger &p)
: m_observers(p.m_observers),
  m_trade(p.m_trade)
{
}

TradingLedger::~TradingLedger()
{
}

TradingLedger &TradingLedger::operator=(const TradingLedger &p)
{
    if (this != &p)
    {
        m_observers = p.m_observers;
        m_trade = p.m_trade;
    }
    return *this;
}

void TradingLedger::addObserver(PObserver observer)
{
    m_observers.insert(observer);
}

void TradingLedger::removeObserver(PObserver observer)
{
    if (m_observers.find(observer) != m_observers.end())
    {
        m_observers.erase(observer);
    }
}

void TradingLedger::triggerNotifications()
{
    for (auto i : m_observers)
    {
        i->notify();
    }
}

void TradingLedger::addTrade(const Trade &t)
{
    m_trade = t;
    this->triggerNotifications();
}

const Trade &TradingLedger::getLastTrade()
{
    return m_trade;
}

int main_obs()
{
    TradingLedger tl;
    PTradeObserver observer1 = PTradeObserver(new TradeObserver(&tl));
    PTradeObserver observer2 = PTradeObserver(new TradeObserver(&tl));
    tl.addObserver(observer1);
    tl.addObserver(observer2);

    // perform trading system here

    Trade aTrade;
    tl.addTrade(aTrade);

    // observers should receive a notification at this point
    return 0;
}
