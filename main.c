
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "main.h"

char *Primary[4]       = {"MKDISK", "FDISK", "MOUNT", "UNMOUNT"};
char *prmCreateDisk[4] = {"-SIZE->", "-UNIT->", "-PATH->", "-FIT->"};
char inputString[10][50]; 

//COMPARACION POR POSICION    
static int Compare(char * str1, char * str2){
    int i, j;
    for(i = 0; str2[i] != '\0'; ++i);
    
    for(j = 0; j<i; j++){
        if(toupper(str1[j]) != toupper(str2[j]))
            return -1;
    }
    return 0;
}

//FUNCION CREAR DISCO
static void fnCreateDisk(int init, int end){
    
    for(int i = init; i < end; i++){
        for(int j = 0; j < 3; j++){
            if(Compare(inputString[i],prmCreateDisk[j]) == 0){
                switch(j){
                    case 0: //SIZE
                         printf("SIZE!!! %s %i",inputString[i], i);
                    break;
                    case 1: //UNIT
                         printf("UNIT!!! %s %i",inputString[i], i);
                    break;
                    case 2: //PATH
                         printf("PATH!!! %s %i",inputString[i], i);
                    break;
                    case 3: //FIT
                         printf("FIT!!! %s %i",inputString[i], i);
                    break;
                }
            }
                
        }
        
    }
    
}

int main(){
    char str1[100];
    int i,j,ctr;
    
    fgets(str1, sizeof str1, stdin);	
 
    j=0; ctr=0;
    for(i=0;i<=(strlen(str1));i++){
        if(str1[i]==' '||str1[i]=='\0'){
            inputString[ctr][j]='\0';
            ctr++;  
            j=0;    
        }else{
            inputString[ctr][j]=str1[i];
            j++;
        }
    }
    
    for(int j=0;j < 4;j++){
            if(Compare(inputString[0],Primary[j]) == 0){
                switch(j){
                    case 0: //MKDISK
                         fnCreateDisk(1, ctr);   
                    break;
                }
                
            }
    }
}
