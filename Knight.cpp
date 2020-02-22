#include <iostream>
#include "Knight.h"
#include "ChessBoard.h"

using namespace std ;


Knight::Knight(ChessBoard* chessboard, int colour,char piece_id):
                            BasePiece(chessboard,colour,piece_id){}
bool Knight::move(int old_rank,int old_file,int new_rank,int new_file,
                                                    bool line_of_sight)
{
    
    //Number of total possible moves broken down  
    int dx[8] =  { 2, 1,-1,-2,-2, -1, 1, 2 };  
    int dy[8] =  { 1, 2, 2, 1,-1, -2, -2, -1 }; 
    int i =0 , x = 0 , y = 0 ;
    
    //Check if each possible move is valid or not 
    while (true)
    {
        //Move is impossible for a knight regardless
        if(i == 8)
        {
            return false ;
        }
        
        //Position of knight after move 
        x = old_file + dx[i]; 
        y = old_rank +  dy[i];
        i++ ;
        
        if(x == new_file && y == new_rank)
        {
            break ;
        }

    }

    //Otherwise the knight may move there "Silo'd"
    return true ;
}

    
  
    
    
    
