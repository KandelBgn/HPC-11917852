#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/****************************************************************************
 This is a program of password cracking of two alphabets and four digits using cuda. 

 
 Compile BY:
    nvcc -o 2Initial4Digit_pwdCrack 2Initial4Digit_pwdCrack.cu 
  
  Run BY:
    ./2Initial4Digit_pwdCrack >2Initial4Digit_Password
 
  To calculate mean time execute the program 10 times and grep time in second only csv file:
   ./mr.py ./2Initial4Digit_pwdCrack | grep Time | awk -F ' ' '{print $6}' | sed 's/s//'> BgnKndl_MeanTime_2Initial4Digit_pwdCrack.csv
  
   =============================================================
        Name: BIGYAN KANDEL  University ID: "1917852"
   =============================================================
********************************************************************************/


__device__ void displayResult(char *password)
{
 printf("Matching password is: %s\n",password);
}

__device__ void is_a_match(char *attempt) {
  char plain_password_1[] = "BI1996";
  char plain_password_2[] = "GY2053";
  char plain_password_3[] = "AN9867";
  char plain_password_4[] = "BK9658";

//send values from kernal as attempt
  char *a = attempt;
  char *b = attempt;
  char *c = attempt;
  char *d = attempt;
  char *p1 = plain_password_1;
  char *p2 = plain_password_2;
  char *p3 = plain_password_3;
  char *p4 = plain_password_4;

//Checking each alphabets of password1 with attempt as a 
  while(*a == *p1) { 
   if(*a == '\0') 
    {
        displayResult(plain_password_1);
      break;
    }

    a++;
    p1++;
  }
	//Checking each alphabets of password2 with attempt as b
  while(*b == *p2) { 
   if(*b == '\0') 
    {
        displayResult(plain_password_2);
      break;
    }

    b++;
    p2++;
  }

//Checking each alphabets of password3 with attempt as c
  while(*c == *p3) { 
   if(*c == '\0') 
    {
	displayResult(plain_password_3);
      break;
    }

    c++;
    p3++;
  }

//Checking each alphabets of password4 with attempt as d
  while(*d == *p4) { 
   if(*d == '\0') 
    {
       displayResult(plain_password_4);
      break;
    }

    d++;
    p4++;
  }
  return;

}


__global__ void  kernel() {
char w,x,y,z;
  
  char password[7];
  password[6] = '\0';

int i = blockIdx.x+65;
int j = threadIdx.x+65;
char firstAlp = i; 
char secondAlp = j; 
    
password[0] = firstAlp;
password[1] = secondAlp;
  for(w='0'; w<='9'; w++){
   for(x='0'; x<='9'; x++){
    for(y='0'; y<='9'; y++){
     for(z='0'; z<='9'; z++){
	password[2] = w;
	password[3] = x;
	password[4] = y;
	password[5] = z; 
      is_a_match(password); // calling device function passing each password
     }
    }
   }
  }

}

int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);
  
  dim3 block_Dim(26,1,1), thread_Dim(26,1,1);        
  kernel <<<block_Dim,thread_Dim>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9)); 

  return 0;
}


