output: social_network.o network.o user.o post.o
	g++ social_network.o network.o user.o post.o -o output
social_network.o: social_network.cpp network.h user.h
	g++ -c social_network.cpp -o social_network.o
network.o: network.cpp network.h user.h
	g++ -c network.cpp -o network.o
user.o: user.cpp user.h
	g++ -c user.cpp -o user.o
post.o: post.cpp post.h
	g++ -c post.cpp -o post.o
clean:
	rm -f *.o output
