#include <fstream>
#include <sstream>
#include <iostream>
#include "BinarySearchTree.h"
#include "LoadRecords.h"
#include "WeatherData.h"


int LoadRecords(BinarySearchTree<WeatherData> &bstTree ,const string & filename)
{
    int count = 0;
    ifstream inFile(filename.c_str());
    const char CSV_DELIMITER = ',';
    const char DATE_DELIMITER = '/';

    string header;
    getline(inFile, header); // read the header

    // process Header to find indexes of WAST, S, SR & T
    stringstream newHeader(header);
    string column;
    int columnidx = 0;
    int dateCol = -1;
    int speedCol = -1;
    int srCol = -1;
    int tCol = -1;

    while(getline(newHeader, column, CSV_DELIMITER))
    {
        if(column == "WAST")
        {
            dateCol = columnidx;
        }

         if(column == "S")
        {
            speedCol = columnidx;
        }

        if(column == "SR")
        {
            srCol = columnidx;
        }

        if(column == "T")
        {
            tCol = columnidx;
        }

        columnidx++;
    }

    string line;
    string tempDateStr;
    string tempStr;
    float windSpeed;
    float airTemp;
    float solarRad;

    while(getline(inFile, line))
    {
        stringstream ss(line);

        getline(ss, tempDateStr, CSV_DELIMITER);

        // convert tempDateStr to Date object
        int year, month, day;
        stringstream ssDate(tempDateStr);

        getline(ssDate, tempStr, DATE_DELIMITER);  // Day in string format
        day = stoi(tempStr);

        getline(ssDate, tempStr, DATE_DELIMITER);  // Month in string format
        month = stoi(tempStr);

        getline(ssDate, tempStr);                  // Year in string format
        year = stoi(tempStr);


        for(int i = 1; i < columnidx; i++)
        {
            getline(ss, tempStr, CSV_DELIMITER);

            if (i == speedCol) // get the speed
            {
                windSpeed = stof(tempStr) * 3.6;  // Convert m/s to km/h

                if (windSpeed < 0)
                {
                    continue;  // Skip this iteration and don't insert this record into the tree
                }
            }

            if (i == tCol) //get air temp
            {
                airTemp = stof(tempStr);
            }

            if (i == srCol) //get solar rad
            {
                solarRad = stof(tempStr);
            }
        }

        WeatherData records;
        records.SetDate(Date(day, month, year));
        records.SetSpeed(windSpeed);
        records.SetAirTemp(airTemp);
        records.SetSolarRad(solarRad);

        bstTree.Insert(records);
        count++;
    }

    return count;
}
