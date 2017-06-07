
all:
	g++ -std=c++11 -o ply2pgsql ply2pgsql.cpp -lpqxx -lpq
install:
	cp ply2pgsql /usr/local/bin/ikg.ply2pgsql
