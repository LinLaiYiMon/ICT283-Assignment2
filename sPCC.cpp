#include <iostream>
#include <cmath>

#include "sPCC.h"
#include "BinarySearchTree.h"
#include "WeatherData.h"

using std::cout;

float* sPCC::windSpeed = nullptr;
float* sPCC::airTemp = nullptr;
float* sPCC::solarRad = nullptr;
int sPCC::count = 0;
int sPCC::capacity = 0;

sPCC::sPCC()
{
    capacity = INITIAL_CAPACITY;
    windSpeed = new float[capacity];
    airTemp = new float[capacity];
    solarRad = new float[capacity];
    count = 0;
}

sPCC::~sPCC()
{
    delete[] windSpeed;
    delete[] airTemp;
    delete[] solarRad;
}

void sPCC::resizeArray()
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

void sPCC::collectData(WeatherData& data)
{
    if (count >= capacity)
    {
        resizeArray();
    }

    windSpeed[count] = data.GetSpeed();
    airTemp[count] = data.GetAirTemp();
    solarRad[count] = data.GetSolarRad();
    count++;
}

float sPCC::sPCC_ST(BinarySearchTree<WeatherData> & bstTree)
{
    count = 0;

    // Traverse the tree and collect data using the wrapper function
    bstTree.InOrderTraversal(sPCC::collectData);

    // Calculate SPCC between wind speed and air temp
    return calculateSPCC(windSpeed, airTemp, count);
}

float sPCC::sPCC_SR(BinarySearchTree<WeatherData> & bstTree)
{
    count = 0;

    bstTree.InOrderTraversal(sPCC::collectData);

    // Calculate SPCC between wind speed and solar rad
    return calculateSPCC(windSpeed, solarRad, count);
}

float sPCC::sPCC_TR(BinarySearchTree<WeatherData> & bstTree)
{
    count = 0;

    bstTree.InOrderTraversal(sPCC::collectData);

    // Calculate SPCC between air temp and solar rad
    return calculateSPCC(airTemp, solarRad, count);
}


float sPCC::calculateSPCC(const float x[], const float y[], int n)
{
    if(n == 0)
    {
        return 0;
    }

    float dataX = 0;
    float dataY = 0;
    float xy = 0; //sum of xy
    float x2 = 0; //x^2
    float y2 = 0; //y^2

    for(int i = 0; i < n; i++)
    {
        dataX += x[i];
        dataY += y[i];
        xy +=  x[i] * y[i];
        x2 += x[i] * x[i];
        y2 += y[i] * y[i];
    }

    float numerator;
    float denomiator;

    numerator = n * xy - dataX * dataY;
    denomiator = sqrt((n * x2 - dataX * dataX) * (n * y2 - dataY * dataY));

    if (denomiator == 0)
    {
        return 0;  // Avoid division by zero
    }

    return numerator / denomiator;  // Return the SPCC value
}
