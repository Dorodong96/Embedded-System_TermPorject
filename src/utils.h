#ifndef UTILS_DOT_H
#define UTILS_DOT_H

extern int dust_data;
//extern char weather_data[20];
void delay(int t);
int temp_out(void);
int humid_out(void);
void t_led(int temperature);
void h_led(int humidity);
void d_led(int dust);
void use_thread();
int webcrawling();
int webSelecting();
//int wecrawling2();
//char *webSelecting2();
void upload_txt(int temp, int humid, int dust);
void upload_html(int temp, int humid, int dust);
//void upload_html(char *weather, int temp, int humid, int dust);

#endif 
