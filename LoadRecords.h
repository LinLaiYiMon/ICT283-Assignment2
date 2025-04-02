#ifndef LOADRECORDS_H_INCLUDED
#define LOADRECORDS_H_INCLUDED

#include "BinarySearchTree.h"
#include "WeatherData.h"
#include <string>

int LoadRecords(BinarySearchTree<WeatherData> &bstTree ,const string & filename);

#endif // LOADRECORDS_H_INCLUDED
