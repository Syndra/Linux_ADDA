#include <stdio.h>
#include <stdlib.h>
#include <bmp180.h>
#include <ads1256.h>
#include <bcm2835.h>
#include <monitor.h>
#include <logger.h>
#include <sensor_data.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <time.h>
#include <timer.h>
#include <pushalarm.h>
#include <databases.h>

//#define SENSOR_BMP180
#define SENSOR_ADS1256
#define BUZZER_PIN 29
#define BUTTON_PIN 28

double cur_light = 0;
double cur_temp = 0;

void test()
{
	puts("Hello, world!\n");
}

void timer_routine()
{
	int a = alarm_off();
	printf("%f : %f \n", cur_light, cur_temp);
}

int main(){

	uint8_t id;
	int32_t adc[8];
	int32_t volt[8];
	uint8_t ch_num = 8;
	int32_t iTemp;
	uint8_t buf[3];

	int i = 0;
	int result = 0;

	/* Data Storage Preparation */
	int nData = 3;
	sensor_data **data = NULL;
	data = (sensor_data *)malloc(sizeof(sensor_data*) * nData);

	for(i = 0 ; i < nData ; i++) {
		data[i] = sensor_data_init();
	}

	/* Initialize */
	ads1256_begin();
	alarm_init(BUZZER_PIN, BUTTON_PIN);
	/* Timer test */

	run_timer(timer_init(), timer_routine, 1, 0, 10000);
	//run_timer(timer_init(), test, 1, 0, 100000);

	while(1){
		/* Sensing */
		while((ADS1256_Scan() == 0));

		/* Set sensor data */

		sensor_data_set(data[0], "Round", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(0) /1670.0, "mV");
		sensor_data_set(data[1], "Light", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(1) /1670.0, "Lm");
		sensor_data_set(data[2], "Temp", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(2), "'C");

		cur_light = sensor_data_get_value(data[1]);
		cur_temp = sensor_data_get_value(data[2]);

		/* Monitor */
		monitor(data, nData);
		fprintf(stdout, "\n");

		/* Logging */
		result = logging("data/data_corpus.dat", data, nData);
		if(result) {
			fprintf(stderr, "File is not written.\n");
			return 1;
		}

		/* Timer */
		bsp_DelayUS(100000);
		bcm2835_delay(1000);
	}

	/* Clean-up */
	for(i = 0 ; i < nData ; i++) {
		sensor_data_deinit(&data[i]);
	}
	free(data);
#ifdef SENSOR_BMP180
	bmp180_end();
#endif
#ifdef SENSOR_ADS1256
	ads1256_end();
#endif

	return 0;
}
