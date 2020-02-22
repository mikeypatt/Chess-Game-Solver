EXE = chess
OBJ = ChessMain.o ChessBoard.o BasePiece.o\
	Pawn.o Castle.o Bishop.o Knight.o Queen.o King.o
CXX = g++
CXXFLAGS = -Wall -g -O3
	
$(EXE): $(OBJ)
	$(CXX) $^ -o $@
	
%.o: %.cpp MakeFile
	$(CXX) $(CXXFLAGS) $<

ChessMain.o: ChessMain.cpp ChessBoard.h
ChessBoard.o: ChessBoard.cpp ChessBoard.h
BasePiece.o: BasePiece.cpp BasePiece.h
Pawn.o: Pawn.cpp Pawn.h BasePiece.h
Castle.o: Castle.cpp Castle.h BasePiece.h
Bishop.o: Bishop.cpp Bishop.h BasePiece.h
Knight.o: Knight.cpp Knight.h BasePiece.h
Queen.o: Queen.cpp Queen.h BasePiece.h
King.o: King.cpp King.h BasePiece.h

clean:
	rm -f $(OBJ) chess
.PHONY: clean

