//#include "stdafx.h"
#include "SensorOfTransmission.h"
#include <iostream>
#include <string>
using namespace std;


SensorOfTransmission::SensorOfTransmission(int n)
{
	if (n >= 0) {
		avail = true;
		numberOfTransmission = n;
	}
	else {
		avail = false;
		numberOfTransmission = -1;
	}

}



SensorOfTransmission::~SensorOfTransmission()
{
}

bool SensorOfTransmission::neutralTransmission()
{

	if (avail) {
		if (numberOfTransmission == 0)
		{
			return true;

		}
		else
		{
			return false;
		}
	}
	else {
		string s = "Error Sensor of transmission";
		throw s;// "выброс" ошибки типа "стринг"
	}


}