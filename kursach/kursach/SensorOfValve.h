#pragma once
#ifndef _SensorOfValve_H_
#define _SensorOfValve_H_
class SensorOfValve
{

public:
	SensorOfValve(int v);
	~SensorOfValve();
	bool avail;
	int ValveOfTurns();

private:
	int pValveOfTurns;


};
#endif

