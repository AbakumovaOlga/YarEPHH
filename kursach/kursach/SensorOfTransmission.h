#pragma once
#ifndef _SensorOfTransmission_H_
#define _SensorOfTransmission_H_
class SensorOfTransmission
{
public:
	SensorOfTransmission(int);
	~SensorOfTransmission();
	bool avail;
	bool neutralTransmission();

private:
	int numberOfTransmission;


};
#endif