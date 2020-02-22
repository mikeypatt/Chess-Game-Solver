#include "Bishop.h"
#include <iostream>
using namespace std ;

Bishop::Bishop(ChessBoard* chessboard, int colour,char piece_id):
                            BasePiece(chessboard,colour,piece_id){} 
bool Bishop::move (int old_rank,int old_file,int new_rank,int new_file,
                                                    bool line_of_sight)
{
    bool record = false ;
    
    //check if the move is diagonal 
    if(abs(new_rank - old_rank) != abs(new_file - old_file))
    {
        return false ;
    }
    //May not be nessaasry 
    if(old_rank == new_rank || old_file == new_file)
    {
        return false ;
    }
    
    if(line_of_sight == true)
    {
        record = true ;
    }
    //check diagonal line of sight
    if(!diagonal_check(old_rank,old_file,new_rank,new_file,record))
    {
        return false ;
    }
    return true ;
}
