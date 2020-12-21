#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "utils.h"

int webcrawling2() {
	char Site[100] = {"www.kma.go.kr/eng/weather/forecast/current_korea.jsp"};
	char Command[100] = {"wget -O index2.html "};
	
	//__fpurge(stdin);
	strcat(Command, Site);
	system(Command);
	//system("clear");
	return 1;
}

char *webSelecting2() {

	char weather[20];
	char weather[20];
	FILE *fp2 = fopen("index2.html", "r");
	if (fp2 == NULL) {
		printf("index2.html is not EXIST!\n");
		return 0;
	}
	else {
		char *buff2 = malloc(sizeof(char) * 1024);
		while (fgets(buff2, 100, fp2)) {
			if (strstr(buff2, "<td>Daegu</td>") != 0) {
				printf("found!\n");
				for (int i = 0; i < 100 - 50; i++) {
					printf("%c\n", buff2[i]);
					buff2[i] = buff2[i+50];
					printf("%c ", buff2[i]);
					if (buff2[i] == '<') {
						buff2[i] = '\0';
						break;
					}
				}
				printf("%s", buff2);
				//strcpy(weather, buff2);
				break;
			} 
		}
		printf("%s\n", weather);
		free(buff2);
		return weather;
	}
}
