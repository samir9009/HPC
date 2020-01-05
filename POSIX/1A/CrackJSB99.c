#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <math.h>


int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$JeVM1k77Et.CgxeHCXl3rtIvM4Mz5Qmfdjy4hdoXQjBbq2sZ8Hy0nLut/aUIEGyxqfCb9lSF9qsoTSZ4c2zTJ.",
  "$6$KB$QHAnM.aHp5I4tJzC.IaZPZkZ4mEu1L9vcYv23jCpnka5eyqaXEu8qmENr/qUsIQftMVYmGNdtjBTC48Ubr7GI0",
  "$6$KB$wEySWhqIQp4sQpLka/aTQ5xC0zaGubZGSQLYvvXz6aRmmDi.WAs168q6M8mkjHRrl0Vb6h4El5pQKCEuDK.HF0",
  "$6$KB$LiSz6YVe0xEZa/IKf6PpRB0M9qenzQOt6jdRuZOpptxoMPT9mIQ9SpsDxTnm5HwF7tkBvIbTSc.XU92FrVBdX1"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crack(char *salt_and_encrypted){
  int e, f, g, h;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for 
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(e='A'; e<='Z'; e++){
    for(f='A'; f<='Z'; f++){
      for(g='A'; g<='Z'; g++){
	for(h=0; h<=99; h++){
        sprintf(plain, "%c%c%c%02d", e, f, g, h); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
	  
	  }
	else{printf(" %-8d%s %s\n", count, plain, enc);}
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
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


int main(int argc, char *argv[]){
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  int i;
  
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }

   clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 

  return 0;
}
