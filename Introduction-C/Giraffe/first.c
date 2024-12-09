#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(){



    return 0;
}

/*
    Comentarios em C #fe
*/


int powsqrt()
{
    printf("%f \n", pow(2, 3));
    printf("%f", sqrt(4));
    //ceil arredonda pra cima
    //floor arredonda pra baixo
    return 0;
}

int sdfc()
{
    int favInt = 7;
    double favDoub = 7.7;
    char favChar = 'g';

    printf("My favorite %s is %d and %f\n", "number", favInt, favDoub);
    printf("and my favorite char is %c", favChar);


    return 0;
}

int dataTypes()
{
    int age = 25;
    double gpa = 3.6;
    char grade = 'G';
    char name[] = "Gabriel Matos";

return 0;
}

int variable()
{
    char name[] = "Grabiel";
    int age = 24;

    printf("There once was a man named %s\n", name);
    printf("he was %d years old\n", age);
    age = 25;
    printf("He really liked the name %s\n", name);
    printf("but did not like being %d.\n", age);

    return 0;
}

int triangle()
{
    printf("   /|\n");
    printf("  / |\n");
    printf(" /  |\n");
    printf("/___|\n");

    return 0;
}