#include <wiringPi.h>

const int analogInCurrent = 8;	//Wiringpi PinNumb
const int analogInVoltage = 9;	//Wiringpi PinNumb

int mV_A = 100;             //mV/A (datasheet)
int rawValue = 0;
int acOffset = 2500;        //datasheet

double spannung = 0;
double strom = 0;

const int maxAmount = 20;
int rawVoltage[maxAmount];

int main(void)
{
	wiringPiSetupSys();

	
	while (true)
	{

	}
	return 0;
}