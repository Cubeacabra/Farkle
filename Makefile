a.out: main.o die.o player.o table.o presetDie.o
	g++ main.o die.o player.o table.o presetDie.o

main.o: main.cc die.h
	g++ -c main.cc

die.o: die.cc die.h
	g++ -c die.cc

player.o: player.cc player.h die.h
	g++ -c player.cc

table.o: table.cc table.h player.h die.h
	g++ -c table.cc

presetDie.o: presetDie.cc die.h
	g++ -c presetDie.cc

clean:
	rm -f *.o a.out core

t.out: testing.o die.o player.o table.o presetDie.o
	g++ testing.o die.o player.o table.o presetDie.o

testing.o: testing.cc table.h player.h die.h presetDie.h
	g++ -c testing.cc
