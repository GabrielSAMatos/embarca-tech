#include "stdio.h"

int main()
{
    int n1, n2, pow = 1;
    
    printf("Enter first number:");
    scanf("%d", &n1);
    printf("Enter second number:");
    scanf("%d", &n2);

    for(int i = 1; i <= n2; i++)
    {
        pow *= n1;
        
    }

    printf("%d", pow);
    
}