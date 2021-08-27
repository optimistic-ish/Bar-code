CC = gcc
CFLAGS  = -lm
SRCS = entry.c makeBars.c readBars.c

BarCode: entry.c makeBars.c readBars.c
	$(CC) $(SRCS) $(CFLAGS) -o BarCode
