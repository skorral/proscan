CC=gcc
CFLAGS=

EXEC=client

all: $(EXEC)

$(EXEC): net.o client.o 
	$(CC) -o $(EXEC) $^ $(CFLAGS)


net.o: ../common/net.c ../common/net.h ../common/const.h
	$(CC) -c $^ $(CFLAGS)

client.o: client.c ../common/net.h ../common/const.h
	$(CC) -c $^ $(CFLAGS)


clean:
	rm -rf *.o *.gch

mrproper: clean
	rm -rf $(EXEC)


