all: testpipe testpipe-inst testfork testfork-inst stackviz
	

testfork: testfork.c
	gcc -c -g -Wall testfork.c -o testfork
	
testfork-inst: testfork.c inst.o
	gcc -finstrument-functions testfork.c -g -Wall inst.o -o testfork-inst

testpipe: testpipe.c
	gcc -c -g -Wall testpipe.c -o testpipe
	
testpipe-inst: testpipe.c inst.o
	gcc -finstrument-functions testpipe.c -g -Wall inst.o -o testpipe-inst

inst.o: inst.c
	gcc -c -g -Wall inst.c

stackviz: stackviz.c
	 gcc -g -Wall stackviz.c -o stackviz

clean:
	rm *.o all
