#include "Castle.h"
#include "ChessBoard.h"
#include <iostream> 
using namespace std ;

Castle::Castle(ChessBoard* chessboard, int colour,char piece_id):
                            BasePiece(chessboard,colour,piece_id){}  
bool Castle::move (int old_rank,int old_file,int new_rank,int new_file,
                                                    bool line_of_sight)
{
    
    bool record = false ;
    if(line_of_sight == true)
    {
        record = true ;
    }
    
    //Can only either move horizontal or vertical  
    if((old_rank != new_rank && old_file != new_file) || 
                    (old_file != new_file && old_rank != new_rank))
    {
        return false ;
    }
    //check line of sight vertically or horizontally
    if(!straight_check(old_rank,old_file,new_rank,new_file,record))
    {
        return false ;
    }
    
    return true ;


}
