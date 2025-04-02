#include "WeatherData.h"

WeatherData::WeatherData()
{
    m_speed = 0;
    m_airTemp = 0;
    m_solarRad = 0;
}

float WeatherData::GetSpeed() const
{
    return m_speed;
}

void WeatherData::SetSpeed(float speed)
{
    m_speed = speed;
}

float WeatherData::GetAirTemp() const
{
    return m_airTemp;
}

void WeatherData::SetAirTemp(float airTemp)
{
    m_airTemp = airTemp;
}

float WeatherData::GetSolarRad() const
{
    return m_solarRad;
}

void WeatherData::SetSolarRad(float solarRad)
{
    m_solarRad = solarRad;
}

void WeatherData::GetDate(Date & date) const
{
    date = m_date;
}

void WeatherData::SetDate(const Date & date)
{
    m_date = date;
}



