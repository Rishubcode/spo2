#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include "serial.h"
#include <string.h>

#define ARDUINO_SLAVE_SPO2  4

char hello[20] ;
char data[]="hello";
int file;
char *bus = "/dev/i2c-1";
char spo2[10] ;
char buf_s[3];
char hr[10] ;
char buf_h[3];


int start_bus()
{
        if((file = open(bus, O_RDWR)) < 0)
        {
                printf("Failed to open the bus. \n");
        //      exit(1);
                return 0;//;FILE_OPEN_ERROR_AMS;
        }
        return 0;
}

float read_i2c(int address)
{
//      start_bus();
        ioctl(file, I2C_SLAVE, address);
        if(read(file,hello, 10) != 10)
        {
                printf("Error : Input/Output error \n");
                return 0;
        }
//                pressure_1 = (data[0] * 256 + data[1]);
  //              pressure2 = ((((pressure_1 - 3277.0) / ((26214.0) / 3.0))-1.5)*70.30);
        //      printf("circuit pressure = %d\n",pressure2);
                return (0);
//close(file);
}
float write_i2c(int address)
{
//      start_bus();
        ioctl(file, I2C_SLAVE, address);
        if(write(file, data, 6)!=0)
        {
                printf("Error : Input/Output error \n");
                return 0;
        }
        //        pressure_1 = (data[0] * 256 + data[1]);
          //      pressure2 = ((((pressure_1 - 3277.0) / ((26214.0) / 3.0))-1.5)*70.30);
        //      printf("circuit pressure = %d\n",pressure2);
                return (0);
/////close(file);
}

int main()
{
	start_bus();
	while(1){
		read_i2c(ARDUINO_SLAVE_SPO2);
		printf(" %s \n",hello);
		for(int i=0;i<3;i++)
			{
				buf_s[i]=hello[i+4];
				buf_h[i]=hello[i+7];
			}
		sprintf(spo2,"K@%s#",buf_s);
		sprintf(hr,"L@%s#",buf_h);

		//strcat(spo2,buf_s);
		//strcat(hr,buf_h);
		printf(" %s \n",spo2);
		printf(" %s \n",hr);
		serial_data_write(spo2);
		serial_data_write(hr);
		//memset(spo2, 0,strlen(spo2));
		//memset(hr, 0,strlen(hr));
		sleep(1);
		}
	return 0;
}
