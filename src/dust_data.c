#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "utils.h"

int webcrawling() {
	char Site[100] = {"www.airkorea.or.kr/web/vicinityStation?item_code=10007\"&\"station_code=422154"};
	char Command[100] = {"wget -O index.html "};
	
	//__fpurge(stdin);
	strcat(Command, Site);
	system(Command);
	system("clear");
	return 1;
}

int webSelecting() {
	int d = 0;
	FILE *fp = fopen("index.html", "r");
	if (fp == NULL) {
		printf("index.html is not EXIST!\n");
		return 0;
	}
	else {
		char *buff = malloc(sizeof(char) * 1024);
		while (fgets(buff, 100, fp)) {
			char *ptr = strstr(buff, "font-size: 30px;\">");
			if (ptr != NULL) {
				d = atoi(ptr+18);
				break;
			}
		}
		free(buff);
		return d;
	}
}
/*
void main(void) {
	int dust;
	if(webcrawling()) 
		dust=webSelecting();
	printf("%d\n", dust);
	system("rm index.html");
}
*/
