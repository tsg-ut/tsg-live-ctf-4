/****************************
Makefile
	gcc  ./IfYouWanna.c -o IfYouWanna -no-pie -fno-stack-protector -z execstack


 This is the easiest pwn in the wrold.
 If you wanna flag, then I will.
*****************************/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dlfcn.h>

long long printf_addr = printf;
long long printf_off = 0x64e80;
long long* got_printf = 0x601020;

char auth(void)
{
  char pw[] = {0x75,0xc,0x6f,0x1,0x6f,0x1e,0x67,0x00};
  char cpw[8];
  char inp[0x10];

  printf("input password > ");
  read(0,inp,10);
  for(int ix=0;pw[ix]!='\x00';++ix){
    if(ix==0){
      if(pw[ix]-2!=inp[0]){
        return -1;
      }
    }else
      if((pw[ix]^pw[ix-1])-2!=inp[ix]){
        return -1;
      }
  }
  return 1;
}

void* get_libcbase(void)
{
  return *got_printf-printf_off;
}

int main(void)
{
  setvbuf(stdout,NULL,_IONBF,0);
  setvbuf(stdin,NULL,_IONBF,0);

  if(auth()==-1)
    return 0;

  char flag[0x50] = {"(っ'ヮ' )ﾉｼ🚩\n"};
  char buf[0x50];

  printf("libc_base: %llx\n",get_libcbase());
  get_libcbase();

  printf("Do you want a flag? > ");
  scanf("%s",buf);

  if(buf[0]=='Y' || buf[0]=='y'){
    printf(flag);
    return 0;
  }else{
    printf("BYE\n");
    exit(0);
  }

  return 0;
}
