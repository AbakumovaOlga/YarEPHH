#pragma once
#ifndef _SensorOfGas_H_
#define _SensorOfGas_H_
class SensorOfGas
{

public:
	SensorOfGas(int g);
	~SensorOfGas();
	bool avail;
	bool GasIsOpen(); //����� ������� ���������� ��������� �������� (������� �� ��������?)

private:
	bool pGasIsOpen; //�������� �������� 


};
#endif
