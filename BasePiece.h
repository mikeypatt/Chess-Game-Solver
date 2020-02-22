/*Header file for the Base chess piece class. The class defined below
 * is a abstract class */

#ifndef BASE_PIECE_H
#define BASE_PIECE_H
#include <iostream>
using namespace std ;

enum colour {white , black} ;

class ChessBoard ;

class BasePiece {
protected:
    
    ChessBoard* chessboard ;
    int number_of_moves = 0 ;
    int colour  ;
    char piece_id = 'B' ; // B-Basepeice
     
public:
    BasePiece(ChessBoard* chessboard, int colour,char piece_id) ;
    
    //Returns the team colour (White/Black)
    int get_colour() ;
    //Returns the piece id (P,C,K,Q etc)
    char get_id() ;
    //Inrements the number of moves upon completion of move
    void increment_nr_moves () ;
    //Returns the number of moves the piece has completed
    int get_nr_moves();
    
    /* Boolean function returns to the ChessBoard.cpp whether the specific
     * piece can move to the designated square.
     * This function is overidden by the specific piece class depending on the
     * functionality
     * Inputs:
     *          old rank (integer) - current row position of piece
     *          old old_file (integer) - current collumn postion of piece
     *          new rank (integer) - destination row position of piece
     *          new file (integer) - desiination collumn position of piece
     *          line of sight (boolean) - boolean swithc to record the line of sight
     *                                    from the piece to king if in check.*/
    virtual bool move (int old_rank,int old_file,int new_rank,int new_file,
                        bool line_of_sight = false) = 0 ;
                        
    /* Boolean function checks whether the diagnonal line of sight from the orgin
     * block to the destination block is clear.
     * Inputs:
     *          old rank (integer) - current row position of piece
     *          old old_file (integer) - current collumn postion of piece
     *          new rank (integer) - destination row position of piece
     *          new file (integer) - desiination collumn position of piece
     *          line of sight (boolean) - boolean swithc to record the line of sight
     *                                    from the piece to king if in check. */
    bool diagonal_check(int old_rank,int old_file,int new_rank,int new_file,
                        bool record_line_of_sight = false);
    
    /* Boolean function checks whether the vertical/horizontal line of sight from
     * the orgin block to the destination block is clear.
     * Inputs:
     *          old rank (integer) - current row position of piece
     *          old old_file (integer) - current collumn postion of piece
     *          new rank (integer) - destination row position of piece
     *          new file (integer) - desiination collumn position of piece
     *          line of sight (boolean) - boolean swithc to record the line of sight
     *                                    from the piece to king if in check.*/
    bool straight_check(int old_rank,int old_file,int new_rank,int new_file,
                        bool record_line_of_sight = false) ;
    
    virtual ~BasePiece() ;
};

#endif
