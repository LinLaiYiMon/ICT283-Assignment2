#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include <string>

using std::ostream;
using std::istream;
using std::string;

class Date
{
public:
    Date();
    Date(int day, int month, int year);

    int GetDay() const;
    void SetDay(int day);

    int GetMonth() const;
    void SetMonth(int month);

    int GetYear() const;
    void SetYear(int year);

    bool operator< (const Date& other) const
    {
        if (m_year != other.m_year)
        {
            return m_year < other.m_year;
        }

        if (m_month != other.m_month)
        {
            return m_month < other.m_month;
        }

        return m_day < other.m_day;
    }

     bool operator> (const Date& other) const
    {
        if (m_year != other.m_year)
        {
            return m_year > other.m_year;
        }

        if (m_month != other.m_month)
        {
            return m_month > other.m_month;
        }

        return m_day > other.m_day;
    }

    bool operator == (const Date& other) const
    {
        return (m_day == other.m_day &&
        m_month == other.m_month && m_year == other.m_year);
    }


private:
    int m_day;
    int m_month;
    int m_year;
};

ostream & operator << (ostream & os, const Date & date);
istream & operator >> (istream & input, Date & date);

#endif // DATE_H_INCLUDED




