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

/*
 *Too big array that cause stack overflow,
 *so I use staic to define it as a global one. 
 *so it may take some seconds to compile.
 */
static int buf[1024*1024*1024/4];

int main()
{
  int filedir;/*open and create .txt file if it doesn't exit.*/
  filedir = open("1GB_data.txt",O_WRONLY | O_CREAT | O_EXCL,0644);

  if(filedir == -1)
    {
      perror("File cannot be opened!");
    }

  else
    {
      long long i;
      for(i=0; i<1024*1024*1024/4; i++)
	{
	  buf[i]=1;//(static) buf data initialization.
	}
      
      unsigned long int count_begin, count_end;
     
      count_begin=RDTSC(); 
      write(filedir, buf, sizeof(buf));
      count_end = RDTSC();

      printf("CPU Tick Time: %lu\n", count_end-count_begin);
    }
  
  close(filedir);

  return 0;
}
