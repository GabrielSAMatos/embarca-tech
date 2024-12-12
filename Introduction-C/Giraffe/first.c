#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main()
{

    FILE * fpointer = fopen("employess.txt", "w");
    fprintf(fpointer, "Jim, Salesman,\nPam, Receptionist\nOscar, Accounting");

    fclose(fpointer);
    return 0;

}


int forLoop()
{
    int secretNumber = 5;
    int guess;

    for(int i=1; i <=3; i++){
        printf("Enter a number: ");
        scanf("%d", &guess);
        if(guess == secretNumber){
            printf("You win!");
            break;
        }
        if(i == 3){
            printf("You lose!");
        }
    }

    return 0;
}

int doWhile()
{

    int index = 6;
    do {
        printf("%d\n", index);
        index++;
    }while(index <= 5);


    return 0;
}

struct Student
{
    char name[50];
    char major[50];
    int age;
    double gpa;
};

int estruturandoUmStruct()
{

    struct Student student1, student2;

    student1.age = 25;
    student1.gpa = 3.2;
    strcpy(student1.name, "Grabiel Matos");
    strcpy(student1.major, "Homeless");

    student2.age = 25;
    student2.gpa = 3.2;
    strcpy(student2.name, "AAAA MaDDDtos");
    strcpy(student2.major, "Homeless");

    printf("%s", student1.name);

    

    return 0;
}

int switchUse()
{
    char grade = 'G';

    switch (grade)
    {
    case 'A':
        printf("You did great! ");
        break;
    case 'B':
        printf("You did alright! ");
        break;
    case 'C':
        printf("You did poorly! ");
        break;
    case 'D':
        printf("You did very bad! ");
        break;
    case 'F':
        printf("You failed! ");
        break;
    default:
        printf("Invalid Grade.");
        break;
    }
    return 0;
}

int simpleCalculator()
{
    double num1, num2;
    char op;

    printf("Enter a first number: ");
    scanf("%lf", &num1);

    printf("Enter a second number: ");
    scanf("%lf", &num2);

    printf("Enter operator: ");
    scanf(" %c", &op);

    if(op == '+'){
        printf("%f", num1 + num2);
    }else if(op == '-'){
        printf("%f", num1 - num2);
    }else if(op == '*'){
        printf("%f", num1 * num2);
    }else if(op == '/'){
        printf("%f", num1 / num2);
    }else{
        printf("Invalid Operator");
    }

    return 0;
}

int max(int num1, int num2, int num3){
    int result;
    if(num1 >= num2 && num1 >= num3){
        result = num1;
    } else if(num2 >= num1 && num2 >= num3){
        result = num2;
    } else{
        result = num3;
    }

    return result;
}

int callFunction3()
{
    printf("%d", max(10, 10, 20));

    return 0;
}

double cube(double num){
    double result = num * num * num;
    return result;
}

int callFunction2()
{
    printf("Answer: %f", cube(6.0));

    return 0;
}

void callFunction()
{

    //sayHi("Grabiel", 25);
    //sayHi("Matos", 25);
    //sayHi("Jon", 99);


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