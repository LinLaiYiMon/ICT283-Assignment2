#ifndef SPCC_H_INCLUDED
#define SPCC_H_INCLUDED

#include "BinarySearchTree.h"
#include "WeatherData.h"

class sPCC
{
public:
    sPCC();
    ~sPCC();

    float sPCC_ST(BinarySearchTree<WeatherData> & bstTree); //avg wind speed and air temp
    float sPCC_SR(BinarySearchTree<WeatherData> & bstTree); //avg wind speed and solar rad
    float sPCC_TR(BinarySearchTree<WeatherData> & bstTree); //air temp and solar rad

    static void collectData(WeatherData& data);

private:
    static float* windSpeed;
    static float* airTemp;
    static float* solarRad;
    static int count;
    static int capacity;
    const static int INITIAL_CAPACITY = 1000;

    float calculateSPCC(const float x[], const float y[], int n);
    static void resizeArray();
};


#endif // SPCC_H_INCLUDED
