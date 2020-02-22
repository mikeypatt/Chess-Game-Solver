/*Header file for inhertied Caslte(Rook) piece
 * See BasePiece.h for function definitons */

#ifndef CASTLE_H
#define CASTLE_H
#include "BasePiece.h"

class Castle : public BasePiece {
    
public:
    
    Castle(ChessBoard* chessboard, int colour,char piece_id) ; 
    bool move (int old_rank,int old_file,int new_rank,int new_file,
                                bool line_of_sight = false) override ;
        
};

#endif
