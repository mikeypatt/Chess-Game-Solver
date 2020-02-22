/*Header file for inhertied King piece
 * See BasePiece.h for function definitons */

#ifndef KING_H
#define KING_H

#include "BasePiece.h"

class King : public BasePiece {
    

public:
    
    King(ChessBoard* chessboard, int colour,char piece_id) ; 
    bool move (int old_rank,int old_file,int new_rank,int new_file,
                            bool line_of_sight = false) override ;
        
};
#endif
