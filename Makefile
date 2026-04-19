CC = gcc
CFLAGS = -Wall -O2

TARGET = sum-nbo

SRC = sum-nbo.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
