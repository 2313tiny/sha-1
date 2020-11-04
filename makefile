SOURCES := Sha.cpp Garray.cpp  main.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))


all:comp run
comp:$(OBJECTS)
	@clear 
	@g++ $(OBJECTS) -o smd -std=c++11

Garray.o:
	@g++ -c Garray.cpp -o Garray.o -std=c++11

Sha.o:
	@g++ -c Sha.cpp -o Sha.o -std=c++11

main.o:
	@g++ -c main.cpp -o main.o -std=c++11

Sha.dep:
	@g++ -c -MM Sha.cpp -MT "Sha.dep Sha.o" \
		 -o Sha.dep  -std=c++11

Garray.dep:
	@g++ -c -MM Garray.cpp -MT "Garray.dep Sha.o" \
		 -o Sha.dep -std=c++11

main.dep:
	@g++ -c -MM main.cpp -MT "main.dep main.o" -o main.dep -std=c++11

-include Sha.dep main.dep Garray.dep 
 
run:
	@./smd
	@ctags -R .
clean:
	rm smd *.o *.dep tags
