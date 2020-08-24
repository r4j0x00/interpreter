CC = g++
CFLAGS = -Wall -pie -fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 -Wl,-z,now -Wl,-z,relro -s
LFLAGS = 
main: main.cc interpreter.cc token.cc
	$(CC) $(CFLAGS) $? $(LDFLAGS) -o bin/$@ $(LFLAGS)
