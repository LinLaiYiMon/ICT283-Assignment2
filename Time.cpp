#include "Time.h"

Time::Time()
{
    m_hour = 0;
    m_minute = 0;
    m_second = 0;
}

Time::Time(int hour, int minute, int second)
{
    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

int Time::GetHour() const
{
    return m_hour;
}

void Time::SetHour(int hour)
{
    m_hour = hour;
}

int Time::GetMinute() const
{
    return m_minute;
}

void Time::SetMinute(int minute)
{
    m_minute = minute;
}

int Time::GetSecond() const
{
    return m_second;
}

void Time::SetSecond(int second)
{
    m_second = second;
}

ostream & operator << (ostream & os, const Time & time)
{
    os << "Time: " << time.GetHour() << "h " <<
    time.GetMinute() << "min " << time.GetSecond() << "s" << '\n';

    return os;
}

istream & operator >> (istream & input, Time & time)
{
    int hour;
    int minute;
    int second;

    input >> hour;
    time.SetHour(hour);

    input >> minute;
    time.SetMinute(minute);

    input >> second;
    time.SetSecond(second);

    return input;
}
