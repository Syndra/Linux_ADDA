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
double cur_alti = 0;
double cur_press = 0;

struct tm* cur_time;

char* get_DATETIME_format()
{
	char* res = malloc(30*sizeof(char));
	sprintf(res,"%d-%d-%d %d:%d:%d",
  cur_time->tm_year+1900,
  cur_time->tm_mon+1,
	cur_time->tm_mday,
	cur_time->tm_hour,
	cur_time->tm_min,
	cur_time->tm_sec);

	return res;
}

void timer_routine()
{
	//int a = alarm_off();
	//printf("%f : %f \n", cur_light, cur_temp);

	//if light is once
	//do alarm once



	/* if button pushed */

	/* DataBases go */
	printf("come!\n");
	char *res = malloc(30*sizeof(char));
	res = get_DATETIME_format();
	insert_data(cur_temp, cur_alti, cur_press, cur_light, res);
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
	int nData = 5;
	sensor_data **data = NULL;
	data = (sensor_data *)malloc(sizeof(sensor_data*) * nData);

	for(i = 0 ; i < nData ; i++) {
		data[i] = sensor_data_init();
	}

	/* Initialize */
	ads1256_begin();
	alarm_init(BUZZER_PIN, BUTTON_PIN);
	database_init("localhost", "root", "1111", "4linux");
	set_table("logs");
	cur_time = get_current_time();

	/* Timer function start */
	run_timer(timer_init(), timer_routine, 1, 0, 10000);

	while(1){
		/* Sensing */
		while((ADS1256_Scan() == 0));

		/* Set sensor data */

		sensor_data_set(data[0], "Round", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(0) /1670.0, "mV");
		sensor_data_set(data[1], "Light", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(1) /1670.0, "Lm");
		sensor_data_set(data[2], "Temp", SENSOR_DATA_TYPE_DOUBLE, (ADS1256_GetAdc(2) * (-11.0) )/ 42594.0 + (28423142.0 / 106485.0), "'C");
		sensor_data_set(data[3], "Alti", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(3) /1670.0, "h");
		sensor_data_set(data[4], "Press", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(4) /1670.0, "Pa");

		cur_light = sensor_data_get_value(data[1]);
		cur_temp = sensor_data_get_value(data[2]);
		cur_alti = sensor_data_get_value(data[3]);
		cur_press = sensor_data_get_value(data[4]);

		/* Monitor */
		monitor(data, nData);
		fprintf(stdout, "\n");

		/* Get Datetime */
		cur_time = get_current_time();
		char* timestamp_file = malloc(40*sizeof(char));
		sprintf(timestamp_file, "data/%d_%d_%d_log.dat", cur_time->tm_year+1900, cur_time->tm_mon+1, cur_time->tm_mday);

		/* Logging */
		result = logging(timestamp_file, data, nData);
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
