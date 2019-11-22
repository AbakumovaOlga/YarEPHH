//#include "stdafx.h"
#include "SensorOfValve.h"

#include <iostream>
#include <string>
using namespace std;
SensorOfValve::SensorOfValve(int v)
{
	if (v < 0) 
	{
		avail = false;
		pValveOfTurns = -1;
	}
	else
	{
		avail = true;
		pValveOfTurns = v;
	}
		
	
}


SensorOfValve::~SensorOfValve()
{
}


int SensorOfValve::ValveOfTurns()
{
	if (avail)
	{
		return pValveOfTurns;
	}
	else
	{
		string s = "Error Sensor of valve";
		throw s;
	}
}

