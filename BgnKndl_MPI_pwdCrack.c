/*****************************************************************************
  Password Cracking using MPI
 
  To compile:
     mpicc -o BgnKndl_MPI_pwdCrack BgnKndl_MPI_pwdCrack.c -lrt -lcrypt
     
  To run 3 processes on this computer:
    mpirun -n 3 ./BgnKndl_MPI_pwdCrack 

  =============================================================
        Name: BIGYAN KANDEL  University ID: "1917852"
  =============================================================
*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <crypt.h>
#include <mpi.h>


int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$KB$bZCkQcKiy6TQtxgQQnpdhRf8lz9Ib8MuGMTKaKpIH3ldT2pja9yqFnc1vX4GAfTLpeE26WQrD.oJn1dwwxnL6/",

"$6$KB$Cqph0ugoW8ND3YeYdokR3IOpFbdp10c/E7bHfjujv7R/QhAut7WTerANkmmCWtt7fIjm1ywsoZQ6Dl3RYVdRG." ,

"$6$KB$web5m040YqGT1MDV5HsUAGQZGj4kBEXRuKjujQDlVmI5sy/f6niZOlqmkMzPBEC5jwre.USjM4qOdGQrDmj9d.", 

"$6$KB$L2Djkv.iAMdWtjoGD1LxYRNILhtBavxwfPK6/tfDFwBVtPjJUXbnmht2xCccNtbvhMCl67pilkT5K15nEHPi7/" 
};

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}
  
void kernel_function_AM(char *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space

  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(x='A'; x<='M'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=9999; z++){
	sprintf(plain, "%c%c%04d",x, y, z);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("Instance 1:");
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	 // printf(" %-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }  
}


void kernel_function_NZ(char *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space

  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=9999; z++){
	
	sprintf(plain, "%c%c%04d",x, y, z);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("Instance 2:");
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	 // printf(" %-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }
 
}


int time_difference(struct timespec *start, struct timespec *finish,
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

int main(int argc, char** argv) {
 struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

 
  int size, rank;
int i;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(size != 3) {
    if(rank == 0) {
      printf("This program needs to run on exactly 3 processes\n");
    }
  } else {
    if(rank ==0){

      int x;
    
      MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send(&x, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);


 
    } else if(rank==1){
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(i=0;i<n_passwords;i<i++) {
          kernel_function_AM(encrypted_passwords[i]);
        }
      }
      else{
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(i=0;i<n_passwords;i<i++) {
          kernel_function_NZ(encrypted_passwords[i]);
        }
      }
    }
    MPI_Finalize(); 
 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 

  return 0;
}
