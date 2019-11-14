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
  char pw[] = {0x75,0xc,0x6f,0x1,0x6f,0x1e,0x67,0x4a,0x25,0x54,0x20,0x43,0x35,0x44,0x30,0x5b,0x2c,0x43,0x6e,0x2,0x70,0x45,0x21,0x48,0x33,0xc,0x00};
  char cpw[27];
  char inp[0x20];
  int sum = 0;

  printf("input password > ");
  read(0,inp,0x20-2);
  
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
  
  inp[26+3] = '\x00';
  if(strtoul(inp+26,NULL,16)!=sum)
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
