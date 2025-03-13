COMP = g++
TP = TP4

all: ${TP}

${TP}:prog
	./${TP}

prog: ${TP}.o
	$(COMP) -o ${TP} ${TP}.o

${TP}.o : ${TP}.cpp
	$(COMP) -c ${TP}.cpp

clean:
	rm -f *.o
	rm -f ${TP}