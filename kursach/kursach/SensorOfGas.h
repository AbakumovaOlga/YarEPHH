#pragma once
#ifndef _SensorOfGas_H_
#define _SensorOfGas_H_
class SensorOfGas
{

public:
	SensorOfGas(int g);
	~SensorOfGas();
	bool avail;
	bool GasIsOpen(); //метод который возвращает состояние заслонки (открыта ли заслонка?)

private:
	bool pGasIsOpen; //сотояние заслонки 


};
#endif
