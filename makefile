CXX = clang

main.o: main.cc inverted_list.h
	$(CXX) -c main.cc

inverted_list.o: inverted_list.cc inverted_list.h
	$(CXX) -c inverted_list.cc

clean:
	rm *.o -f
