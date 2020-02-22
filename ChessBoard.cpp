/*Implimentation file for the ChessBoard. Please
 * find the respective function definitions in the ChessBoard.h
 * file */
#include "ChessBoard.h"
#include <iostream>
#include <string>
using namespace std;


ChessBoard::ChessBoard()
{
        
    cout <<"A new chess game is started!"<< endl ;
    Turn = white ;

    for(int j = 0 ; j<Maximum_Ranks; j++)
    {
        for(int i = 0 ; i<Maximum_Files; i++)
        {
            board[j][i] = NULL ;
        }
    }
    
    for(int i = 0 ; i<Maximum_Files; i++)
    {
        board[1][i] = new Pawn(this,white,'P');
        board[6][i] = new Pawn(this,black,'P');
    }
    
    int colour = white ;
    int rank = 0  ;
    for(;colour <= black ; colour++)
    {
        board[rank][1] = new Knight(this,colour,'N') ;
        board[rank][6] = new Knight(this,colour,'N') ;
        board[rank][2] = new Bishop(this,colour,'B') ;
        board[rank][5] = new Bishop(this,colour,'B') ;
        board[rank][0] = new Castle(this,colour,'C') ;
        board[rank][7] = new Castle(this,colour,'C') ;
        board[rank][3] = new Queen(this,colour,'Q') ;
        board[rank][4] = new King(this,colour,'K')  ;
        king_positions[colour][0] = rank ;
        king_positions[colour][1] = 4 ;
    
        rank = 7 ;
    }
}

void ChessBoard::submitMove(string current_position ,string move_to_position) {
    
    
    //Converting the input strings to usable integers
    int old_rank = static_cast<int>(current_position[1]-'1') ;
    int old_file = static_cast<int>(current_position[0]-'A') ;

    int new_rank = static_cast<int>(move_to_position[1]-'1') ;
    int new_file = static_cast<int>(move_to_position[0]-'A') ;
    
    //Perform move default checks
    if(default_move_checks(current_position,move_to_position,old_rank,old_file,
                                                        new_rank,new_file)!=0)
    {
        return ;
    }
    
    //if not check the individual pieces move eligibiltiy
    if(board[old_rank][old_file]->move(old_rank,old_file,new_rank,new_file))
    {
        //if castling is happening 
        if(caslting_move == true)
        {
            print_move(current_position,move_to_position,
                            new_rank,new_file,new_rank,new_file);
            switch_turn() ;
            caslting_move = false ;
            return ;
        }

        //Print move to the screen
        print_move(current_position,move_to_position,
                            old_rank,old_file,new_rank,new_file);
            
        //Perform the move on the board
        perform_move(old_rank,old_file,new_rank,new_file);
        
        //Check whether oppostion team is in check
        if (after_move_check(new_rank,new_file))
        {
            cout << endl ;
            print_team((Turn+1)%2);
            cout << " is in check";
        }
        
        //Change turns
        switch_turn();
        
        //If team is in check,find if king can be saved before next turn
        if(king_in_check == true)
        {
            if(!free_king_check())
            {
                cout << "mate" << endl ;
                return;
            }
        }
        cout << endl ;

        //Check for stalemate before next turn
        if(stale_mate())
        {
            cout << "Game is a stale mate" << endl ;
        }
        return;
        
    }
    
    //If move can't be done for whatever reason print.
    print_team(board[old_rank][old_file]->get_colour());
    cout <<"'s " ;
    print_piece(board[old_rank][old_file]->get_id()) ;
    cout << " cannot move to " << move_to_position << "!" << endl ;
    
    return;
}
    
void ChessBoard::resetBoard()
{
    this->~ChessBoard(); // destruct
    new(this) ChessBoard(); // reconstruct
} 



void ChessBoard::switch_turn ()
{
    Turn = (Turn + 1)%2 ;
}

void ChessBoard::print_piece(char position_id)
{
    switch (position_id)
	{
		case 'P':     cout << "Pawn";
                         break ;
		case 'N':     cout << "Knight";
                         break ;
		case 'C':     cout << "Castle";
                         break ;
		case 'B':     cout << "Bishop";
                         break ;
		case 'Q':     cout << "Queen";
                         break ;
        case 'K':     cout << "King";
                         break ;
	}
}

void ChessBoard::print_team(int colour)
{
    switch (colour)
	{
		case 0:     cout << "White";
                         break ;
		case 1:     cout << "Black";
                         break;
	}
}


ChessBoard::~ChessBoard()
{
    for(int j = 0 ; j<Maximum_Ranks; j++)
    {
        for(int i=0;i<Maximum_Files; i++)
        {
            if(board[j][i] != NULL)
            {
                delete board[j][i] ;
                board[j][i] = NULL ;
            }
        }
    }
}


