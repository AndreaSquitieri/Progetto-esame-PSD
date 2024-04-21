##
# Progetto esame PSD, Prima traccia
#
# @file
# @version 0.1


progetto-psd:	main.o mevent.o date.o logging.o event_queue.o event_bst.o
	gcc main.o mevent.o date.o event_queue.o event_bst.o logging.o -o progetto-psd

main.o:	main.c mevent.h
	gcc -c main.c

date.o:	date.c
	gcc -c date.c

mevent.o: mevent.c date.h logging.h
	gcc -c mevent.c

logging.o:	logging.c
	gcc -c logging.c

event_queue.o:	event_queue.c mevent.h date.h
	gcc -c event_queue.c

event_bst.o:	event_queue.c mevent.h date.h
	gcc -c event_bst.c

clean:
	rm -f *.o progetto-psd

# end
