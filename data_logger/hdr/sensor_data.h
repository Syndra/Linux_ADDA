#ifndef __SENSOR_DATA_H__
#define __SENSOR_DATA_H__

#define SENSOR_DATA_TYPE_DOUBLE 1

#define SENSOR_DATA_NAME_LEN 10
#define SENSOR_DATA_UNIT_LEN 5

typedef struct sensor_data {
	char name[SENSOR_DATA_NAME_LEN];
	int type;
	double value;
	char unit[SENSOR_DATA_UNIT_LEN];
} sensor_data;

/* Initializer */
sensor_data *sensor_data_init();
void sensor_data_deinit(sensor_data **instance);

/* Getter, Setter */
char *sensor_data_get_name(sensor_data *data);
int sensor_data_get_type(sensor_data *data);
double sensor_data_get_value(sensor_data *data);
char *sensor_data_get_unit(sensor_data *data);
void sensor_data_set(sensor_data *data, char *paramName, int paramType, double paramValue, char *paramUnit);

#endif
