#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>
#include<wiringPi.h>

	void my_delay_func(long DELAY_TIME)
{
for (long jj=0; jj <= DELAY_TIME; jj++);
}
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

   // send msg cmd1 to gsm module (open message centre)
   if (count = write(file,msg_cmd1,strlen(msg_cmd1))<0){
      perror("UART: Failed to write to the output\n");
      return -1;
   }
   write(file, "\n\r", 2);
my_delay_func(2000000);
   //read(file,buf,10);

  // fprintf(file,"%s\n",msg_cmd1);
  //   fscanf(file,"%s",buf);

  //printf("here %s ",buf);
  //fflush(stdout);
  

 // send msg cmd2 to gsm module (specifies recipient)
if ((count = write(file,msg_cmd2,sizeof(msg_cmd2)))<0){
      perror("UART: Failed to write to the output\n");
      return -1;
   }
   write(file, "\n\r", 2);
 my_delay_func(2000000);

 // send the actual msg 
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

