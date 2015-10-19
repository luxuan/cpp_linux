all: server client

server: server.cc request.pb.h request.pb.cc
	g++ -g -o $@ $^  -lpthread `pkg-config --cflags --libs protobuf`

client: client.cc request.pb.h request.pb.cc
	g++ -g -o $@ $^  -lpthread `pkg-config --cflags --libs protobuf`

# Clean
.PHONY: clean 
clean:
	rm -f server client
