//#include "stdafx.h"
#include <iostream> 
#include <Windows.h>
#include <stdio.h>
#include <fstream> 
#include <string> 
#include <vector>
#include <sstream>
#include "SensorOfRotation.h"
#include "SensorOfTransmission.h"
#include "SensorOfGas.h"
#include "SensorOfValve.h"

using namespace std;
void workGas(SensorOfGas sensorOfGas, SensorOfTransmission sensorOfTransmission, SensorOfRotation sensorOfRotation, SensorOfValve sensorOfValue);
void workTransmission(SensorOfGas sensorOfGas, SensorOfTransmission sensorOfTransmission, SensorOfRotation sensorOfRotation, SensorOfValve sensorOfValue);
void workRotation(SensorOfGas sensorOfGas, SensorOfTransmission sensorOfTransmission, SensorOfRotation sensorOfRotation, SensorOfValve sensorOfValue);
void logger(string s);
string s;
bool sostclp;
string pathL;
string pathP;
int countOfOperation;
int lastValue;
int main()
{
	lastValue = 0;
	setlocale(LC_CTYPE, "Russian");
	sostclp = false;
	string line;

	// rand()%(b-a+1) + a;

	cout << "Введите путь к файлу log:" << endl;
	cin >> pathL;

	cout << "Введите путь к файлу product:" << endl;
	cin >> pathP;

	cout << "Введите количество операций:" << endl;
	cin >> countOfOperation;

	//ifstream file("C:\\My projects\\product.txt"); // окрываем файл для чтения  
	//ifstream file("product.txt");
	ofstream fout1(pathP, ofstream::app);
	for (int i = 0; i < countOfOperation; i++)
	{
		int g = rand() % (1 + 1 + 1) - 1; //gas
		int t = rand() % (6 + 1 + 1) - 1; //transmission
		int r = rand() % (0 + 1 + 1) - 1; //rotation
		int v = rand() % (7000 + 1 + 1) - 1; //value
		fout1 << g << " " << t << " " << r << " " << v << endl;
	}
	fout1.close();

	ifstream file(pathP);
	if (file.is_open())
	{

		while (getline(file, line))
		{
			vector<int> mass;
			int n;
			istringstream ss(line);

			while (ss >> n) mass.push_back((int)n);
			s = "Считываем данные";
			cout << s << endl;
			logger(s);

			SensorOfGas* sensorOfGas = new SensorOfGas(mass[0]);
			SensorOfTransmission* sensorOfTransmission = new SensorOfTransmission(mass[1]);
			SensorOfRotation* sensorOfRotation = new SensorOfRotation(mass[2], sostclp);
			SensorOfValve* sensorOfValue = new SensorOfValve(mass[3]);

			workGas(*sensorOfGas, *sensorOfTransmission, *sensorOfRotation, *sensorOfValue);

			delete sensorOfGas;
			delete sensorOfTransmission;
			delete sensorOfRotation;
			delete sensorOfValue;
			s = "________________";
			cout << s << endl;
			logger(s);
		}
	}
	file.close(); // закрываем файл 

	s = "Программа завершила работу";
	cout << s << endl;
	logger(s);
	return 0;
}

