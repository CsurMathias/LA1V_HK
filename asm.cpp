#include <wiringPi.h>



const int analogInCurrent = A0;
const int analogInVoltage = A1;

int mV_A = 100;             //Milli Volt pro Ampere (Wert laut Datenblatt)
int rawValue = 0;
int acOffset = 2500;        //Wert laut Datenblatt

double spannung = 0;
double strom = 0;

int maxAmount = 20;
int rawVoltage[maxAmount];



double findPeakV()
{
    int arrayMax = 0;

   for (int i = 0; i < maxAmount; i++)
   {
       rawVoltage[i] = analogRead(analogInVoltage);
   }
   
    for (int j = 0; j < maxAmount; j++)
    {
        if (rawVoltage[j] > arrayMax)
        {
            arrayMax = rawVoltage[j];
        }        
    }
    return arrayMax;
}


double readCurrent(int rawInput)
{
    rawValue = rawInput;

    spannung = (rawValue / 1024.0) * 5000;
    strom = ((spannung - acOffset) / mV_A);
    return strom;
}


int Main(void)
{
    wiringPiSetupGpio(void);
    void pinMode(analogInCurrent, INPUT);

    rawValue = analogRead(analogInCurrent);
    readCurrent(rawValue);

    return 0;
}
