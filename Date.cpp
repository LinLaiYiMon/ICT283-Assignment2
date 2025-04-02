#include "Date.h"

Date::Date()
{
    m_day = 0;
    m_month = 0;
    m_year = 0;
}

Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

int Date::GetDay() const
{
    return m_day;
}

void Date::SetDay(int day)
{
    m_day = day;
}
int Date::GetMonth() const
{
    return m_month;
}

void Date::SetMonth(int month)
{
    m_month = month;
}

int Date::GetYear() const
{
    return m_year;
}

void Date::SetYear(int year)
{
    m_year = year;
}

ostream & operator << (ostream & os, const Date & date)
{
    os << "Date: " << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear() << '\n';
    return os;
}

istream & operator >> (istream & input, Date & date)
{
    int day;
    int month;
    int year;

    input >> day;
    date.SetDay(day);

    input >> month;
    date.SetMonth(month);

    input >> year;
    date.SetYear(year);

    return input;
}
