#include <iostream>
#include <cmath>

#include "BinarySearchTree.h"
#include "WeatherData.h"
#include "DataCalculations.h"

using namespace std;

float* DataCalculations::windSpeed = nullptr;
float* DataCalculations::airTemp = nullptr;
float* DataCalculations::solarRad = nullptr;
int DataCalculations::count = 0;
int DataCalculations::capacity = 0;

DataCalculations::DataCalculations()
{
    averageSpeed = 0;
    averageAirTemp = 0;

    capacity = INITIAL_CAPACITY;
    windSpeed = new float[capacity];
    airTemp = new float[capacity];
    solarRad = new float[capacity];
    count = 0;
}

DataCalculations::~DataCalculations()
{
    delete[] windSpeed;
    delete[] airTemp;
    delete[] solarRad;
}

void DataCalculations::resizeArray()
{
    int newCapacity;

    if(capacity == 0)
    {
        newCapacity = INITIAL_CAPACITY;
    }

    else
    {
        newCapacity = capacity * 2; //resize the dynamic array to 2x capacity
    }

    float* newWindSpeed = new float[newCapacity];
    float* newAirTemp = new float[newCapacity];
    float* newSolarRad = new float[newCapacity];

    for (int i = 0; i < count; i++)
    {
        newWindSpeed[i] = windSpeed[i];
        newAirTemp[i] = airTemp[i];
        newSolarRad[i] = solarRad[i];
    }

    delete[] windSpeed;
    delete[] airTemp;
    delete[] solarRad;

    windSpeed = newWindSpeed;
    airTemp = newAirTemp;
    solarRad = newSolarRad;
    capacity = newCapacity;
}

void DataCalculations::collectData(WeatherData& data)
{
    if (count >= capacity)
    {
        resizeArray();
    }

    if (count == 0)
    {
        count++;
        return;  // Skip index 0
    }

    windSpeed[count] = data.GetSpeed();
    airTemp[count] = data.GetAirTemp();
    solarRad[count] = data.GetSolarRad();

    count++;
}

float DataCalculations::CalculateAvgSpeed(BinarySearchTree <WeatherData> & dataRecords)
{
    count = 0;
    dataRecords.InOrderTraversal(DataCalculations::collectData);

    if(count == 0)
    {
        return 0;
    }

    float sum = 0;

    for (int i = 0; i < count; i++)
    {
        sum += windSpeed[i];
    }

    return sum / count;

}

float DataCalculations::CalculateSpeedSD(BinarySearchTree <WeatherData> & dataRecords, float averageSpeed)
{
    count = 0;
    dataRecords.InOrderTraversal(DataCalculations::collectData);

    if(count == 0)
    {
        return 0;
    }

    float sum = 0;

    for(int i = 0; i < count; i++)
    {
        sum += (windSpeed[i] - averageSpeed) * (windSpeed[i] - averageSpeed);
    }

    return sqrt(sum / count);
}

float DataCalculations::CalculateSpeedMAD(BinarySearchTree <WeatherData> & dataRecords)
{
    count = 0;
    dataRecords.InOrderTraversal(DataCalculations::collectData);

    if (count == 0)
    {
        return 0;
    }

    float meanSpeed = CalculateAvgSpeed(dataRecords);
    float speedMAD = 0;

    for(int i = 0; i < count; i++)
    {
        speedMAD += abs(windSpeed[i] - meanSpeed); //return absolute value
    }

    return speedMAD / count;
}

float DataCalculations::CalculateAvgAirTemp(BinarySearchTree <WeatherData> & dataRecords)
{
    count = 0;
    dataRecords.InOrderTraversal(DataCalculations::collectData);

    if(count == 0)
    {
        return 0;
    }

    float sum = 0;

    for (int i = 0; i < count; i++)
    {
        sum += airTemp[i];
    }

    return sum / count;
}

float DataCalculations::CalculateAirTempSD(BinarySearchTree <WeatherData> & dataRecords, float averageAirTemp)
{
    count = 0;
    dataRecords.InOrderTraversal(DataCalculations::collectData);

    if(count == 0)
    {
        return 0;
    }

    float sum = 0;

    for(int i = 0; i < count; i++)
    {
        sum+= (airTemp[i] - averageAirTemp) * (airTemp[i] - averageAirTemp);
    }

    return sqrt(sum / count);
}

float DataCalculations::CalculateAirTempMAD(BinarySearchTree <WeatherData> & dataRecords)
{
    count = 0;
    dataRecords.InOrderTraversal(DataCalculations::collectData);

    if (count == 0)
    {
        return 0;
    }

    float meanAirTemp = CalculateAvgAirTemp(dataRecords);
    float airTempMAD = 0;

    for(int i = 0; i < count; i++)
    {
        airTempMAD += abs(airTemp[i] - meanAirTemp); //return absolute value
    }

    return airTempMAD / count;
}

float DataCalculations::CalculateSolarRad(BinarySearchTree <WeatherData> & dataRecords)
{
    count = 0;
    dataRecords.InOrderTraversal(DataCalculations::collectData);

    if(count == 0)
    {
        return 0;
    }

    float sum = 0;

    for(int i = 0; i < count; i++)
    {
        sum += solarRad[i];
    }

    return sum;
}

