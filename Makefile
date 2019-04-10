main:main.cpp
	g++ main.cpp -o main -lpcap
clean:
	rm -rf *.o main
