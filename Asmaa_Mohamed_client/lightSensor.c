#include <stdio.h>
#include <unistd.h>
#include "mraa/aio.h"

#define ANALOG_PIN 0
#define DIGITAL_PIN 7
#define THRESHOLD 500

int main ()
{
	mraa_aio_context adc;
	uint16_t value;
	mraa_result_t result;
	mraa_gpio_context gpio;
	
	
	adc= mraa_aio_init(ANALOG_PIN);
	if(adc == NULL)
	{
		
		return "cannot init analog pin";
	}
	
	gpio = mraa_gpio_init(DIGITAL_PIN);
	if(gpio == NULL)
	{
		
		return "cannot init digital pin";
	}
	
	
	
	result = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
	
	if(result!= MRAA_SUCCESS)
	{
		mraa_result_print(result);
		
	}
	else
	{
		printf(" [+] pin %d is initialized as output \n", DIGITAL_PIN);
	}
	
	while(true)
	{
		value = mraa_aio_read(adc);
		fprintf(stdout, "pin A%d recieved %hu .\n", ANALOG_PIN, value);
		if(value < THRESHOLD)
		{
			//result = mraa_gpio_write(gpio , 1);
			//fprintf(stdout , "GPIO 1 \n");
                       
                       return "board2, off";
		}
		else
		{
			result = mraa_gpio_write(gpio, 0);
			//fprintf(stdout , "GPIO 0 \n");
                      
                      return "board2, on";
			
		}
		sleep(1);
	}
	return 0;
}