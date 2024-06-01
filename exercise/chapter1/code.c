#include <stdio.h>

void goodbye(void){
    printf("See You agian!!!\n");
}

void printname(char* name[]){
    printf("Hey %s I am calling form PrintName funciton\n",name[1]);
    goodbye();
}


int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage %s {Name}\n",*argv);
        return -1;
    }
    printname(argv);
    return  0;
}
