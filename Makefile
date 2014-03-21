gtuxnes: gtuxnes.o general.o gtuxnes.h sound.o files.o video.o input.o panels.o debug.o config.o
	gcc -o gtuxnes gtuxnes.o general.o sound.o files.o video.o input.o\
		panels.o debug.o config.o `gtk-config --cflags --libs`

%.o: %.c gtuxnes.h
	gcc `gtk-config --cflags` -c $*.c -o $@

clean:
	rm -f *.o 

distclean: clean
	rm gtuxnes