bool ChessBoard::free_king_check()
{
    for(int j = 0 ; j<Maximum_Ranks; j++)
    {
       for(int i = 0 ; i<Maximum_Files; i++)
       {
           if(board[j][i] != NULL && board[j][i]->get_colour() == Turn)
           {
               for(int k = 0 ; k<=line_of_sight_distance ; k++)
               {
                   //Go through the line of sight of the piece and
                    if(board[j][i]->move(j,i,check_positions[k][0],
                                            check_positions[k][1]))
                    {
                        /*if the current piece is the king and its not killing the 
                         * other team's piece with the line of sight*/
                        if((board[j][i]->get_id() == 'K') && k != 0)
                        {
                            //skip as this move is not valid
                            continue ;
                        }
                        /*Temporarily moves the piece to the new postion if its
                         * not the kings position*/
                        if(k > 0)
                        {
                            board[check_positions[k][0]][check_positions[k][1]]
                                        = board[j][i] ;
                            board[j][i] = NULL ;
                        }
                        /*Sweep through the other team to ensure that a line of
                         * sight has not opened up with the positions swapped out*/
                        if(!check_sweep())
                        {
                            //put the piece back to original posiiton after sweep
                            if(k>0)
                            {
                                board[j][i] = board[check_positions[k][0]]
                                              [check_positions[k][1]];
                                board[check_positions[k][0]]
                                            [check_positions[k][1]] = NULL ;
                            }
                            //Set that the king has been saved
                            king_in_check = false ;
                            return true;
                        }
                        if(k>0)
                        {   //put the piece back to original posiiton after sweep
                            board[j][i] = board[check_positions[k][0]]
                                                [check_positions[k][1]] ;
                            board[check_positions[k][0]]
                                        [check_positions[k][1]] = NULL ;
                        }
                    }
               }
           }
       }
    }

    //The king cannot be saved(Check mate)
    return false ;
                
}
   
bool ChessBoard::after_move_check(int new_rank,int new_file)
{
    //Get opposition kings position
    int kings_rank =  king_positions[(Turn+1)%2][0];
    int kings_file =  king_positions[(Turn+1)%2][1];
    //Reset check line of site distance to zero
    line_of_sight_distance = 0 ;
    //if the piece can move to the king record line of sight (true)
    if(board[new_rank][new_file]->move(new_rank,new_file,kings_rank,
                                            kings_file,true))
    {
        //Set that king is in check
        king_in_check = true ;
        //set first check positon to the current positon of piece
        check_positions[0][0] = new_rank;
        check_positions[0][1] = new_file;
        return true ;
    }
  
    return false ;
                
}
 

bool ChessBoard::check_sweep(bool stale_mate_check)
 {
    //Gets its own kings position
    int kings_rank =  king_positions[Turn][0];
    int kings_file =  king_positions[Turn][1];

     for(int j = 0 ; j<Maximum_Ranks; j++)
     {
         for(int i = 0 ; i<Maximum_Files; i++)
         {
             //Finds positions of opposition teams peices
             if(board[j][i] != NULL && board[j][i]->get_colour() == ((Turn+1)%2))
             {
                 /*if its the postion that has just been moved there to make the
                  * check in the previous turn ignore it*/
                 if((j == check_positions[0][0] && i == check_positions[0][1]) 
                        && stale_mate_check == false)
                 {
                     continue ;
                 }
                 //Finds positions of opposition team's peices
                 if(board[j][i]->move(j,i,kings_rank,kings_file))
                 {
                     //King is in check again
                     return true ;
                 }
             }
         }
     }
     //King is not in check
     return false ;
 }
     

bool ChessBoard::stale_mate() 
{
    for(int j = 0; j<Maximum_Ranks; j++)
    {
       for(int i = 0; i<Maximum_Files; i++)
       {
           //Sees if any piece can move to any board position 
           if(board[j][i] != NULL && board[j][i]->get_colour()==Turn)
           {
               for(int nj = 0 ;nj<Maximum_Ranks; nj++)
               {
                   for(int ni = 0 ; ni<Maximum_Files; ni++)
                   {
                       //Prevents the piece moving to its own square
                       if(nj == j && ni == i)
                       {
                           continue;
                       }
                       //Prevents the piece moving to a square occupied by its own team
                       if(board[nj][ni]!=NULL && (board[nj][ni]->get_colour()==Turn))
                       {
                           continue ;
                       }

                       if(board[j][i]->move(j,i,nj,ni))
                       {
                        //if move can be performed it is not stalemate
                         if(stalemate_switch(j,i,nj,ni))
                         {
                             return false ;
                         }
                         
                       }
                   }
               }
           }
       }
    }
    //Board is in stalemate
    return true ;
}
                       

void ChessBoard::print_move(string current_position ,string move_to_position,
                        int old_rank,int old_file,int new_rank,int new_file)
{
    if(board[new_rank][new_file] != NULL && caslting_move==false)
    {
            print_team(board[old_rank][old_file]->get_colour());
            cout <<"'s " ;
            print_piece(board[old_rank][old_file]->get_id()) ;
            cout << " moves from " << current_position << " to " ;
            cout << move_to_position << " taking " ;
            print_team(board[new_rank][new_file]->get_colour());
            cout <<"'s " ;
            print_piece(board[new_rank][new_file]->get_id()) ;
            return ;
    }
    print_team(board[old_rank][old_file]->get_colour());
    cout <<"'s " ;
    print_piece(board[old_rank][old_file]->get_id()) ;
    cout << " moves from " << current_position << " to " ;
    cout << move_to_position ;
    if(caslting_move == true)
    {
        cout << " under castling rules" ;
    }
    return ;
}
    
