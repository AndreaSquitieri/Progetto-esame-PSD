##
# Progetto esame PSD, Prima traccia
#
# @file
# @version 0.1


progetto-psd:	main.o evento.o data.o
	gcc main.o evento.o data.o -o progetto-psd

main.o:	main.c evento.h
	gcc -c main.c

data.o:	data.c
	gcc -c data.c

evento.o: evento.c data.h logging.h
	gcc -c evento.c

logging.o:	logging.c
	gcc -c logging.c

queue_eventi.o:	queue_eventi.c evento.h data.h
	gcc -c queue_eventi.c

clean:
	rm -f *.o progetto-psd

# end
