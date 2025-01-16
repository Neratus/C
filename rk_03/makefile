FILES := $(wildcard *.c)
OBJ_FILES := $(FILES:.c=.o)

run: app.exe
	./app.exe in.txt out.txt

build: app.exe

app.exe : $(OBJ_FILES)
	gcc $(OBJ_FILES) -o ./$@ 

%.o : %.c
	gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -Wvla -Wfloat-conversion -Wfloat-equal -c $<

clean:
	rm -f *.o
