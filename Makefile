CC = gcc
CCFLAGS = -std=c99 -g -Wall -Wextra
EXEC = convert
OBJS = convert.o

${EXEC}: ${OBJS}
	${CC} ${CCFLAGS} -o ${EXEC} ${OBJS}

.c.o:
	${CC} ${CCFLAGS} -c $<

convert.o: convert.c

run: ${EXEC}
	./${EXEC)

clean:
	rm -f ${EXEC} ${OBJS}
