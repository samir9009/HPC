#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/****************************************************************************
  This program gives an example of a poor way to implement a password cracker
  in CUDA C. It is poor because it acheives this with just one thread, which
  is obviously not good given the scale of parallelism available to CUDA
  programs.
  
  The intentions of this program are:
    1) Demonstrate the use of __device__ and __global__ functions
    2) Enable a simulation of password cracking in the absence of library 
       with equivalent functionality to libcrypt. The password to be found
       is hardcoded into a function called is_a_match.   

  Compile and run with:
    nvcc -o CrackAZ99Cuda CrackAZ99Cuda.cu
    ./CrackAZ99Cuda
   
  Dr Kevan Buckley, University of Wolverhampton, 2018
*****************************************************************************/

/****************************************************************************
  This function returns 1 if the attempt at cracking the password is 
  identical to the plain text password string stored in the program. 
  Otherwise,it returns 0.
*****************************************************************************/

__device__ int is_a_match(char *attempt) {
	char mypassword1[] = "SA1234";
	char mypassword2[] = "MI4567";
	char mypassword3[] = "RC7890";
	char mypassword4[] = "HA2345";


	char *p = attempt;
	char *r = attempt;
	char *a = attempt;
	char *t = attempt;
	char *p1 = mypassword1;
	char *p2 = mypassword2;
	char *p3 = mypassword3;
	char *p4 = mypassword4;

	while(*p == *p1) { 
		if(*p == '\0') 
		{
			printf("Password: %s\n",mypassword1);
			break;
		}

		p++;
		p1++;
	}
	
	while(*r == *p2) { 
		if(*r == '\0') 
		{
			printf("Password: %s\n",mypassword2);
			break;
		}

		r++;
		p2++;
	}

	while(*a == *p3) { 
		if(*a == '\0') 
		{
			printf("Password: %s\n",mypassword3);
			break;
		}

		a++;
		p3++;
	}

	while(*t == *p4) { 
		if(*t == '\0') 
		{
			printf("Password: %s\n",mypassword4);
			return 1;
		}

		t++;
		p4++;
	}
	return 0;

}

__global__ void  kernel() {
	char i1,i2,i3,i4;

	char password[7];
	password[6] = '\0';

	int i = blockIdx.x+65;
	int j = threadIdx.x+65;
	char firstMatch = i; 
	char secondMatch = j; 

	password[0] = firstMatch;
	password[1] = secondMatch;
	for(i1='0'; i1<='9'; i1++){
		for(i2='0'; i2<='9'; i2++){
			for(i3='0'; i3<='9'; i3++){
				for(i4='0'; i4<='9'; i4++){
					password[2] = i1;
					password[3] = i2;
					password[4] = i3;
					password[5] = i4; 
					if(is_a_match(password)) {
					} 
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

	kernel <<<26,26>>>();
	cudaThreadSynchronize();

	clock_gettime(CLOCK_MONOTONIC, &finish);
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9)); 

	return 0;
}


