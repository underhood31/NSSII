#include <stdio.h>
#include <stdlib.h>

void g()
{
    printf("now inside g()!\n");
}


void f()
{   
    printf("now inside f()!\n");
    // can only modify this section
    // cant call g(), maybe use g (pointer to function)
}

int main (int argc, char *argv[])
{
    f();
    return 0;
}
