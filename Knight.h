/*Header file for inhertied Knight piece
 * See BasePiece.h for function definitons */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "BasePiece.h"

class Knight : public BasePiece {
    
public:
    
    Knight(ChessBoard* chessboard, int colour,char piece_id) ; 
    bool move (int old_rank,int old_file,int new_rank,int new_file,
                                    bool line_of_sight = false) override ;
        
};
#endif
