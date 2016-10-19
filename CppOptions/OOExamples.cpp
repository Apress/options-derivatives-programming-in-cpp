//
//  OOExamples.cpp

#include "OOExamples.h"


double GeneralDerivative::strike()
{
    return m_strike;
}


double CDSContract::kStandardPayoff = 1000.0;

void CDSContract::setCounterpart(const std::string &s)
{
    m_counterpart = s;
    setPayoff(kStandardPayoff);
}

double CDSContract::computeCurrentValue(const Date &d)
{
    if (!counterpart().empty())
    {
        processCreditEvent(); // make sure there is no credit event;
    }
    return 0; //calculateInternalValue();
}

void LoanOnlyCDSContract::processCreditEvent()
{
}


double LoanOnlyCDSContract::computeCurrentValue(const Date &d)
{
    return 0;
}

CDSContract *createSimpeleContract()
{
    CDSContract *contract = new LoanOnlyCDSContract();
    contract->setCounterpart("IBM");
    return contract;
}


void useContract(bool isLOContract, Date &currentDate)
{
    CDSContract *contract = nullptr;
    if (isLOContract)
    {
        contract = new LoanOnlyCDSContract();
    }
    else
    {
        //contract = new CDSContract(); // normal CDS contract
    }

    contract->computeCurrentValue(currentDate);
    delete contract;
}

void useBasePtr(CDSContract *contract, Date &currentDate)
{
    contract->computeCurrentValue(currentDate);
    delete contract;
}

void callBasePtr()
{
    Date date(1,1,2010);
    useBasePtr(new LoanOnlyCDSContract(), date);
}

int main_ooe()
{
    Date date(1,1,2010);
    //useContract(true, date);
    useBasePtr(new LoanOnlyCDSContract(), date);
    return 0;
}
