#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include "colors.h"
#include "utils.h"


#define FILEPATH "/dev/fb0"
#define NUM_WORDS 64
#define FILESIZE (NUM_WORDS * sizeof(uint16_t))

void t_led(int temperature)
{
    int i;
    int fbfd;
	uint16_t color;
    uint16_t *map;
    uint16_t *p;
    struct fb_fix_screeninfo fix_info;

	/*temp data*/
	int t_out = temperature+16;

    /* open the led frame buffer device */
    fbfd = open(FILEPATH, O_RDWR);
    if (fbfd == -1) {
        perror("Error (call to 'open')");
        exit(EXIT_FAILURE);
    }
    
    /* read fixed screen info for the open device */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
        perror("Error (call to 'ioctl')");
        close(fbfd);
        exit(EXIT_FAILURE);
    }

    /*now check the correct device has been found*/
    if (strcmp(fix_info.id, "RPi-Sense FB") != 0) {
        printf("%s\n", "Error: RPi-Sense FB not found");
        close(fbfd);
        exit(EXIT_FAILURE);
    }

    /*map the led frame buffer device into memory*/
    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (map == MAP_FAILED) {
        close(fbfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    /*set a pointer to the start of the memory area */
    p = map;

    /*clear the led matrix */
    memset(map, 0, FILESIZE);
	
	if (t_out <= 10) {
		color = RGB565_BLUE;
	} else if (t_out > 10 && t_out <=28) {
		color = RGB565_GREEN;
	} else if (t_out > 28) {
		color = RGB565_RED;
	} 
    /*light up*/
    for (i = 0; i < t_out; i++) {
       	*(p + i) = color;
	    delay(25);
    }

    delay(2000);

    /* clear the led matix */
    memset(map, 0, FILESIZE);

    /* un-map and close */
    if(munmap(map, FILESIZE) == -1) {
	    perror("Error un-mmapping the file");
    }
    close(fbfd);
}

void h_led(int humidity)
{
    int i;
    int fbfd;
    uint16_t *map;
    uint16_t *p;
    struct fb_fix_screeninfo fix_info;

	/*temp data*/
	int h_out = (int)(humidity+0.64);

    /* open the led frame buffer device */
    fbfd = open(FILEPATH, O_RDWR);
    if (fbfd == -1) {
        perror("Error (call to 'open')");
        exit(EXIT_FAILURE);
    }
    
    /* read fixed screen info for the open device */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
        perror("Error (call to 'ioctl')");
        close(fbfd);
        exit(EXIT_FAILURE);
    }

    /*now check the correct device has been found*/
    if (strcmp(fix_info.id, "RPi-Sense FB") != 0) {
        printf("%s\n", "Error: RPi-Sense FB not found");
        close(fbfd);
        exit(EXIT_FAILURE);
    }

    /*map the led frame buffer device into memory*/
    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (map == MAP_FAILED) {
        close(fbfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    /*set a pointer to the start of the memory area */
    p = map;

    /*clear the led matrix */
    memset(map, 0, FILESIZE);
	
    /*light up*/
    for (i = 0; i < h_out; i++) {
       	*(p + i) = RGB565_GREY;
	    delay(25);
    }

    delay(2000);

    /* clear the led matix */
    memset(map, 0, FILESIZE);

    /* un-map and close */
    if(munmap(map, FILESIZE) == -1) {
	    perror("Error un-mmapping the file");
    }
    close(fbfd);
}

void d_led(int dust)
{
    int i;
    int fbfd;
	uint16_t color;
    uint16_t *map;
    uint16_t *p;
    struct fb_fix_screeninfo fix_info;

	/*temp data*/
	int d_out = dust;

    /* open the led frame buffer device */
    fbfd = open(FILEPATH, O_RDWR);
    if (fbfd == -1) {
        perror("Error (call to 'open')");
        exit(EXIT_FAILURE);
    }
    
    /* read fixed screen info for the open device */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
        perror("Error (call to 'ioctl')");
        close(fbfd);
        exit(EXIT_FAILURE);
    }

    /*now check the correct device has been found*/
    if (strcmp(fix_info.id, "RPi-Sense FB") != 0) {
        printf("%s\n", "Error: RPi-Sense FB not found");
        close(fbfd);
        exit(EXIT_FAILURE);
    }

    /*map the led frame buffer device into memory*/
    map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (map == MAP_FAILED) {
        close(fbfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    /*set a pointer to the start of the memory area */
    p = map;

    /*clear the led matrix */
    memset(map, 0, FILESIZE);
    
	/*light up*/
	int ledArr[10];
	if (d_out <= 30) {
		int Arr[10] = {11, 12, 13, 14, 18, 23, 35, 38, 43, 46};
		memcpy(ledArr, Arr, sizeof(Arr));
		color = RGB565_BLUE;
	} else if (d_out > 30 && d_out <=80) {
		int Arr[10] = {10, 11, 12, 13, 14, 15, 35, 38, 43, 46};
		memcpy(ledArr, Arr, sizeof(Arr));
		color = RGB565_GREEN;
	} else if (d_out > 80) {
		int Arr[10] = {10, 15, 19, 20, 21, 22, 35, 38, 43, 46};
		memcpy(ledArr, Arr, sizeof(Arr));
		color = RGB565_RED;
	} 

    for (i = 0; i < sizeof(ledArr)/sizeof(int); i++) {
       	*(p + ledArr[i] - 1) = color;
    }
    delay(2000);

    /* clear the led matix */
    memset(map, 0, FILESIZE);

    /* un-map and close */
    if(munmap(map, FILESIZE) == -1) {
	    perror("Error un-mmapping the file");
    }
    close(fbfd);
}

