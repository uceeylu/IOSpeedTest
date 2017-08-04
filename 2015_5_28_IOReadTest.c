/*
adapted from "fwt_in_ram.c"
basic implementation for report code
measure total time for 100 runs for sizes (long long):
 2^{22}, 34 sec,  12 sec (spiral - check real memory cost)
 2^{24},149 sec (2min), 51 sec (spiral)
 2^{26},635 sec (8min)
 2^{28},2707 sec (.5Hr) gadd: 16 sec/one run
 2^{30},11502 sec (2Hr) gadd: 68 sec/one run, spiral 49 sec/one run

 2^{32}, est. 46000 sec/100 runs (not real result)
         est. ext-memory alg. 51200 sec/one run
*/

/*
my laptop
my code 40s(all zero input),49s (rand input)

spiral sequential installation
10s(all zero input), 18s(rand input) now 21s(rand input)

parallel installation
parallel 12s(zero input), sequential execution 18s(zero input)
sequential execution 29s(rand input)
sequential execution(bug corrected) 20s(rand input)
parallel execution(bug corrected) 9s(zero input)
parallel execution(bug corrected) 28s(rand input) <= still have bugs

ucl(2^22,zero inputs):
ref. 1.413e-1 (bug corrected: 6.47e-2)
2-core, 7.723e-2 (bug corrected: 3.548e-2)
4-core, 4.031e-2

2-core bug corrected: 4.348e+00 for input x[i] = i*1.0

*/

/*
external-memory:
last 3 rounds:
ext-fwt.c, 7200s, 8G(BL=29)
fwt-g.c, rd.30-32, 4862s (BL=24) 1600*32 = 51200 s
         rd.20-22, 2190s (BL=24) 700*3

BL=24,FFT_L=32
Rd. 25: time 1922.00 sec
Rd. 26: time 1968.00 sec
Rd. 27: time 1911.00 sec
Rd. 28: time 1911.00 sec
Rd. 29: time 1950.00 sec
Rd. 30: time 1834.00 sec
Rd. 31: time 1896.00 sec
Rd. 32: time 1855.00 sec


         previous complete timing results (running on different machine)
         43597 s (12.1Hrs)
         56408 s  15.7Hrs - more common
*/

#define _FILE_OFFSET_BITS  64

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

unsigned A[1]={18};
unsigned L=29, BL;
long long *buf0;



main(){
unsigned i,j,k;
int fp0;
time_t startT, stopT;    



printf("L=%d:\n", L);


unsigned k1,k2;


fp0=open("gg",O_RDONLY);
if(fp0==-1)
{   
   printf("file open err\n");exit(1);
}


for(i=0;i<1;i++)
{

   BL=A[i];
   printf("BL=%d, ", BL);

   buf0=(long long *)malloc(sizeof(long long)<<BL);
   if(!buf0)
   { 
      printf("memory allocation err\n");exit(1);
   }

   startT = time(NULL);


   for(k1=0;k1<(1<<(L-BL));k1++)
   {
    
      if(read(fp0,buf0,(8<<BL))!=(8<<BL))      
      {
         printf("file read err\n");exit(1);
      }

      for(k2=0;k2<(1<<BL);k2++)buf0[k2]+=random();
   
   }

   stopT = time(NULL);
   printf("time: %.2f s\n", difftime(stopT,startT));

   free(buf0);
}


close(fp0);

}


