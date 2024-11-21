#build executable file
build:out

#make objs
obj/main.o: src/main.c
	gcc -o obj/main.o src/main.c -I include -I library/nodeSystem -c

obj/nodeSystem.o: library/nodeSystem/nodeSystem.c
	gcc -o obj/nodeSystem.o library/nodeSystem/nodeSystem.c -I include -I library/nodeSystem -c

out: obj/main.o obj/nodeSystem.o
	gcc -o out obj/main.o obj/nodeSystem.o

all: clean out

clean:
	$(RM) out obj/main.o obj/nodeSystem.o