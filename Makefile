CC = gcc
CCFLAGS = -std=c99 -g -Wall -Wextra
EXEC = convert.c
OBJS = convert

${EXEC}: ${OBJS}
	${CC} ${CCFLAGS} ${EXEC} -o ${OBJS}

.c.o:
	${CC} ${CCFLAGS} -c $<

run: ${EXEC}
	./${EXEC}

clean:
	rm -f ${EXEC} ${OBJS}
