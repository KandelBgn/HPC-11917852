#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

/******************************************************************************
 This parogram cracks an encrypted password using a simple"brute force" algorithm. 
 Works on passwords that consist only of 2 uppercase letters and a 2 digit integer.
 Two threads are used in this program to crack the passwords. One Kernal_Function_AM 
  and other is Kernal_Function_MZ which crack password initialize from A to M and
  N to Z respectively.
 Compile with:
    cc -o pthread_passwordCrack pthread_passwordCrack.c -lcrypt -pthread

  To analyse, the result is redirect to the txt file.
    ./pthread_passwordCrack > BgnKndl_pthread_passwordCrack.txt

  Here, the code can executed 10 times and can greap time in second inexcel file,
    ./mr.py ./pthread_passwordCrack | grep Time | awk -F ' ' '{print $6}' | sed 's/s//'> BgnKndl_MeanTime_pthread_passwordCrack.csv
    
    
   =============================================================
        Name: BIGYAN KANDEL  University ID: "1917852"
   =============================================================

******************************************************************************/


int n_password = 4;
 pthread_t thread_1;
 pthread_t thread_2;
int count;
char *encrypted_passwords[] = {
  "$6$KB$6SsUGf4Cq7/Oooym9WWQN3VKeo2lynKV9gXVyEG4HvYy1UFRx.XAye89TLp/OTcW7cGpf9UlU0F.cK/S9CfZn1",
  "$6$KB$1ocIiuN6StvEskjsYoYBid/gy8zXybieNCm9uM94nRw.ik9I04W3DJg0E52dswnozLmM0BIlzRZxgd.TleBwp1",
  "$6$KB$L4mWcpv6rMAbZdxfSsuAL2UZhbJ4vSGAAxk.vEcRKvIuPpwcSRKHzi3BXzWQWaH1p1ubwaFl.06CRQv6bVo3M1",
  "$6$KB$OpOIZac00sMBfYemANRTO3lKNZCFLegKAMakI3i2fk78/vZgo01X5mdG/1R1K0Ohs0V1AuxfOK7KY.th3dInb0"
};

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

//Crack password initialize from A to M
void *Kernal_Function_AM(void *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='M'; x++){ //first thread starts to crack from A to M
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          //printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          //printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }pthread_exit(NULL);
}

//Crack password initialize from N to Z
void *Kernal_Function_NZ(void *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='N'; x<='Z'; x++){ //first thread starts to crack from N to M
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          //printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          //printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }pthread_exit(NULL);
}

//this functions returns the time difference between start and end of program executions.
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

//Main functions
int main(int argc, char *argv[]){
 int i;
 struct timespec start, finish;
 long long int time_elapsed;

 clock_gettime(CLOCK_MONOTONIC, &start);

 for (int i=0; i<n_password;i++){
  pthread_create(&thread_1,NULL,Kernal_Function_AM,encrypted_passwords[i]);
  pthread_create(&thread_2,NULL,Kernal_Function_NZ,encrypted_passwords[i]);
  pthread_join(thread_1,NULL);
  pthread_join(thread_2,NULL);
 }
 clock_gettime(CLOCK_MONOTONIC, &finish);

 time_difference(&start, &finish, &time_elapsed);
 printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 

  return 0;
}







