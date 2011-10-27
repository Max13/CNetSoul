# Project: CNetSoul
# Makefile created by Dev-C++ 4.9.9.2
# Modified by Adnan RIHAN (Max13)

CC   = cc
OBJ  = main.o send.o recv.o socks.o func.o
LINKOBJ  = main.o send.o recv.o socks.o func.o
LIBS =  -lcurses -lssl -lcrypto -lpthread
BIN  = CNetSoul.bin
CXXFLAGS = -fexpensive-optimizations -O3
CFLAGS = -D_REENTRANT $(CXXFLAG)
RM = rm -f

all: $(BIN)

clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

send.o: send.c
	$(CC) -c send.c -o send.o $(CFLAGS)

recv.o: recv.c
	$(CC) -c recv.c -o recv.o $(CFLAGS)

socks.o: socks.c
	$(CC) -c socks.c -o socks.o $(CFLAGS)

func.o: func.c
	$(CC) -c func.c -o func.o $(CFLAGS)