void ChessBoard::perform_move(int old_rank,int old_file,int new_rank,
                              int new_file)
{

    if(board[new_rank][new_file] != NULL)
    {
        delete board[new_rank][new_file] ;
        board[new_rank][new_file] = board[old_rank][old_file] ;
        board[old_rank][old_file] = NULL ;
        board[new_rank][new_file]->increment_nr_moves() ;
        return ;
    }
    board[new_rank][new_file] = board[old_rank][old_file] ;
    board[old_rank][old_file] = NULL ;
    board[new_rank][new_file]->increment_nr_moves() ;
    return;
}

int ChessBoard::default_move_checks(string current_position ,string move_to_position,
                                    int old_rank,int old_file,int new_rank,int new_file)
{
    //Check for silly inputs 
    if(new_rank > 7 || new_rank < 0)
    {
        cout << "Block does not exist" << endl ;
        return Invalid_Move;
    }
    if(new_file > 7 || new_file < 0)
    {
        cout << "Block does not exist" << endl ;
        return Invalid_Move;
    }
    
    if(new_rank == old_rank && new_file==old_file)
    {
        cout << "Can't stay in the same square" << endl ;
        return Invalid_Move;
    }
    
    
    //Check for piece 
    if(board[old_rank][old_file] == NULL )
    {
        cout << "There is no piece at position " << current_position;
        cout <<"!" << endl ;
        return Invalid_Move;
    }
    

    if(board[old_rank][old_file]->get_colour() != Turn)
    {
        cout << "It is not " ;
        print_team(board[old_rank][old_file]->get_colour());
        cout << "'s turn to move!" << endl ;
        return Invalid_Move;
    }
    
    //Check to see if the piece in the new position is of the same team 
    if(board[new_rank][new_file] != NULL &&
        board[new_rank][new_file]->get_colour() == Turn)
    {
        print_team(board[old_rank][old_file]->get_colour());
        cout <<"'s " ;
        print_piece(board[old_rank][old_file]->get_id()) ;
        cout << " cannot move to " << move_to_position << "!" << endl; 
        return Invalid_Move;
    }
    
    
    //check to see if the move will put the king in check
    if(board[new_rank][new_file]!= NULL)
    {
        temp_pointer = board[new_rank][new_file];
    }
    
    board[new_rank][new_file] = board[old_rank][old_file];
    board[old_rank][old_file] = NULL;
    if(check_sweep(true))
    {
        board[old_rank][old_file] = board[new_rank][new_file];
        board[new_rank][new_file] = temp_pointer ;
        temp_pointer = NULL ;
        print_team(board[old_rank][old_rank]->get_colour());
        cout <<"'s " ;
        print_piece(board[old_rank][old_rank]->get_id()) ;
        cout << " cannot move to " << move_to_position << "!" ;
        cout << " the king will be in check." << endl ;
        return Invalid_Move;
    }
    board[old_rank][old_file] = board[new_rank][new_file];
    board[new_rank][new_file] = temp_pointer ;
    temp_pointer = NULL ;
    
    
    return Valid_Move;
    
}
    

bool ChessBoard::stalemate_switch(int j,int i,int nj,int ni) 
{
    //if block is occupied assign temporary pointer
    if(board[nj][ni] != NULL)
    {
        temp_pointer = board[nj][ni] ;
    }
    
    //temporarily moves the piece to the new postion
    board[nj][ni] = board[j][i];
    if(board[j][i]->get_id() == 'K')
    {
        //if piece is king update kings position
        king_positions[Turn][0] = nj ;
        king_positions[Turn][1] = ni ;
    }
    board[j][i] = NULL ;

    //check to see whether the move has put the king in check
    if(!check_sweep(true))
    {
        //move it back after the sweep
        board[j][i] = board[nj][ni] ;
        board[nj][ni] = temp_pointer ;
        temp_pointer = NULL ;
        
        if(board[j][i]->get_id() == 'K')
        {
            //if piece is king revert to kings original position
            king_positions[Turn][0] = j ;
            king_positions[Turn][1] = i ;
        }
        //return that the move is possible
        return true ;
    }
    
    //move it back after sweeping check
    board[j][i] = board[nj][ni] ;
    board[nj][ni] = temp_pointer ;
    temp_pointer = NULL ;
    if(board[j][i]->get_id() == 'K')
    {
        //if piece is king revert to kings original position
        king_positions[Turn][0] = j ;
        king_positions[Turn][0] = i ;
    }
    
    //return that the move is not possible
    return false ;
    
}
