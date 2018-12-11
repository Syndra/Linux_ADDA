#include <sensor_data.h>
#include <stdio.h>

int logging(char *path, sensor_data **data, int len) {
	int i;
	FILE *file = fopen(path, "a");
	for(i = 0 ; i < len ; i++) {
		fprintf(file, "%.2f", data[i]->value);
		if(i < len-1) fprintf(file, ",");
	}
	fprintf(file, "\n");
	fclose(file);

	return 0;
}
