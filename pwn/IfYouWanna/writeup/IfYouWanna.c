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
  char pw[] = {0x6f,0x1e,0x6a,0x9,0x24,0x41,0x30,0x41,0x2c,0x47,0x20,0xd,0x7d,0x1e,0x6e,0x43,0x35,0x3,0x76,0x1c,0x77,0x5a,0x2f,0x56,0x35,0x6,0x35,0x44,0x3d,0x2};
  char cpw[30];
  char inp[0x30];
  int sum = 0;

  printf("input password > ");
  read(0,inp,0x30-2);
  
  for(int ix=0;pw[ix]!='\x00';++ix){
    if(ix==0){
      if(pw[ix]-2!=inp[0]){
        return -1;
      }
      sum += inp[ix];
    }else{
      if((pw[ix]^pw[ix-1])-2!=inp[ix]){
        return -1;
      }
      sum += inp[ix];
    }
  }
  
  inp[30+3] = '\x00';
  if(strtoul(inp+30,NULL,16)!=sum)
    return -1;
  
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

  if(auth()==-1){
    printf("incorrect\n");
    return 0;
  }

  char flag[0x50] = {"(っ'ヮ' )ﾉｼ🚩\n"};
  char buf[0x50];

  printf("Hey, friend.\n");
  printf("libc_base: %llx\n",get_libcbase());

  printf("Do you wanna flag? > ");
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