void workGas(SensorOfGas sensorOfGas, SensorOfTransmission sensorOfTransmission, SensorOfRotation sensorOfRotation, SensorOfValve sensorOfValue)
{
	if (sensorOfGas.avail)
	{
		s = "Датчик положения дроссельной заслонки доступен";
		cout << s << endl;
		logger(s);
		if (!sensorOfGas.GasIsOpen())
		{
			s = "Заслонка закрыта";
			cout << s << endl;
			logger(s);
			workTransmission(sensorOfGas, sensorOfTransmission, sensorOfRotation, sensorOfValue);
			return;
		}
		else
		{
			s = "Заслонка открыта";
			cout << s << endl;
			logger(s);
			if (sensorOfRotation.avail)
			{
				s = "Датчик положения клапана доступен";
				cout << s << endl;
				logger(s);
				if (sensorOfRotation.RotationOpen())
				{
					s = "Клапан включен";
					cout << s << endl;
					logger(s);
					sensorOfRotation.ChangeStatusOfRotation(false);
					sostclp = false;
					s = "Выключаем клапан";
					cout << s << endl;
					logger(s);
				}
				else {
					s = "Клапан выключен";
					cout << s << endl;
					logger(s);
					s = "Клапан остается выключенным";
					cout << s << endl;
					logger(s);
				}
				return;
			}
			else
			{
				s = "Система недоступна. Отказ датчика положения клапана";
				cout << s << endl;
				logger(s);
				return;
			}
		}
	}
	else
	{
		s = "Система недоступна. Отказ датчика положения дроссельной заслонки";
		cout << s << endl;
		logger(s);
		/*
		if (sensorOfRotation.avail)
		{
			s = "Датчик положения клапана доступен";
			cout << s << endl;
			logger(s);
			if (sensorOfRotation.RotationOpen())
			{
				sensorOfRotation.ChangeStatusOfRotation(false);
				sostclp = false;
				s = "Закрываем клапан";
				cout << s << endl;
				logger(s);
			}
			else {
				s = "Клапан остается выключенным";
				cout << s << endl;
				logger(s);
			}
			return;
		}
		else
		{
			s = "Датчик клапанпа недоступен";
			cout << s << endl;
			logger(s);
			return;
		}*/
	}
}
void workTransmission(SensorOfGas sensorOfGas, SensorOfTransmission sensorOfTransmission, SensorOfRotation sensorOfRotation, SensorOfValve sensorOfValue)
{
	if (sensorOfTransmission.avail)
	{
		s = "Датчик передачи доступен";
		cout << s << endl;
		logger(s);
		if (!sensorOfTransmission.neutralTransmission())
		{
			s = "Передача не нейтральная";
			cout << s << endl;
			logger(s);
			workRotation(sensorOfGas, sensorOfTransmission, sensorOfRotation, sensorOfValue);
			return;
		}
		else
		{
			s = "Передача нейтральная";
			cout << s << endl;
			logger(s);
			if (sensorOfRotation.avail)
			{
				s = "Датчик клапана доступен";
				cout << s << endl;
				logger(s);
				if (sensorOfRotation.RotationOpen())
				{
					s = "Клапан включен";
					cout << s << endl;
					logger(s);
					sensorOfRotation.ChangeStatusOfRotation(false);
					sostclp = false;
					s = "Выключаем клапан";
					cout << s << endl;
					logger(s);
				}
				else {
					s = "Клапан выключен";
					cout << s << endl;
					logger(s);
					s = "Клапан остается выключенным";
					cout << s << endl;
					logger(s);
				}
			}
			else
			{
				s = "Система недоступна. Отказ датчика клапана";
				cout << s << endl;
				logger(s);
				return;
			}
		}
	}
	else
	{
		s = "Система недоступна. Отказ датчика передачи";
		cout << s << endl;
		logger(s);
		/*
		if (sensorOfRotation.avail)
		{
			s = "Датчик клапана доступен";
			cout << s << endl;
			logger(s);
			if (sensorOfRotation.RotationOpen()) {
				sensorOfRotation.ChangeStatusOfRotation(false);
				sostclp = false;
				s = "Закрываем клапан";
				cout << s << endl;
				logger(s);
				return;
			}else{
				s = "Клапан остается выключенным";
				cout << s << endl;
				logger(s);
			}
		}
		else
		{
			s = "Датчик клапана недоступен";
			cout << s << endl;
			logger(s);
			return;
		}
		*/
	}
}
void workRotation(SensorOfGas sensorOfGas, SensorOfTransmission sensorOfTransmission, SensorOfRotation sensorOfRotation, SensorOfValve sensorOfValue)
{
	if (sensorOfRotation.avail)
	{
		s = "Датчик клапана доступен";
		cout << s << endl;
		logger(s);
		
			if (sensorOfValue.avail)
			{
				s = "Датчик частоты вращения коленвала доступен";
				cout << s << endl;
				logger(s);
				if (sensorOfValue.ValveOfTurns() > lastValue)
				{
					s = "Поток оборотов восходящий";
					cout << s << endl;
					logger(s);
					if (sensorOfValue.ValveOfTurns() > 2100)
					{
						s = "Частота вращения коленвала > 2100 оборотов в минуту";
						cout << s << endl;
						logger(s);
						if (sensorOfRotation.RotationOpen())
						{
							s = "Клапан включен";
							cout << s << endl;
							logger(s);
							sensorOfRotation.ChangeStatusOfRotation(false);
							sostclp = false;
							s = "Выключаем клапан";
							cout << s << endl;
							logger(s);
						}
						else {
							s = "Клапан выключен";
							cout << s << endl;
							logger(s);
							s = "Клапан остается выключенным";
							cout << s << endl;
							logger(s);
						}
						return;
					}
					else
					{
						s = "Частота вращения коленвала <= 2100 оборотов в минуту";
						cout << s << endl;
						logger(s);
						if (!sensorOfRotation.RotationOpen())
						{
							s = "Клапан выключен";
							cout << s << endl;
							logger(s);
							sensorOfRotation.ChangeStatusOfRotation(true);
							sostclp = true;
							s = "Включаем клапан";
							cout << s << endl;
							logger(s);
						}
						else {
							s = "Клапан включен";
							cout << s << endl;
							logger(s);
							s = "Клапан остается включенным";
							cout << s << endl;
							logger(s);
						}

						return;
					}


				}
				else
				{
					s = "Поток оборотов низходящий";
					cout << s << endl;
					logger(s);
					if (sensorOfValue.ValveOfTurns()<1900)
					{
						s = "Частота вращения коленвала < 1900 оборотов в минуту";
						cout << s << endl;
						logger(s);
						if (!sensorOfRotation.RotationOpen())
						{
							s = "Клапан выключен";
							cout << s << endl;
							logger(s);
							sensorOfRotation.ChangeStatusOfRotation(true);
							sostclp = true;
							s = "Включаем клапан";
							cout << s << endl;
							logger(s);
						}
						else {
							s = "Клапан включен";
							cout << s << endl;
							logger(s);
							s = "Клапан остается включенным";
							cout << s << endl;
							logger(s);
						}
						return;
					}
					else
					{
						s = "Частота вращения коленвала >= 1900 оборотов в минуту";
						cout << s << endl;
						logger(s);
						if (sensorOfRotation.RotationOpen())
						{
							s = "Клапан включен";
							cout << s << endl;
							logger(s);
							sensorOfRotation.ChangeStatusOfRotation(false);
							sostclp = false;
							s = "Выключаем клапан";
							cout << s << endl;
							logger(s);
						}
						else {
							s = "Клапан выключен";
							cout << s << endl;
							logger(s);
							s = "Клапан остается выключенным";
							cout << s << endl;
							logger(s);
						}
						return;
					}

					
					

					

				}
				

				














			}
			else
			{
				s = "Система недоступна. Отказ датчика вращения коленвала";
				cout << s << endl;
				logger(s);
				/*
				if (sensorOfRotation.RotationOpen())
				{
					sensorOfRotation.ChangeStatusOfRotation(false);
					sostclp = false;
					s = "Выключаем клапан";
					cout << s << endl;
					logger(s);
				}
				else {
					s = "Клапан остается выключенным";
					cout << s << endl;
					logger(s);
				}
				return;*/
			}
		
		
	}
	else
	{
		s = "Система недоступна. Отказ датчика положения клапана";
		cout << s << endl;
		logger(s);
		return;
	}
}

void logger(string s) {
	SYSTEMTIME st;
	GetLocalTime(&st);
	//ofstream fout("log.txt", ofstream::app);
	ofstream fout(pathL, ofstream::app);
	//fout << ("%d %02d %02d %02d %02d %02d %03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds) <<"   " << s << endl;
	fout << ("%d", st.wYear) << "-" << ("%2d", st.wMonth) << "-" << ("%02d", st.wDay) << " " << ("%02d", st.wHour) << ":" << ("%02d", st.wMinute) << ":" << ("%02d", st.wSecond) << "." << ("%02d", st.wMilliseconds) << "   " << s << endl;

	fout.close();
}

