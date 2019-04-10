main:main.cpp
	g++ main.cpp -o main -lpcap -lxerces-c
clean:
	rm -rf *.o main
