/*
 *Write 1GB of data to a single new file (data.txt).
 */
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

unsigned long int RDTSC (void)
{
  unsigned int low, hi;
  asm volatile ("cpuid \n\t" "rdtsc \n\t": "=a" (low), "=d" (hi) ::);
  return((unsigned long int) hi << 32) | low;
}


 /*Too big array may cause stack overflow,
 *so I use staic to define it as a global one. 
 *Thus it may take some seconds to compile c code.
 */
static int buf[1024/4];
static char FileName[10];

int main()
{
  /*buf data initialization .*/
  long long i;
  for(i=0; i<1024/4; i++)
    {
      buf[i]=1;
    }
  
  unsigned long int count_begin, count_end;
  count_begin=RDTSC();//Start!

  /*create K plaint text files, and each file name is stored in name[].*/
  long k;
  char name[30];
  
  for(k=0; k<1000000; k++)
    {
      sprintf(name, "%lu", k);/*Convert long int k to char*/
      
      int filedir;
      filedir = open(name, O_WRONLY | O_CREAT | O_EXCL, 0644);

      if(filedir == -1)
	{
	  perror("File cannot be opened!");
	}
      
      else
	{
	  write(filedir, buf, sizeof(buf));
	}
      
      close(filedir);
    }

  count_end = RDTSC();//End!
  printf("CPU Tick Time: %lu\n", count_end-count_begin);
  
  return 0;
}
