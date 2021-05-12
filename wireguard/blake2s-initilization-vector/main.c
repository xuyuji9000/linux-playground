// This program calculate the initialization vector from prime number 2.

#include <stdio.h>
#include <math.h>

#define PRIME_NUMBER 2.0

int main()
{
    double output;
    
    double integer; 
    
    // Get fraction part of the sqaure root
    output = modf(sqrt(PRIME_NUMBER), &integer);
    output = output*((long)1<<32);

    printf("%lx\n", (long int)output);
    return 0;
}
