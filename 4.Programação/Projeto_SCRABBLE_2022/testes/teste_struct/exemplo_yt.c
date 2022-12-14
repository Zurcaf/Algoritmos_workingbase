#include <stdio.h>

int main ()
{
    struct address
    {
        int hno; //house number
        int pincode;
    };

    struct person
    {
        char name[30];
        int age;
        struct address addr; // struct dentro de struct
    };

    // struct person2
    // {
    //     char name[30];
    //     int age;
    //     struct address *addr; // pointer addr aponta para uma sruct 
    // };

    // struct person anil = {}; // pode se colocar 0 dentro dos braquetes ou não inicializar
    
    // anil.name = "kjwbw";
    // anil.age = 34;
    // anil.addr.hno = 100; //acesso de uma estruturra de uma estrutura
    // anil.addr.pincode = 572987; // acesso ao pin code
    
    // struct person anil = { "Anil", 24, {27, 75129}}; // atenção a ordem pq interessa!!!
    struct person anil = { age: 24, addr: {pincode: 75129, hno: 27}, name: "Anil"};

    // struct person2 anil2 = {};
    // anil2.addr->hno = 100;

    printf("%s %d %d %d\n", anil.name, anil.age, anil.addr.hno, anil.addr.pincode);

}