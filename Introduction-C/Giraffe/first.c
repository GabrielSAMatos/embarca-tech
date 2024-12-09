#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{

    return 0;
}

int callFunction()
{

    sayHi("Grabiel", 25);
    sayHi("Matos", 25);
    sayHi("Jon", 99);


}

void sayHi(char name[], int age)
{

    printf("Hello, %s. You are %d years old\n", name, age);
}

void array()
{

    int luckyNumbers[10];

    luckyNumbers[1] = 20;

    printf("%d", luckyNumbers[0]);

}

void twoParametersInScanf()
{

    char color[20], plural[20], celebrityF[20], celebrityL[20];

    printf("Enter an color: ");
    scanf("%s", color);

    printf("Enter an plural-noun: ");
    scanf("%s", plural);
    
    printf("Enter an celebrity: ");
    scanf("%s %s", celebrityF, celebrityL);

    printf("\n");
    printf("Roses are %s\n", color);
    printf("%s are blue\n", plural);
    printf("I love %s %s\n", celebrityF, celebrityL);

}

void summ()
{
    double num1, num2;

    printf("Enter first number: ");
    scanf("%lf", &num1);

    printf("Enter second number: ");
    scanf("%lf", &num2);

    printf("The sum of %lf and %lf is: %lf", num1, num2, num1 + num2);

}

void scanffgets()
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

}

void constvariable(){

    const int num = 5;
    printf("%d\n", num);
    //num = 8;
    printf("%d", num);

}
/*
    Comentarios em C #fe
*/
void powsqrt()
{
    printf("%f \n", pow(2, 3));
    printf("%f", sqrt(4));
    //ceil arredonda pra cima
    //floor arredonda pra baixo
}

void sdfc()
{
    int favInt = 7;
    double favDoub = 7.7;
    char favChar = 'g';

    printf("My favorite %s is %d and %f\n", "number", favInt, favDoub);
    printf("and my favorite char is %c", favChar);


}

void dataTypes()
{
    int age = 25;
    double gpa = 3.6;
    char grade = 'G';
    char name[] = "Gabriel Matos";
}

void variable()
{
    char name[] = "Grabiel";
    int age = 24;

    printf("There once was a man named %s\n", name);
    printf("he was %d years old\n", age);
    age = 25;
    printf("He really liked the name %s\n", name);
    printf("but did not like being %d.\n", age);

}

void triangle()
{
    printf("   /|\n");
    printf("  / |\n");
    printf(" /  |\n");
    printf("/___|\n");

}