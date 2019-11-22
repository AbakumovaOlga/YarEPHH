//#include "stdafx.h"
#include "SensorOfGas.h"

#include <iostream>
#include <string>
using namespace std;
SensorOfGas::SensorOfGas(int g)
{
	if (g == 1)
	{
		avail = true;
		pGasIsOpen = true;
	}
	if (g == 0)
	{
		avail = true;
		pGasIsOpen = false;
	}
	if (g == -1)
	{
		avail = false;
	}
}


SensorOfGas::~SensorOfGas()
{
}

bool SensorOfGas::GasIsOpen()
{

	if (avail) {
		return pGasIsOpen;
	}
	else {
		string s = "Error Sensor of gas";
		throw s;// "выброс" ошибки типа "стринг"
	}


}
