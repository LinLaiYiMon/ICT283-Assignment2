#ifndef WEATHERDATA_H_INCLUDED
#define WEATHERDATA_H_INCLUDED

#include <iostream>
#include <string>
#include "Date.h"
#include "Time.h"

using namespace std;

class WeatherData
{
public:
    WeatherData();

    float GetSpeed() const;
    void SetSpeed(float speed);

    float GetAirTemp() const;
    void SetAirTemp(float airTemp);

    float GetSolarRad() const;
    void SetSolarRad(float solarRad);

    void GetDate(Date & date) const;
    void SetDate(const Date & date);

    bool operator<(const WeatherData& other) const
    {
        return this->GetSpeed() < other.GetSpeed();
    }

    bool operator>(const WeatherData& other) const
    {
        return this->GetSpeed() > other.GetSpeed();
    }

    bool operator==(const WeatherData& other) const
    {
        return this->GetSpeed() == other.GetSpeed();
    }

private:
    float m_speed;
    float m_airTemp;
    float m_solarRad;
    Date m_date; // date is already constructed
};

#endif // WEATHERDATA_H_INCLUDED
