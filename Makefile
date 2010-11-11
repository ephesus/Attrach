OPTS=-Wall
SOURCE_FILES=attrach.c

all:
	gcc ${OPTS} -o attrach ${SOURCE_FILES}

clean:
	rm attrach
	rm -f *~
	rm -f *.o

