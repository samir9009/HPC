#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <math.h>
#include <mpi.h>
/***********************************************************************
*******
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2
uppercase
  letters and a 2 digit integer. Your personalised data set is included
in the
  code. 

 
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$H8s0k9/1RQ783G9gF69Xkn.MI.Dq5Ox0va/dFlkknNjO7trgekVOjTv1BKCb.nm3vqxmtO2mOplhmFkwZXecz0",
  "$6$KB$VDUCASt5S88l82JzexhKDQLeUJ5zfxr16VhlVwNOs0YLiLYDciLDmN3QYAE80UIzfryYmpR.NFmbZvAGNoaHW.",
  "$6$KB$EsP1JEbzKmbN.CzfjPpWW4cFmaULuLMtlwzZweeoOhv.Lq9abZ4eQaZqSzW1X9GmrC8XI4ND3L78fI9HGFrGX/",
  "$6$KB$Iu4iYgLk4Cuv1Hdc/DTrfNRXVNnKmPPat4bqInq85qs7xNapjF6ZrogA/S88rzpJIWDy27PFI6EzVsg1lL6a80"
};


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crackAM(char *salt_and_encrypted){
  int c, h, u;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space

  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(c='A'; c<='M'; c++){
    for(h='A'; h<='Z'; h++){
      for(u=0; u<=99; u++){
        sprintf(plain, "%c%c%02d", c, h, a); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } /*else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }*/
      }
    }
  }
  printf("%d solutions explored\n", count);
}

void crackNZ(char *salt_and_encrypted){
  int s, a, m;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space

  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(s='N'; s<='Z'; s++){
    for(a='A'; a<='Z'; a++){
      for(m=0; m<=99; m++){
        sprintf(plain, "%c%c%02d", s, a, m); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } /*else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }*/
      }
    }
  }
  printf("%d solutions explored\n", count);
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
int main(int argc, char *argv[]){

 struct timespec start, finish;   
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

 

int size, rank;

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
      
	
    } 
else if (rank == 1){
        int number, i;
      	MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for ( i = 0; i<n_passwords;i<i++){
		crackAM(encrypted_passwords[i]);
	
        }
      }
	else {
      	int number, i;
      	MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for (i = 0; i<n_passwords;i<i++){
		crackNZ(encrypted_passwords[i]);
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


