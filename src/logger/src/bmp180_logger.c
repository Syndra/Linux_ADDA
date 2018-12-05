#include <bmp180_logger.h>
#include <stdio.h>

int logging(char *path, float temp, float press, float alti) {
	/* Verification */
	if(path == NULL) return 1;

	FILE *file = fopen(path, "a");
	
	/* Validation */
	if(file == NULL) return 1;

	fprintf(file, "%.2f,%.2f,%.2f\n", temp, press, alti);

	fclose(file);

	return 0;
}

