all:
	g++ difference.cpp -o diff
	./diff

clean:
	rm -f diff
