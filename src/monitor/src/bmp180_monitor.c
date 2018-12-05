#include <bmp180_monitor.h>
#include <stdio.h>

void monitor(float temp, float press, float alti) {
	printf("\nTemperature : %.2f C\n",temp);
	printf("Pressure :    %.2f Pa\n",press);
	printf("Altitude :    %.2f h\n",alti);
}
