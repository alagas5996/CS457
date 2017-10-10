GEN_SRC := chord_constants.cpp chord_types.cpp ramDisc.cpp FileStore.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /home/yaoliu/src_code/local/include
LIB_DIR := /home/yaoliu/src_code/local/lib/

INC := -I$(THRIFT_DIR) -Isrc/ -I$(THRIFT_DIR)/thrift

.PHONY: all clean

all: server client

%.o: gen-cpp/%.cpp
	$(CXX)  -std=c++11 -lstdc++ -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

%.o: src/%.cpp
	$(CXX)  -std=c++11 -lstdc++ -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

server: FileStore_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -std=c++11 -lstdc++ -L$(LIB_DIR) -lthrift 

client: FileStore_client.o $(GEN_OBJ)
	$(CXX) $^ -o $@  -std=c++11 -lstdc++ -L$(LIB_DIR) -lthrift 

clean:
	$(RM) *.o server client
