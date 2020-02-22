/*Implimentaion file (.cpp) for the Basepiece Class
 * See BasePiece.h for function definiton
 */

#include "BasePiece.h"
#include <iostream>
#include "ChessBoard.h"

BasePiece::BasePiece(ChessBoard* chessboard, int colour ,char piece_id): 
            chessboard(chessboard), colour(colour), piece_id(piece_id) {} 


void BasePiece::increment_nr_moves () { this->number_of_moves++ ;}
int BasePiece::get_nr_moves() { return number_of_moves;}
int BasePiece::get_colour(){return colour ; }
char BasePiece::get_id(){return piece_id ; } ;

bool BasePiece::diagonal_check(int old_rank,int old_file,int new_rank,
                               int new_file,bool record_line_of_sight)
{
    
    int i = 0 ;
    
    if(abs(old_rank - new_rank) != abs(old_file - new_file))
    {
    
        return false ;
    }
    
    //check if there are pieces in the way 
    if(new_rank > old_rank && new_file > old_file)
    {
        for(int j = old_rank+1 ; j < new_rank ; j++)
        {
            i = old_file + (j-old_rank) ;
            if(record_line_of_sight == true)
            {
                chessboard->check_positions[j-(old_rank)][0] = j;
                chessboard->check_positions[j-(old_rank)][1] = i;
                chessboard->line_of_sight_distance++ ;
            }
            if(chessboard->board[j][i] != NULL)
            {
                
                return false ;
            }
        }
    }
    //check if there are pieces in the way
    if(new_rank < old_rank && new_file < old_file)
    {
        for(int j = old_rank-1 ; j > new_rank ; j--)
        {
            i = old_file - (old_rank-j) ;
            if(record_line_of_sight == true)
            {
                chessboard->check_positions[abs(j-(old_rank))][0] = j;
                chessboard->check_positions[abs(j-(old_rank))][1] = i;
                chessboard->line_of_sight_distance++ ;
            }
            if(chessboard->board[j][i] != NULL)
            {
                
                return false ;
            }
            
        }
    }
    
    if(new_rank > old_rank && new_file < old_file)
    {
        for(int j = old_rank+1 ; j < new_rank ; j++)
        {
            
            i = old_file - (j-old_rank) ;
            if(record_line_of_sight == true)
            {
                chessboard->check_positions[j-(old_rank)][0] = j;
                chessboard->check_positions[j-(old_rank)][1] = i;
                chessboard->line_of_sight_distance++ ;
            }            
            if(chessboard->board[j][i] != NULL)
            {
                return false ;
            }
        }
    }
    
    if(new_rank < old_rank && new_file > old_file)
    {
        for(int j = old_rank-1 ; j > new_rank ; j--)
        {
            i = old_file + (old_rank-j) ;
            if(record_line_of_sight == true)
            {
                chessboard->check_positions[abs(j-(old_rank))][0] = j;
                chessboard->check_positions[abs(j-(old_rank))][1] = i;
                chessboard->line_of_sight_distance++ ;
            }            
            if(chessboard->board[j][i] != NULL)
            {
                return false ;
            }
        }
    }
    
    return true ;
}

bool BasePiece::straight_check(int old_rank,int old_file,int new_rank,
                               int new_file,bool record_line_of_sight)
{
    
    //Check to see if anything is in the way
    if(old_rank == new_rank)
    {
        //Check to see if anything is in the way
        if(new_file > old_file)
        {
            for(int i = old_file + 1 ; i < new_file ; i++)
            {
                if(record_line_of_sight == true)
                {
                    chessboard->check_positions[i-(old_file)][0] = new_rank;
                    chessboard->check_positions[i-(old_file)][1] = i;
                    chessboard->line_of_sight_distance++ ;
                }
                if(chessboard->board[old_rank][i] != NULL)
                {
                    return false ;
                }
            }

        }
        //Check to see if anything is in the way
        if(new_file < old_file)
        {    
            for(int i = old_file-1 ; i > new_file ; i--) 
            {
                if(record_line_of_sight == true)
                {
                    chessboard->check_positions[abs(i-(old_file))][0] = new_rank;
                    chessboard->check_positions[abs(i-(old_file))][1] = i;
                    chessboard->line_of_sight_distance++ ;
                }
                if(chessboard->board[old_rank][i] != NULL)
                {
                    return false ;
                }
            }
        }
    }
    //Check to see if anything is in the way
    if(old_file == new_file)
    {
        if(new_rank > old_rank)
        {
            for(int j = old_rank + 1 ; j < new_rank ; j++)
            {
                if(record_line_of_sight == true)
                {
                    chessboard->check_positions[j-(old_rank)][0] = j ;
                    chessboard->check_positions[j-(old_rank)][1] = new_file;
                    chessboard->line_of_sight_distance++ ;
                }
                if(chessboard->board[j][old_file] != NULL)
                {
                    return false ;
                }
            }
        }
        //Check to see if anything is in the way
        if(new_rank < old_rank)
        {
            for(int j = old_rank -1 ; j > new_rank ; j--) 
            {
                if(record_line_of_sight == true)
                {
                    chessboard->check_positions[abs(j-(old_rank))][0] = j ;
                    chessboard->check_positions[abs(j-(old_rank))][1] = new_file;
                    chessboard->line_of_sight_distance++ ;
                }
                if(chessboard->board[j][old_file] != NULL)
                {
                    return false ;
                }
            }
        }
    }
    
    return true ;
}
    
 
BasePiece::~BasePiece() {} 
    
