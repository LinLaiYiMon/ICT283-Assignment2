#ifndef DATACALCULATIONS_H_INCLUDED
#define DATACALCULATIONS_H_INCLUDED

#include "BinarySearchTree.h"
#include "WeatherData.h"

class DataCalculations
{
public:
    DataCalculations();
    ~DataCalculations();

    float CalculateAvgSpeed(BinarySearchTree <WeatherData> & dataRecords);
    float CalculateSpeedSD(BinarySearchTree <WeatherData> & dataRecords, float averageSpeed);
    float CalculateSpeedMAD(BinarySearchTree <WeatherData> & dataRecords);
    float CalculateAvgAirTemp(BinarySearchTree <WeatherData> & dataRecords);
    float CalculateAirTempSD(BinarySearchTree <WeatherData> & dataRecords, float averageAirTemp);
    float CalculateAirTempMAD(BinarySearchTree <WeatherData> & dataRecords);
    float CalculateSolarRad(BinarySearchTree <WeatherData> & dataRecords);

    static void collectData(WeatherData& data);


private:
    float averageSpeed;
    float averageAirTemp;

    static float* windSpeed;
    static float* airTemp;
    static float* solarRad;
    static int count;
    static int capacity;
    const static int INITIAL_CAPACITY = 1000;
    static void resizeArray();
};

#endif // DATACALCULATIONS_H_INCLUDED
