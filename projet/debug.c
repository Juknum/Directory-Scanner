#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "debug.h"

void debug(char* msg, ...){
// permet d'afficher un message pour débuger si DEBUG est défini dans debug.h
#ifdef DEBUG
	va_list ap;
	va_start(ap,msg);
	int i=0;
	while(msg[i]!='\0'){
		if(msg[i]=='%'){
			switch(msg[i+1]){
			case 100:
				printf("%d",va_arg(ap, int));
			break;
			case 115:
				printf("%s",va_arg(ap, char*));
			break;
			default:
			break;
			}
			i=i+2;
		}else{
			printf("%c",msg[i]);
			i=i+1;
		}
	}
	printf("\n");
#endif
}
