#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "BinarySearchTree.h"
#include "Date.h"
#include "WeatherData.h"
#include "sPCC.h"
#include "LoadRecords.h"
#include "DataCalculations.h"

using namespace std;

string getMonthName(int month)
{
    const string months[] = {"January", "February", "March", "April",
                             "May", "June", "July", "August",
                             "September", "October", "November", "December"};

    if (month >= 1 && month <= 12)
    {
        return months[month - 1];  // Returns the month name
    }

    else
    {
        return "Invalid";
    }
}

int main()
{
    BinarySearchTree<WeatherData> bstTree;
    sPCC spccCalculator;
    DataCalculations dataCal;

    ifstream infile("data/data_source.txt");
    if (!infile)
    {
        return -1;
    }

    string csvFile;
    while (getline(infile, csvFile))
    {
        LoadRecords(bstTree, "data/" + csvFile);
    }

    infile.close(); // close the file after reading

    string option = " ";

    do
    {
        cout << endl;
        cout << "Menu Option" << endl;
        cout << "1.Average Wind Speed and Standard Deviation" << endl;
        cout << "2.Average Air Temperature and Standard Deviation" << endl;
        cout << "3.SPCC Calculations" << endl;
        cout << "4.Mean Absolute Deviation (MAD) Calculation" << endl;
        cout << "5.Exit" << endl << '\n';

        cout << "Choose Your Option: ";
        cin >> option;

        if(option == "1")
        {
            cout << "----------------------------------------------" << endl;
            cout << "Average Wind Speed and Standard Deviation" << endl << '\n';

            string month;
            int year;
            cout << "Enter month and year: ";
            cin >> month >> year;

            bstTree.InOrderTraversal(DataCalculations::collectData);

            float avgSpeed = dataCal.CalculateAvgSpeed(bstTree);
            float speedSD = dataCal.CalculateSpeedSD(bstTree, avgSpeed);

            // Output
            cout << month << " " << year << '\n';
            cout << "Average speed: " << avgSpeed << " km/h " << endl;
            cout << "Sample stdev: " << speedSD << endl;

        }

        else if(option == "2")
        {
            cout << "----------------------------------------------" << endl;
            cout << "Average Air Temperature and Standard Deviation" << endl << '\n';

            int year;
            cout << "Enter the year: ";
            cin >> year;

            for(int i = 1; i <= 12; i++) //loop through the months
            {
                float avgAirTemp = dataCal.CalculateAvgAirTemp(bstTree);
                float airTempSD = dataCal.CalculateAirTempSD(bstTree, avgAirTemp);

                // Output
                cout << getMonthName(i) << ": average: " << avgAirTemp << " degree C, stdev: "
                << airTempSD << endl;
            }
        }

        else if(option == "3")
        {
            cout << "----------------------------------------------" << endl;
            cout << "sPCC Calculations" << endl << '\n';

            //ask user to enter month
            int month;
            cout << "Enter month(1-12): ";
            cin >> month;

            string monthName = getMonthName(month);

            float ST;
            float SR;
            float TR;

            bstTree.InOrderTraversal(sPCC::collectData);

            ST = spccCalculator.sPCC_ST(bstTree);  // Wind Speed and Temperature
            SR = spccCalculator.sPCC_SR(bstTree);  // Wind Speed and Solar Radiation
            TR = spccCalculator.sPCC_TR(bstTree);  // Temperature and Solar Radiation

            // Output the results
            cout << "Sample Pearson Correlation Coefficient for Month: " << monthName << '\n';
            cout << "S_T: " << ST << endl;
            cout << "S_R: " << SR << endl;
            cout << "T_R: " << TR << endl;
        }

        else if(option == "4")
        {
            cout << "----------------------------------------------" << endl;
            cout << "MAD Calculations" << endl << '\n';

            int year;
            cout << "Enter the year: ";
            cin >> year;

            ofstream outputFile("WindTempSolar.csv");
            if(!outputFile)
            {
                return -1;
            }

            outputFile << year << endl;

            for(int i = 1; i <= 12; i++) //loop through the months
            {
                float avgSpeed = dataCal.CalculateAvgSpeed(bstTree);
                float speedSD = dataCal.CalculateSpeedSD(bstTree, avgSpeed);
                float speedMAD = dataCal.CalculateSpeedMAD(bstTree);
                float avgAirTemp = dataCal.CalculateAvgAirTemp(bstTree);
                float airTempSD = dataCal.CalculateAirTempSD(bstTree, avgAirTemp);
                float airTempMAD = dataCal.CalculateAirTempMAD(bstTree);
                float totalSolarRad = dataCal.CalculateSolarRad(bstTree);

                // Output
                cout << getMonthName(i) << "," << avgSpeed << "(" << speedSD << ", " << speedMAD << "),"
                << avgAirTemp << "(" << airTempSD << ", " << airTempMAD << "),"
                << totalSolarRad << endl;

                // Write results to file
                outputFile << year << endl;
                outputFile << getMonthName(i) << "," << avgSpeed << "(" << speedSD << ", " << speedMAD
                << ")," << avgAirTemp << "(" << airTempSD << ", " << airTempMAD << "),"
                << totalSolarRad << endl;
            }
            outputFile.close();
            cout << "Results written to WindTempSolar.csv" << endl << '\n';
        }

        else if(option == "5")
        {
            cout << "----------------------------------------------" << endl;
            cout << "Exiting Program!" << endl;
        }
        else
        {
            cout << "Invalid Input! Please enter number from 1 to 4." << endl << '\n';
        }
    }

    while(option != "5");

    cout << '\n' << "~End Of Program~" << endl;

    return 0;
}

