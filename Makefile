OPTS=-Wall
SOURCE_FILES=attrach.c
#COMPILER=gcc
COMPILER=clang

all:
	${COMPILER} ${OPTS} -o attrach ${SOURCE_FILES}

clean:
	rm attrach
	rm -f *~
	rm -f *.o

