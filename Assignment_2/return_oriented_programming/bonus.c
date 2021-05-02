#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
void called(unsigned long a, unsigned long b, unsigned long c){
	printf("%ld %ld %ld\n",a,b,c);
} 

int main(){
	char name[64],*cptr;
        void *ptr;
	printf("buffer address: %p\n", name);  //print address of buffer
        puts("Enter text for name:");
        gets(name);
        printf("content of buffer: %s\n", name);
        printf("execve of execve: %p\n", execve);
        
        memset(name,0,64);
        strcpy(name,"hello world\n"); 
        
        cptr = name+80+8;
        ptr = (unsigned long *)cptr;
     
	
        
        *((int*)(ptr+5*(sizeof(void*)))) = (int) 1; //first arg
	*((unsigned long*)(ptr+5*(sizeof(void*))+sizeof(int))) = (unsigned long*) name;        //second //arg
	*((unsigned long*)(ptr+6*(sizeof(void*))+sizeof(int)))=(unsigned long)12;	//third arg
	*((unsigned long *)(ptr+3*(sizeof(void*)))) = (unsigned long *)write;
	//OR if randomization is disabled
	// *(ptr+3) = (unsigned long *)0xf7e4a2b0;
	

        return 0;

}
