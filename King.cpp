#include "King.h"
#include <iostream>
#include "ChessBoard.h"

King::King(ChessBoard* chessboard, int colour,char piece_id):
                        BasePiece(chessboard,colour,piece_id) {} 
bool King::move(int old_rank,int old_file,int new_rank,int new_file,
                                                bool line_of_sight)
{
    
    //Castling implimentation
    if((old_rank == new_rank) && abs(old_file - new_file) == 2 
                                        && number_of_moves ==0)
    {
        int dx,castle_file ;

        //if the king is not already in check
        if(!chessboard->check_sweep(true))
        {
            if(old_file < new_file)
            {
                castle_file = Maximum_Files ;
                dx = -1 ;
            }else{
                castle_file = 0 ;
                dx = +1 ;
            }
            
            //if the castle hasnt moved yet in the game
            if(chessboard->board[old_rank][castle_file]->get_nr_moves() == 0)
            {
                //checks if there is nothing between the king and the castle
                if(straight_check(old_rank,old_file,new_rank,castle_file))
                {
                    int current_file = old_file ;
                    while(current_file != new_file)
                    {
                        //checks every increment for king being in check
                        chessboard->king_positions[colour][1] = current_file;
                        if(chessboard->check_sweep(true))
                        {
                            return false;
                        }
                        if(dx > 0)
                        {
                            current_file--;
                        }else{
                            current_file++;
                        }
                    }
                        
                    //switch the king to the required block
                    chessboard->board[old_rank][new_file]=
                                chessboard->board[old_rank][old_file];
                    //switch the castle to the required block
                    chessboard->board[old_rank][new_file+dx]=
                                chessboard->board[old_rank][castle_file];
                    //update the kings position
                    chessboard->king_positions[colour][0] = new_rank;
                    chessboard->king_positions[colour][1] = new_file;
                    //if final position does not put the king in check
                    if(!chessboard->check_sweep(true))
                    {
                        //update castle and kings old position to null
                        chessboard->board[old_rank][old_file] = NULL;
                        chessboard->board[old_rank][castle_file] = NULL;
                        //Increment the kings number of moves
                        chessboard->board[old_rank][new_file]->
                        increment_nr_moves();
                        //Increment the castle number of moves
                        chessboard->board[old_rank][new_file+dx]->
                        increment_nr_moves();
                        //return that caslting move is possible
                        chessboard->caslting_move = true ;
                        return true;
                    }
                    //Return castle and king back to original position
                    chessboard->board[old_rank][new_file] = NULL;
                    chessboard->board[old_rank][new_file+dx] = NULL;
                    chessboard->king_positions[colour][0] = old_rank;
                    chessboard->king_positions[colour][1] = old_file;
                }
            }
        }
        //return that caslting move is not possible
        return false ;
    }
    
    //Can only move once space either way (straight or diagnonally
    if(abs(old_rank - new_rank) > 1 || abs(old_file - new_file) > 1)
    {
        return false ;
    }
    
    if(line_of_sight == false)
    {
        chessboard->king_positions[colour][0] = new_rank ;
        chessboard->king_positions[colour][1] = new_file ;
    }
        
    return true ;
} 



    
