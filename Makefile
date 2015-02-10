CC=gcc
CFLAGS= $(mysql_config --cflags) $(mysql_config --libs)
CFLAGS_2= -I/usr/include/mysql -I/usr/include/mysql/.. -fPIC -pipe -fstack-protector-strong --param=ssp-buffer-size=4 -fno-strict-aliasing -DBIG_JOINS=1 -fomit-frame-pointer -fno-delete-null-pointer-checks -g -static-libgcc -fno-omit-frame-pointer -fno-strict-aliasing -L/usr/lib -lmysqlclient -lpthread -lz -lm -lssl -lcrypto -ldl -Wall

#CFLAGS_BDD=/usr/include/mysql/mysql.h

EXEC=master

all: $(EXEC)

$(EXEC): crud.o net.o server.o 
	        $(CC) -o $(EXEC) $^ $(CFLAGS_2)
crud.o: bdd/crud.c
		$(CC) -c $^ $(CFLAGS_2)

net.o: common/net.c common/net.h common/const.h
	        $(CC) -c $^ $(CFLAGS_2)

server.o: server/server.c common/net.h common/const.h bdd/crud.h
	        $(CC) -c $^ $(CFLAGS_2)


clean:
	rm -rf *.o *.gch *.d

mrproper: clean
	rm -rf $(EXEC)
