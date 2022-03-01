link_options=-lsfml-graphics -lsfml-window -lsfml-system

target_name=../bin/FreakOut

all: $(target_name)

$(target_name): main.o
	g++ -o $(target_name) $^ $(link_options)
	mv *.o ../bin/

%.o: %.c
	gcc -c -o $@ $< 