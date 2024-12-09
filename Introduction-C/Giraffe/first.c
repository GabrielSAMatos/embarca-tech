#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int scanffgets()
{
    int age;
    double gpa;
    char grade;
    char name[20];

    printf("Enter your name: ");
    fgets(name, 20, stdin);

    printf("Enter your grade: ");
    scanf("%c", &grade);

    printf("Enter your age: ");
    scanf("%d", &age);
    
    printf("Enter your gpa: ");
    scanf("%lf", &gpa);


    printf("Your grade is %c.\n", grade);
    printf("Your name is %s.\n", name);
    printf("You are %d years old.\n", age);
    printf("Your gpa is %f.", gpa);

    return 0;
}



int constvariable(){

    const int num = 5;
    printf("%d\n", num);
    //num = 8;
    printf("%d", num);

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