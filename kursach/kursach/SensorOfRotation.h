#pragma once
#ifndef _SensorOfRotation_H_
#define _SensorOfRotation_H_
class SensorOfRotation
{

public:
	SensorOfRotation(int r, bool sostclp);
	~SensorOfRotation();
	bool avail;
	bool RotationOpen();
	void ChangeStatusOfRotation(bool sost);

private:
	bool statusOfRotation;




};
#endif

