#define _FILE_OFFSET_BITS  64

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

unsigned A[1]={24};
unsigned L=32, BL;
long long *buf0;



main(){
unsigned i,j,k;
int fp0;
time_t startT, stopT;    


startT = time(NULL);
srandom(startT);


printf("L=%d:\n", L);


unsigned k1,k2;


for(i=0;i<1;i++)
{

   BL=A[i];
   printf("BL=%d, ", BL);

   buf0=(long long *)malloc(sizeof(long long)<<BL);
   if(!buf0)
   { 
      printf("memory allocation err\n");exit(1);
   }

   

   fp0=open("gg_L32",O_WRONLY|O_SYNC);
   if(fp0==-1)
   {   
      printf("file open err\n");exit(1);
   }

   startT = time(NULL);


   for(k1=0;k1<(1<<(L-BL));k1++)
   {
    
      for(k2=0;k2<(1<<BL);k2++)buf0[k2]=random();

      if(write(fp0,buf0,(8<<BL))!=(8<<BL))      
      {
         printf("file write err\n");exit(1);
      }
      
   
   }

   stopT = time(NULL);
   printf("time: %.1f s\n", difftime(stopT,startT));

   free(buf0);close(fp0);

}


}


