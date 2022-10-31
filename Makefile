all:
	gcc server.c -o Server
	gcc client.c -o Client
clean:
	rm -rf Server
	rm -rf Client