#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

// small macro to display value in dexadecimal with 2 places
#define MAG_ADDR	0x1e

#define MAG_REG		0x02

#define MAG_X_REG	0x03
#define MAG_Z_REG	0x05
#define MAG_Y_REG	0x07

#define BUFFER_SIZE	40

int main() {

	int file;

	char readBuffer[BUFFER_SIZE];
	char writeBuffer[1] = {0x01};	// what register I want data from

	printf("Starting the LSM303 test application\n");

	if ( (file = open("/dev/i2c-1", O_RDWR)) < 0) {
		perror("failed to open the bus\n");
		return 1;
	}

	if ( ioctl(file, I2C_SLAVE, MAG_ADDR) < 0) {
		perror("failed to connect to the sensor\n");
		return 1;
	}

	// i2cget -y 1 MAG_ADDR MAG_REG	
	if ( write(file, writeBuffer, 1) != 1) {
		perror("Failed to reset the read address\n");
		return 1;
	}

	// where the result of my i2cget is stored	
	if( read(file, readBuffer, BUFFER_SIZE) != BUFFER_SIZE) {
		perror("Failed to read in the buffer\n");
		return 1;
	}

	printf("The Magnetometer Operating Status is: 0x%02x\n", readBuffer[MAG_REG]);
	printf("%02x\n",readBuffer[MAG_X_REG]);
	close(file);
	return 0;
}
