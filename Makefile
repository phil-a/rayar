OBJ = main.o
INC = -I "./"

rayar: $(OBJ)
	g++ $(OBJ) -o rayar
	rm -f $(OBJ)

main.o:
	g++ -c main.cpp $(INC)

clean:
	rm -f $(OBJ) rayar