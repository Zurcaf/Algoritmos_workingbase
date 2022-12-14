#include <stdio.h>

int main ()
{
    struct student
    {
        char name[30];
        int age;
    };

    struct student anil = { age: 24, name: "Anil"};

    struct student *ptr; //stuct student é o tipo de variavel é como por int

    ptr = &anil; //pointer do tipo struct student aponta para address da struct do anil
    anil.age = 200;
    // ptr.age = 2000 é errado

    (*ptr).age = 2000; // o ponto tem perioridade parentessis são essenciais a idade muda de 200 para 2000

    ptr->age = 3000; // struct pointer operator nunca pode ter espaço entre traço e maior tipo (- >) está errado
    // int x = 10;
    // int *p;
    // p = &x;
    // *p = 20;

    printf("name: %s age: %d\n", anil.name, anil.age);

}