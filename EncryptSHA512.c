#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
/******************************************************************************
  This program is used to set challenges for password cracking programs. 
  Encrypts using SHA-512.
  
  Compile with:
    cc -o EncryptSHA512 EncryptSHA512.c -lcrypt
    
  To encrypt the password "BGN45":
    ./EncryptSHA512 BGN45

   =============================================================
        Name: BIGYAN KANDEL  University ID: "1917852"
   =============================================================
******************************************************************************/
#define SALT "$6$KB$"

int main(int argc, char *argv[]){
  
  printf("%s\n", crypt(argv[1], SALT));

  return 0;
}
