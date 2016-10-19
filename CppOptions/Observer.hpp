//
//  Observer.hpp

#ifndef Observer_hpp
#define Observer_hpp

#include <set>
#include <memory>


class Observer {
public:
    Observer();
    Observer(const Observer &p);
    ~Observer();
    Observer &operator=(const Observer &p); // not implemented

    virtual void notify() = 0;

private:
    
};

class Trade {
    // ....
};

class TradingLedger;

class TradeObserver : public Observer {
public:
    TradeObserver(TradingLedger *t);
    TradeObserver(const TradeObserver &p);
    ~TradeObserver();
    TradeObserver &operator=(const TradeObserver &p);

    void notify();
    void processNewTrade();
private:
    Trade m_trade;
    TradingLedger *m_ledger;
};


class TradingLedger {
public:
    TradingLedger();
    TradingLedger(const TradingLedger &p);
    ~TradingLedger();
    TradingLedger &operator=(const TradingLedger &p);

    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);
    void triggerNotifications();

    void addTrade(const Trade &t);
    const Trade &getLastTrade();

private:
    std::set<std::shared_ptr<Observer>> m_observers;
    Trade m_trade;
};




#endif /* Observer_hpp */
