all: server client

client: DUMBclient.c
	gcc -o DUMBclient DUMBclient.c -lpthread -lm

server: DUMBserver.c
	gcc -o DUMBserver DUMBserver.c -lpthread -lm

clean:
	rm DUMBclient DUMBserver
