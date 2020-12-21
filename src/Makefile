CC=gcc
CFLAGS= -D_REENTRANT
TARGET=main.out
OBJS=th_data.o thd_led.o dust_data.o thread.o web.o main.o
LDFLAGS= -pthread -lpthread

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJS) -li2c

th_data.o: th_data.c
	$(CC) -c th_data.c

thd_led.o: thd_led.c
	$(CC) -c thd_led.c

dust_data.o: dust_data.c
	$(CC) -c dust_data.c

thread.o: thread.c
	$(CC) -c $(CFLAGS) thread.c

web.o: web.c
	$(CC) -c web.c

main.o: main.c
	$(CC) -c main.c

clean:
	rm -f *.o
	rm -f $(TARGET)
