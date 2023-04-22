#CC = clang
CFLAGS = -Ipingpong_lib
#CFLAGS = -DDEBUG -g3 -O0 -Ipingpong_lib

BIN_DIR = bin
DATA_DIR = data

LDFLAGS = -L$(BIN_DIR) -lpingpong -lrt
PINGPONG_LIB=$(BIN_DIR)/libpingpong.a
PONG = $(BIN_DIR)/pong_server
UDP_PING = $(BIN_DIR)/udp_ping
TCP_PING = $(BIN_DIR)/tcp_ping
PONG_OBJS = $(BIN_DIR)/pong_server.o
UDP_PING_OBJS = $(BIN_DIR)/udp_ping.o
TCP_PING_OBJS = $(BIN_DIR)/tcp_ping.o

EXECS = $(PONG) $(UDP_PING) $(TCP_PING)

all: $(EXECS)

.PHONY: clean tgz tgz-full

$(EXECS): | $(DATA_DIR)

# Common library
$(PINGPONG_LIB): $(BIN_DIR)/fail.o $(BIN_DIR)/readwrite.o $(BIN_DIR)/statistics.o | $(BIN_DIR)
	ar rcs $@ $(BIN_DIR)/*.o
$(BIN_DIR)/fail.o: pingpong_lib/pingpong.h pingpong_lib/fail.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ pingpong_lib/fail.c
$(BIN_DIR)/readwrite.o: pingpong_lib/pingpong.h pingpong_lib/readwrite.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ pingpong_lib/readwrite.c
$(BIN_DIR)/statistics.o: pingpong_lib/pingpong.h pingpong_lib/statistics.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ pingpong_lib/statistics.c

# Pong server
$(PONG): $(PONG_OBJS) $(PINGPONG_LIB) | $(BIN_DIR)
	$(CC) -o $@ $(PONG_OBJS) $(LDFLAGS)
$(BIN_DIR)/pong_server.o: pingpong_lib/pingpong.h pong_server/pong_server.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ pong_server/pong_server.c

# UDP Ping client
$(UDP_PING): $(UDP_PING_OBJS) $(PINGPONG_LIB) | $(BIN_DIR)
	$(CC) -o $@ $(UDP_PING_OBJS) $(LDFLAGS)
$(BIN_DIR)/udp_ping.o: pingpong_lib/pingpong.h udp_ping/udp_ping.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ udp_ping/udp_ping.c

# TCP Ping client
$(TCP_PING): $(TCP_PING_OBJS) $(PINGPONG_LIB) | $(BIN_DIR)
	$(CC) -o $@ $(TCP_PING_OBJS) $(LDFLAGS)
$(BIN_DIR)/tcp_ping.o: pingpong_lib/pingpong.h tcp_ping/tcp_ping.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ tcp_ping/tcp_ping.c

# Directories
$(BIN_DIR):
	mkdir $(BIN_DIR)
$(DATA_DIR):
	mkdir $(DATA_DIR)

# Utilities
clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_DIR)/lib* $(BIN_DIR)/pong* $(BIN_DIR)/tcp* $(BIN_DIR)/udp*
tgz: clean
	rm -rf $(DATA_DIR)
	cd ..; tar cvzf pingpong.tgz --exclude='pingpong/.idea' pingpong
tgz-full: clean
	rm -rf $(DATA_DIR)
	cd ..; tar cvzf pingpong-full.tgz --exclude='pingpong-full/.idea' pingpong-full

