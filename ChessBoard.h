//Header file for the ChessBoard Class

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "BasePiece.h"
#include "Pawn.h"
#include "Castle.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"

#define Maximum_Ranks	8
#define Maximum_Files	8
#define Rank_and_File   2
#define Number_of_Teams 2
#define Invalid_Move    -1
#define Valid_Move      0
 
using namespace std ;

class ChessBoard {
protected:
    
    //The "board" is comprised of 8x8 Basepiece pointers
    BasePiece* board[Maximum_Ranks][Maximum_Files];
    //Tempoary pointer to use in check mate checks
    BasePiece* temp_pointer = NULL ;
    //Holds the current teams turn
    int Turn;
    bool king_in_check = false;
    //is current move caslting
    bool caslting_move = false ;
    //Number of blocks in the check line of sight
    int line_of_sight_distance = 0;
    //Positions in check line of sight
    int check_positions[Maximum_Ranks][Rank_and_File];
    //Holds the positions of both team's kings
    int king_positions[Number_of_Teams][Rank_and_File];
public:
    
    ChessBoard();
    
    /*Function submits the given move on the board specified in ChessMain.cpp
     * Inputs:
     *          current position (string) - Current Block ID
     *          move_to_position (string) - Destination Block ID*/
    void submitMove(string current_position,string move_to_position);
    
    /*Boolean Function checks whether once the king has been put into check
     whether it can be freed in the current turn by any piece and returns false
     if not: 
     * Inputs:
     *          new rank (integer) - Recent Desintation row number of piece
     *          new file (integer) - Recent Desintation collumn number of piece*/
    bool free_king_check() ;
    
    /*Function checks whether the current move has put the oppostion
     king into a check postion and switches the King_in_Check boolean
     to True if so: 
     * Inputs:
     *          new rank (integer) - Recent Desintation row number of piece
     *          new file (integer) - Recent Desintation collumn number of piece*/
    bool after_move_check(int new_rank,int new_file);
    
    /*Function checks whether any piece in the oppostion team can hypothectically
     put the current teams king in check and returns true if so.The function is 
     used to check whether the the game is in stalemate and whether a move to 
     save the king from check would result in another check scenario.
     Inputs:
            stale_mate_check (boolean) - switch for stalemate scenario*/
    bool check_sweep(bool stale_mate_check = false);
    
    /*Function checks whether the game is in stalemate and returns true if so
     by checking whether any piece in the current team can move without putting
     its king into a check position*/
    bool stale_mate();
    
    /*Function resets the board to the starting setup and changes the current
     turn to White*/
    void resetBoard();
    
    /*Function performs standardised move checks that are unanamous across
     the different pieces (invalid inputs,whether move will result in check..)
    Inputs:
            current position (string) - Current Block ID
            move_to_position (string) - Destination Block ID
            old rank (integer) - current row position of piece
            old_file (integer) - current collumn postion of piece
            new rank (integer) - destination row position of piece
            new file (integer) - desiination collumn position of piece*/
    int default_move_checks(string current_position ,string move_to_position,
                            int old_rank,int old_file,int new_rank,int new_file);
    
    /*Function prints the outcome of the move to the standard output
    Inputs: (dublicate to prevent unessasry further calulations)
            current_position (sting) - Current Block ID 
            move_to_position (sting) -Destination Block ID
            old rank (integer) - current row position of piece
            old_file (integer) - current collumn postion of piece
            new rank (integer) - destination row position of piece
            new file (integer) - desiination collumn position of piece*/
    void print_move(string current_position,string move_to_position,
                int old_rank,int old_file,int new_rank,int new_file);
    
    /*Function performs the move specified by sumbit_move
    Inputs:
            old rank (integer) - current row position of piece
            old_file (integer) - current collumn postion of piece
            new rank (integer) - destination row position of piece
            new file (integer) - desiination collumn position of piece*/
    void perform_move(int old_rank,int old_file,int new_rank,int new_file);
    
    /*Function performs the hypotheical moves to check for stalemate
     returns true if move is possible
    Inputs:
            old rank (integer) - current row position of piece
            old_file (integer) - current collumn postion of piece
            new rank (integer) - destination row position of piece
            new file (integer) - desiination collumn position of piece*/
    bool stalemate_switch(int j,int i,int nj,int ni);

    /*Function to switch turns upon succesful completion of move */
    void switch_turn ();
    
    /*Function to print the piece name based on ID*/
    void print_piece(char position_id);
    
    /*Function to print the team name based on enum (white,black)*/
    void print_team(int colour);
    
    ~ChessBoard();
    
    friend BasePiece ;
    friend Pawn ;
    friend Knight ;
    friend King ;

    
};
    
    
#endif
    
