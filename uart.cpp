#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>
#include<wiringPi.h>

//int msg(char *str)
int main()
{
   int file, count;
   char buf[10];
 char msg_cmd1[] = "AT+CSCA=\"15149931123\"";
char msg_cmd2[] = "AT+CMGS=\"14377796894\""; 
  if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the device.\n");
      return -1;
   }
   struct termios options;
   tcgetattr(file, &options);
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;
   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);
   if (count = write(file,msg_cmd1,strlen(msg_cmd1))<0){
      perror("UART: Failed to write to the output\n");
      return -1;
   }
   write(file, "\n\r", 2);

//read(file,buf,10);

  // fprintf(file,"%s\n",msg_cmd1);
//   fscanf(file,"%s",buf);

printf("here %s ",buf);
//fflush(stdout);

if ((count = write(file,msg_cmd2,sizeof(msg_cmd2)))<0){
      perror("UART: Failed to write to the output\n");
      return -1;
   }
   write(file, "\n\r", 2);

if ((count = write(file,"how are you",20))<0){
      perror("UART: Failed to write to the output\n");
      return -1;
   }
   write(file, "\n\r", 2);

 write(file, "\n\r", 2);
 write(file, "\n\r", 2);

   close(file);
   return 0;
}

