#include <sensor_data.h>
#include <stdlib.h>
#include <string.h>

/* Initializer */
sensor_data *sensor_data_init() {
	sensor_data *instance = (sensor_data*)malloc(sizeof(sensor_data));
	if(instance == NULL) return NULL;	// ERROR is not handled properly

	return instance;
}

void sensor_data_deinit(sensor_data **instance) {
	free(instance);
	*instance = NULL;
}

/* Getter, Setter */
char *sensor_data_get_name(sensor_data *data) {
	/* Parameter Verification */
	if(data == NULL) return NULL;
	
	return data->name;
}

int sensor_data_get_type(sensor_data *data) {
	/* Parameter Verification */
	if(data == NULL) return 0;
	
	return data->type;
}

double sensor_data_get_value(sensor_data *data) {
	/* Parameter Verification */
	if(data == NULL) return 0;
	
	return data->value;
}

char *sensor_data_get_unit(sensor_data *data) {
	/* Parameter Verification */
	if(data == NULL) return NULL;
	
	return data->unit;
}

void sensor_data_set(sensor_data *data, char *paramName, int paramType, double paramValue, char *paramUnit) {
	/* Parameter Verification */
	if(data == NULL) return;

	/* Initialize */
	int i = 0;
	memset(data->name, 0, SENSOR_DATA_NAME_LEN);
	memset(data->unit, 0, SENSOR_DATA_UNIT_LEN);

	/* Name */
	if(paramName != NULL && strlen(paramName) < SENSOR_DATA_NAME_LEN) {
		strncpy(data->name, paramName, strlen(paramName));
	}

	/* Type */
	data->type = paramType;

	/* Value */
	data->value = paramValue;

	/* Unit */
	if(paramUnit != NULL && strlen(paramUnit) < SENSOR_DATA_UNIT_LEN) {
		strncpy(data->unit, paramUnit, strlen(paramUnit));
	}
}
