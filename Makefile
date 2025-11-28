a.out: main.o die.o player.o table.o
	g++ main.o die.o player.o table.o

main.o: main.cc die.h
	g++ -c main.cc

die.o: die.cc die.h
	g++ -c die.cc

player.o: player.cc player.h die.h
	g++ -c player.cc

table.o: table.cc table.h player.h die.h
	g++ -c table.cc

clean:
	rm -f *.o a.out core
