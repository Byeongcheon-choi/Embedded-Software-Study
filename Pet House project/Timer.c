#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>

void Setting(void) { //Setting Timer to enable the LED
	int startTime; // get info from APP
	int finishTime; // get info from APP
	unsigned int setting = -(finishTime - startTime) // Setting How much Turn LED setting on

	int second = 1000;
	int count = 0;
	unsigned int Time = now = millis(); // Using System timer -> This one is more accurate than Delay or Sleep function.

	while (count < setting)
	{
		if ((now - Time) < second) // when difference is less than Second unit, update the current system time.
		{
			now = millis();
		}
		Time = now = millis(); // when consume 1 second, reset timer setting
		count++ // counting until to reach the Customer setting.
	}
}

int main() {
	int config; // *Turn On/Off the Timer* -> get from App

	if (wiringPiSetup() == -1)
	{
		printf("Fail to start Project");
		return 1;
	}
	
	while (1)
	{
		if (config == 1); Setting(); // If getting On setting from App, implement Timer

	}
	
}



