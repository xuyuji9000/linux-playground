#include <stdio.h>
#include <math.h>

int main()
{
    double input = 2.0, output;
    
    double integer; 
    output = modf(sqrt(input), &integer);
    output = output*pow(10.0, 32.0);

    long long int tmp = (long long int) output;
    printf("%lld\n", tmp);
    return 0;
}

