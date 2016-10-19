//
//  DateCompact.cpp
//
//  Implementation for the DateCompact class

#include "DateCompact.h"

#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

DateCompact::DateCompact(int year, int month, int day)
{
    setYear(year);
    setMonth(month);
    setDay(day);
}

DateCompact::DateCompact(const DateCompact &p)
{
    strcpy(m_date, p.m_date);
}

DateCompact::~DateCompact()
{
}

DateCompact &DateCompact::operator=(const DateCompact &p)
{
    if (&p != this)
    {
        strcpy(m_date, p.m_date);
    }
    return *this;
}

//
// Use string comparison to determine if the dates are equal
//
bool DateCompact::operator==(const DateCompact &d) const
{
    return strncmp(m_date, d.m_date, 8) == 0;
}

// Use the strncmp function to determine if a date is less than the other.
bool DateCompact::operator<(const DateCompact &d) const
{
    // strcmp returns negative values if the first argument is less than the second.
    return strncmp(m_date, d.m_date, 8) < 0;
}

//
// Functions to calculate the year, month, and days as an integers,
// based on the characters contained in the string 'm_date'.
//

int DateCompact::year()
{
    // (x - '0')  computes the numeric value corresponding to the each character.
    return  1000 * (m_date[0] - '0') + 100 * (m_date[1] - '0') + 10 * (m_date[2] - '0') +  (m_date[3] - '0');
}

int DateCompact::month()
{
    return  10 * (m_date[4] - '0') +  (m_date[5] - '0');
}

int DateCompact::day()
{
    return  10 * (m_date[6] - '0') +  (m_date[7] - '0');
}

void DateCompact::print()
{
    // copy the m_date string into a NULL terminated string (with 9 characters).
    char s[9];
    strncpy(s, m_date, 8);
    s[8] = '\0';             // properly terminate the string
    cout << s << endl;
}

//
// calculate the string corresponding to the given numeric parameter.
//

void DateCompact::setYear(int year)
{
    m_date[3] = '0' + (year % 10);
    year /= 10;
    m_date[2] = '0' + (year % 10);
    year /= 10;
    m_date[1] = '0' + (year % 10);
    year /= 10;
    m_date[0] = '0' + (year % 10);
}

void DateCompact::setMonth(int month)
{
    m_date[5] = '0' + (month % 10);  month /= 10;
    m_date[4] = '0' + (month % 10);

}

void DateCompact::setDay(int day)
{
    m_date[7] = '0' + (day % 10);  day /= 10;
    m_date[6] = '0' + (day % 10);
}


#include "Date.h"


int main_dtc()
//int main()
{
    DateCompact d(2008, 3, 17);
    DateCompact e(2008, 5, 11);
    cout << " size of DateCompact: " << sizeof(DateCompact) << endl;

    d.print();
    e.print();

    if (d < e)
    {
        cout << " d is less than e " << endl;
    }
    else
    {
        cout << " d is not less than e " << endl;
    }

    Date date(2008, 3, 17);
    cout << " size of Date: " << sizeof(Date) << endl;

    return 0;
}

