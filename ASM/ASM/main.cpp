#include <wiringPi.h>
#include <string>
#include <bitset>
#include <iostream>

using namespace std

#define ADU_PIN0  6
#define ADU_PIN1 10
#define ADU_PIN2 11
#define ADU_PIN3 31

#define RELAIS_SOURCE 2
#define RELAIS_STAR 3
#define RELAIS_TRIANGLE 4

const int analogInCurrent = 8;	
const int analogInVoltage = 9;	


int mV_A = 100;             //mV/A (datasheet)
int rawValue = 0;
int acOffset = 2500;        //datasheet


const int maxAmount = 20;
int rawVoltage[maxAmount];


int main(void)
{
	wiringPiSetupSys();
	
	pinMode(ADU_PIN0, INPUT); 
	pinMode(ADU_PIN1, INPUT);
	pinMode(ADU_PIN2, INPUT);
	pinMode(ADU_PIN3, INPUT);

	pinMode(analogInCurrent, INPUT);
	pinMode(analogInVoltage, INPUT);
	


	return 0;
}

double findPeakV()
{
	int arrayMax = 0;

	//read ADC
	for (int counter = 0; counter < maxAmount; counter++)
	{
		rawVoltage[counter] = readADC();
	}

	//find max U val
	for (int counter = 0; counter < maxAmount; counter++)
	{
		if (rawVoltage[counter] > arrayMax)
		{
			arrayMax = rawVoltage[counter];
		}
	}
}

//calculate Current value from raw input
double calcCurrent(int rawInput)
{
	rawValue = rawInput;
	double voltage = (rawValue / 1024.0) * 5000;
	return ((voltage - acOffset) / mV_A);
}

//reads ADC-Value converts it to ulong
int readADC()
{
	int bit0_int = digitalRead(ADU_PIN0);
	int bit1_int = digitalRead(ADU_PIN1);
	int bit2_int = digitalRead(ADU_PIN2);
	int bit3_int = digitalRead(ADU_PIN3);

	std::string bit0 = std::to_string(bit0_int);
	std::string bit1 = std::to_string(bit1_int);
	std::string bit2 = std::to_string(bit2_int);
	std::string bit3 = std::to_string(bit3_int);

	std::string nibble = bit3 + bit2 + bit1 + bit0;

	int decVal = std::bitset<8>(nibble).to_ulong();

	return decVal;
}


void meassure(int mode)
{
	digitalWrite(RELAIS_SOURCE, HIGH);
	
	//TDODO: Software lock 
	switch (mode)
	{
		case 1:
			//star-triangle
			//TODO: meassure current to go to triangle
			digitalWrite(RELAIS_STAR, HIGH);
			break;

		case 2:
			//star
			digitalWrite(RELAIS_TRIANGLE, LOW);
			digitalWrite(RELAIS_STAR, HIGH);
			break;
		case 3:
			//triangle
			digitalWrite(RELAIS_STAR, LOW);
			digitalWrite(RELAIS_TRIANGLE, HIGH);
		case 100:
			//error
			break;

		default:
			break;
	}
}

//get userinput
int userChoice() 
{
	int input;
	int ack;

	std::cout << "Select your desired starting manner. 1 = Stern-Dreieck / 2 = Sternbetrieb / 3 = Dreieckbetrieb";
	std::cin >> input;

	std::cout << "You have chosen " << input << " correct = 1 / exit = 0";
	std::cin >> ack;

	if (ack == 1) 
	{
		return input;
	}
	else 
	{
		return 100;
	}
}