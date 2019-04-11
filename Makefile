main:main.o parse_config.o
	g++ -o main main.o parse_config.o -lxerces-c -lpcap
main.o:main.cpp header.h log.h
	g++ -c main.cpp    
parse_config.o:parse_config.h parse_config.cpp log.h
	g++ -c parse_config.cpp 
clean:
	rm -rf *.o main
