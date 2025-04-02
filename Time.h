#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Time
{
public:
    Time();
    Time(int hour, int minute, int second);

    int GetHour() const;
    void SetHour(int hour);

    int GetMinute() const;
    void SetMinute(int minute);

    int GetSecond() const;
    void SetSecond(int second);

private:
    int m_hour;
    int m_minute;
    int m_second;
};

ostream & operator << (ostream & os, const Time & time);
istream & operator >> (istream & input, Time & time);

#endif // TIME_H_INCLUDED
