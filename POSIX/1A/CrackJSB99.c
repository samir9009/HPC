#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <math.h>


int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$51CtT20QhxYFaySrvWILAaTqExQUjACDYdzWtVCO4MLDwldbIfL4JOvef0kJlw/2EF2FT1RTboM.7Ubspxo2N1",
  "$6$KB$2y7rUoL1ZYcm6HZFi1RyG3lxYkGJnsGrwr4tw0Flk3.iUFNvRJRlSUsLdFZF2kkqQOXVD3IKiz3PmhSo32AsA0",
  "$6$KB$GIkiC.83K5a8w.K8QN0CraOxQWqBMT7Zg7wCpg6tnw8qif8ixEK6ks3v7AfCC5L/LGghJlyrxfDigcb2vpIkq0",
  "$6$KB$eLSNKH/oufGrRDDNHx3qUNSL4/KRCTK4GaeVfy2gsOlDK3Nf2juGygydgsJosVXGCKhY/DeFE4k1KvpojnwjT0"
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
