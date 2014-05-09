/*
 *Read 4kB of data from (1KB_data.txt) 1 million times.
 *Using syscall: open(2), read(2), lseek(2)
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

/*
 *Too big array that cause stack overflow,
 *so I use staic to define it as a global one. 
 *so it may take some seconds to compile.
 */
static int buf[1024];

int main()
{
  int filedir;
  filedir = open("4KB_data.txt",O_WRONLY | O_APPEND);

  if(filedir == -1)
    {
      perror("File cannot be opened!");
    }

  else
    {
      long i;
      for(i=0; i<1024; i++)
	{
	  buf[i]=1;//buf data initialization.
	}
      
      unsigned long int count_begin, count_end;

      count_begin=RDTSC();
      
      long j;
      for (j=0; j<1000000; j++)
	{
	  lseek(filedir, 0, SEEK_SET);
	  read(filedir, buf, sizeof(buf));
	}
     
      count_end = RDTSC();

      printf("CPU Tick Time: %lu\n", count_end-count_begin);
    }
  
  close(filedir);

  return 0;
}
