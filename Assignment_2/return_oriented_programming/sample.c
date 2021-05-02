#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
void called(){
	printf("hello\n");
} 

int main(){
	called();
        char name[64],*cptr;
        unsigned long *ptr;
	printf("buffer address: %p\n", name);  //print address of buffer
	printf("func address: %p\n",called);
	printf("execve address: %p\n",execve);  
	printf("%d\n",sizeof(unsigned long));      
	puts("Enter text for name:");
        gets(name);
        printf("content of buffer: %s\n", name);
        
        memset(name,0,64);
        strcpy(name,"/bin/sh"); 
        
        cptr = name+64+8;
        ptr = (unsigned long *)cptr;
        *ptr = 0x0000ffffd098;
        *(ptr+1) = (unsigned long *)name;
        *(ptr+2) = 0x00007ffff7b79d76;
        *(ptr+3) = (unsigned long *)0;
        *(ptr+4) = 0x00007ffff7a15b8e;
        *(ptr+5) = (unsigned long *)0;
        *(ptr+6) = 0x00007ffff7ad5ec0;
       
  
        return 0;

}
