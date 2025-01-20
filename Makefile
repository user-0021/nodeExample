#build executable file
build:example.node

#make objs
obj:
	@mkdir obj

obj/main.o: src/main.c
	gcc -o obj/main.o src/main.c -I include -I library/nodeSystem -c

obj/nodeSystem.o: library/nodeSystem/nodeSystem.c
	gcc -o obj/nodeSystem.o library/nodeSystem/nodeSystem.c -I include -I library/nodeSystem -c

example.node: obj obj/main.o obj/nodeSystem.o
	gcc -o example.node obj/main.o obj/nodeSystem.o

all: clean example.node

clean:
	$(RM) example.node obj/main.o obj/nodeSystem.o