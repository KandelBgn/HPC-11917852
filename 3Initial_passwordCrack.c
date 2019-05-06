#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/******************************************************************************
  This program crack an encrypted passwords using a simple "brute force" 
    algorithm.Works on passwords that consist only of 3 uppercase letters 
    and a 2 digit integer.

  Compile with:
    cc -o 3Initial_passwordCrack 3Initial_passwordCrack.c -lcrypt

  To analyse the result, redirictiong result in txt file.
    ./3Initial_passwordCrack > BgnKndl_3InitialPasswordCrack.txt
	
  This program is executed only one time. This programs claculates the time
   required to decrypt the 3 initialize uppercase letter and 2 digits number
   and also find the plane text.

  Password is: BGN45

  Here, the code can executed 10 times and can greap time in second in excel file,
    ./mr.py ./3Initial_passwordCrack | grep Time | awk -F ' ' '{print $6}' | sed 's/s//'> BgnKndl_MeanTime3Initial_passwordCrack.csv

   =============================================================
        Name: BIGYAN KANDEL  University ID: "1917852"
   =============================================================

******************************************************************************/
char *encrypted_passwords = {
  "$6$KB$EQ.KOnnaMVcIjoo7XKPQ6qee1vpShrdQL19YlO1pC51MCqyG0qCh2p7McRbYcmNKj4KgVuZfJcy3cObC5nbUz0"  
};

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void passwordCrack(char *salt_and_encrypted){
  int t, x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(t='A'; t<='Z'; t++){
    for(x='A'; x<='Z'; x++){
      for(y='A'; y<='Z'; y++){
        for(z=0; z<=99; z++){
          sprintf(plain, "%c%c%c%02d", t, x, y, z); 
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
            printf("#%-8d%s %s\n", count, plain, enc);
          } else {
            printf(" %-8d%s %s\n", count, plain, enc);
          }
        }
      }
    }
  }pthread_exit(NULL);
}

// Calculating the time difference.
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

// main function.
int main(int argc, char *argv[]){

  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  passwordCrack(encrypted_passwords);
  clock_gettime(CLOCK_MONOTONIC, &finish);

  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 
  return 0;
}




