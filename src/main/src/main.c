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

//#define SENSOR_BMP180
#define SENSOR_ADS1256

void test()
{
	puts("Hello, world!\n");
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
	int nData = 2;
	sensor_data **data = NULL;
	data = (sensor_data *)malloc(sizeof(sensor_data*) * nData);

	for(i = 0 ; i < nData ; i++) {
		data[i] = sensor_data_init();
	}

	/* Initialize */
	ads1256_begin();

	/* Timer test */
	run_timer(timer_init(), test, 1, 0, 1000000);

	while(1){
		/* Sensing */
		while((ADS1256_Scan() == 0));

		/* TEST */

		for (i = 0; i < nData; i++)
		{
			sensor_data_set(data[i], "???", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(i) /1670.0, "mV");
		}

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
