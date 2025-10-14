output: main.o network.o user.o
	g++ main.o network.o user.o -o output
main.o: main.cpp network.h user.h
	g++ -c main.cpp -o main.o
network.o: network.cpp network.h user.h
	g++ -c network.cpp -o network.o
user.o: user.cpp user.h
	g++ -c user.cpp -o user.o
clean:
	rm -f *.o output