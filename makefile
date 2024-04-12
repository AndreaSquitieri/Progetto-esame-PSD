##
# Progetto esame PSD, Prima traccia
#
# @file
# @version 0.1


progetto-psd:	main.o evento.o data.o
	gcc main.o evento.o data.o -o progetto-psd

main.o:	main.c evento.h
	gcc -g main.c

data.o:	data.c
	gcc -g data.c

evento.o: evento.c data.h
	gcc -g evento.c

clean:
	rm -f *.c *.o progetto-psd

# end
