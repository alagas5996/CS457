EXEC = -g -std=c++11 -O2 -pthread -Wall -Wextra -Wundef
FILE = -g -std=c++11 -O2 -pthread -Wall -Wextra -Wundef -c

all: server

server: main.o
	g++ $(EXEC) main.o -o server

main.o: main.cpp
	g++ $(FILE) main.cpp -o main.o

client: client.o
	g++ $(EXEC) client.o -o client

client.o: client.cpp
	g++ $(FILE) client.cpp -o client.o

clean:
	rm server *.o
