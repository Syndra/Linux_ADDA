#include <stdio.h>
#include <stdlib.h>
#include <bmp180.h>
#include <ads1256.h>
#include <bcm2835.h>
#include <monitor.h>
#include <logger.h>
#include <sensor_data.h>

//#define SENSOR_BMP180
//#define SENSOR_ADS1256

int main(){
	uint8_t id;
int32_t adc[8];
int32_t volt[8];
uint8_t i;
uint8_t ch_num;
int32_t iTemp;
uint8_t buf[3];
if (!bcm2835_init())
		return 1;
/*
bcm2835_spi_begin();
bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST );      // The default
bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);                   // The default
bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1024); // The default
*/

bcm2835_spi_begin();
bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);   //default
bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);                //default
bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);//default

bcm2835_gpio_fsel(SPICS, BCM2835_GPIO_FSEL_OUTP);//
bcm2835_gpio_write(SPICS, HIGH);
bcm2835_gpio_fsel(DRDY, BCM2835_GPIO_FSEL_INPT);
bcm2835_gpio_set_pud(DRDY, BCM2835_GPIO_PUD_UP);
//ADS1256_WriteReg(REG_MUX,0x01);
//ADS1256_WriteReg(REG_ADCON,0x20);
// ADS1256_CfgADC(ADS1256_GAIN_1, ADS1256_15SPS);
id = ADS1256_ReadChipID();
printf("\r\n");
printf("ID=\r\n");
if (id != 3)
{
printf("Error, ASD1256 Chip ID = 0x%d\r\n", (int)id);
}
else
{
printf("Ok, ASD1256 Chip ID = 0x%d\r\n", (int)id);
}
ADS1256_CfgADC(ADS1256_GAIN_1, ADS1256_15SPS);
	 ADS1256_StartScan(0);
ch_num = 8;
//if (ADS1256_Scan() == 0)
//{
	//continue;
//}
while(1)
{
		 while((ADS1256_Scan() == 0));
for (i = 0; i < ch_num; i++)
{
	adc[i] = ADS1256_GetAdc(i);
						 volt[i] = (adc[i] * 100) / 167;
}

for (i = 0; i < ch_num; i++)
{
							buf[0] = ((uint32_t)adc[i] >> 16) & 0xFF;
							buf[1] = ((uint32_t)adc[i] >> 8) & 0xFF;
							buf[2] = ((uint32_t)adc[i] >> 0) & 0xFF;
							printf("%d=%02X%02X%02X, %8ld", (int)i, (int)buf[0],
										 (int)buf[1], (int)buf[2], (long)adc[i]);

							iTemp = volt[i];	/* uV  */
			if (iTemp < 0)
			{
				iTemp = -iTemp;
												printf(" (-%ld.%03ld %03ld V) \r\n", iTemp /1000000, (iTemp%1000000)/1000, iTemp%1000);
			}
			else
			{
												printf(" ( %ld.%03ld %03ld V) \r\n", iTemp /1000000, (iTemp%1000000)/1000, iTemp%1000);
			}

}
	printf("\33[%dA", (int)ch_num);
bsp_DelayUS(100000);
	}
bcm2835_spi_end();
bcm2835_close();

return 0;
// 	int i = 0;
// 	int result = 0;
//
// 	/* Data Storage Preparation */
// 	int nData = 2;
// 	sensor_data **data = NULL;
// 	data = (sensor_data *)malloc(sizeof(sensor_data*) * nData);
//
// 	for(i = 0 ; i < nData ; i++) {
// 		data[i] = sensor_data_init();
// 	}
//
// 	/* Initialize */
// #ifdef SENSOR_BMP180
// 	if(!bmp180_begin()) return 1;
// #endif
// #ifdef SENSOR_ADS1256
// 	if(!ads1256_begin()) return 1;
// #endif
//
// 	while(1){
// 		/* Sensing */
// #ifdef SENSOR_BMP180
// 		sensor_data_set(data[0], "temp", SENSOR_DATA_TYPE_DOUBLE, read_temperature(), "C");
// 		sensor_data_set(data[1], "press", SENSOR_DATA_TYPE_DOUBLE, read_pressure()/100.0, "Pa");
// 		sensor_data_set(data[2], "alti", SENSOR_DATA_TYPE_DOUBLE, read_altitude(), "h");
// #endif
// #ifdef SENSOR_ADS1256
// 		while((ADS1256_Scan() == 0));
// 		for (i = 0; i < nData; i++)
// 		{
// 			sensor_data_set(data[i], "???", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(i) /1670.0, "mV");
// 		}
// #endif
//
// 		/* Monitor */
// 		monitor(data, nData);
// 		fprintf(stdout, "\n");
//
// 		/* Logging */
// 		result = logging("data/data_corpus.dat", data, nData);
// 		if(result) {
// 			fprintf(stderr, "File is not written.\n");
// 			return 1;
// 		}
//
// 		/* Timer */
// 		bsp_DelayUS(100000);
// 		bcm2835_delay(1000);
// 	}
//
// 	/* Clean-up */
// 	for(i = 0 ; i < nData ; i++) {
// 		sensor_data_deinit(&data[i]);
// 	}
// 	free(data);
// #ifdef SENSOR_BMP180
// 	bmp180_end();
// #endif
// #ifdef SENSOR_ADS1256
// 	ads1256_end();
// #endif
//
// 	return 0;
}
