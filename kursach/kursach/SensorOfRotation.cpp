//#include "stdafx.h"
#include "SensorOfRotation.h"

#include <iostream>
#include <string>
using namespace std;
SensorOfRotation::SensorOfRotation(int r, bool sostclp)
{
	if (r == 0)
	{
		avail = true;
	}
	if (r == -1)
	{
		avail = false;
	}
	statusOfRotation = sostclp;
}


SensorOfRotation::~SensorOfRotation()
{
}

bool SensorOfRotation::RotationOpen()
{
	if (avail)
	{
		return statusOfRotation;
	}
	else
	{
		string s = "Error Sensor of rotation";
		throw s;
	}
}

void SensorOfRotation::ChangeStatusOfRotation(bool sost)
{
	if (avail)
	{
		statusOfRotation = sost;
	}
	else
	{
		string s = "Error Sensor of rotation";
		throw s;
	}
}

