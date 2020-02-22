/*Header file for inhertied Bishop piece
 * See BasePiece.h for function definitons */

#ifndef BISHOP_H
#define BISHOP_H

#include "BasePiece.h"

class Bishop : public BasePiece {
    

public:
    
    Bishop(ChessBoard* chessboard, int colour,char piece_id) ; 
    bool move (int old_rank,int old_file,int new_rank,int new_file,
                                bool line_of_sight = false) override ;
        
};

#endif
