#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 
#define BUFFER_LENGTH 256               /
static char receive[BUFFER_LENGTH];     
 
int main(){
	
	int ret, fd;
	char stringToSend_1[BUFFER_LENGTH];
	char stringToSend_2[BUFFER_LENGTH];
   
	printf("Opening the regulator device's\n");
	fd = open("/dev/regul_com", O_RDWR);             // Open the device with read/write access
	
	if (fd < 0){
		perror("Failed to open the device...");
		return errno;
	}
	
	printf("Type the voltage value:\n");
	scanf("%[^\n]%*c", stringToSend_1);                

	printf("Send voltage value to device ...\n");
	ret = write(fd, stringToSend_1, strlen(stringToSend_1)); // Send the string to device
	
	if (ret < 0){
		perror("Failed to write the message to the device.");
		return errno;
	}
	printf("Success\n");
	close(fd);
	
	return 0;
}
