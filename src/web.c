#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

void upload_txt(int temp, int humid, int dust)
{
	FILE *fp = fopen("log.txt", "a");
	char Msg[1024];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(Msg, "%4d-%02d-%02d  %02d:%02d:%02d                    %3d           %3d             %3d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, temp, humid, dust);
	fputs(Msg, fp);

	fclose(fp);
	system("sudo cp log.txt /var/www/html/log.txt");
}

void upload_html(int temp, int humid, int dust)
{
	FILE *fp = fopen("log.html", "r+");
	char Msg[1024];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fseek(fp, -17, SEEK_END);
	sprintf(Msg, "\n\t\t\t<tr style=\"font-size:100\%\">\n<th>%4d-%02d-%02d</th>\n<th>%02d:%02d:%02d</th>\n<th>%3d</th>\n<th>%3d</th>\n<th>%3d</th>\n\t\t\t</tr>\n\t</body>\n</html>", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, temp, humid, dust);
	fputs(Msg, fp);
	fclose(fp);
	system("sudo cp log.html /var/www/html/log.html");
}

