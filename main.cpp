#include <curses.h>
#include <iostream>
#include <utility>
#include "getChar.hpp"
#include "screen.hpp"
#include "worm.hpp"
#include <string> 
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <tuple>

void startup( void );
void terminate( void );
int drawHeader( int col );
void drawScore( int score );
void drawBorder( int row, int col );
std::tuple<int,int,int> generateNewMunchie(Screen &screen);

const int MIN_ROWS = 9;
const int MAX_ROWS = 25;
const int MIN_COLS = 9;
const int MAX_COLS = 80;


int main(int argc, const char * argv[])
{
     if( argc != 3) {
            std::cout << "usage: " << argv[0] << "\n";
            exit(1);
     }
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    if (row < MIN_ROWS || row  > MAX_ROWS || col < MIN_COLS || col > MAX_COLS){
        std::cout << "Invalid row or colummns entries. Row range:( 9 - 25 )    Col Range:( 9 - 80)";
        exit(2);
    }

     int c, scoreCol;
     int score = 0;
     startup(); 
     move(0,0);
     scoreCol = drawHeader(col);                               // draws the worm and score header of the game
     drawScore(score);                                                             // draws the initial score
     drawBorder(row, col);                                                       // draws the asterisk border

     Screen screen(row, col);                                                            // initialize screen
     std::pair<int,int> freecell = screen.generateRandomFreeCell();         // get freecell to draw worm head
     int newRow = newRow = std::get<0>(freecell);     // row of the freecell where we will draw the worm head
     int newCol = std::get<1>(freecell);              // col of the freecell where we will draw the worm head
     Worm worm((row - 2) * (col - 2), newRow, newCol);     // initialize worm vector and define head and tail
     mvaddch(newRow,newCol,'@');                                                        // draw the worm head
     screen.removeFromFreePool(newRow,newCol);                   // set the position of the worm head as used
     std::tuple<int,int,int> newMunchie = generateNewMunchie(screen);           // generate the first mumchie
     refresh();                                                   // display the game, worm head, and munchie
     int linksToAdd = 0;  // accumulator for the number of links to be added to the worm when a munchie eaten
     bool notInit = false;       // flags we are in first loop of the game to control initial board variables

     do {
          mvaddch(std::get<0>(worm.head()), std::get<1>(worm.head()), 'o');   // add a tail, remove if needed
          if (notInit){                                                                 // not the first loop
               mvaddch(newRow,newCol,'@');                                          // progress the worm head
               worm.addHead(newRow,newCol);                               // add worm head to the worm vector
               screen.removeFromFreePool(newRow,newCol);         // set the position of the worm head as used
          }

          if(newRow != std::get<0>(newMunchie) || newCol != std::get<1>(newMunchie)){   // not a munchie cell
               if (notInit && linksToAdd <= 0){    // not the first loop, no links to add, so remove the tail
                    mvaddch(std::get<0>(worm.tail()), std::get<1>(worm.tail()), ' ');  // clear cell on board
                    worm.removeTail();                                        // remove tail from worm vector
                    screen.makeFree(std::get<0>(worm.tail()), std::get<1>(worm.tail()));  // set tail as free
               }
               else
                    linksToAdd--;  // we didnt remove the tail, so one less link to add to the worm next turn
          }
          else {                                                                         // is a munchie cell
               linksToAdd += std::get<2>(newMunchie);  // get the value of the munchie and adjust accumulator
               score += std::get<2>(newMunchie);             // adjust the score based on munchie value eaten
               move(0, scoreCol + 7);                                               // move to score position
               drawScore(score);                                                        // draw the new score
               newMunchie = generateNewMunchie(screen);                               // generate new munchie
          }
          refresh();                                                     // display the new state of the game
          
          char newChar = get_char();                                                      // get player input
          switch (newChar){
               case 'l': newCol++;                                                      // player moves right
                    break;                                               
               case 'h': newCol--;                                                       // player moves left 
                    break;
               case 'k': newRow--;                                                         // player moves up 
                    break;
               case 'j': newRow++;                                                       // player moves down 
                    break;
               default: break;                                // player moves the same direction as last move
          }
          notInit = true;                                               // set loop flag to out of first loop 
     
     } while(screen.isFree(newRow,newCol));  // game procesds if the next position determined by user is free
     
     terminate();                                                         // otherwise the game end and exits
}






void startup( void ){
     initscr();	                                                                       // activate curses
     curs_set(0);                                                                // do not display the cursor
     clear();	                                                      // clear the screen that curses provides
     noecho();	                                         // prevent the input chars to be echoed to the screen
     cbreak();	           // characters are delivered to the program as they are typed, no need to hit return
}






void terminate( void ){
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     clear();
     refresh();
     endwin();
}






int drawHeader( int col ){
     int nextCol;
     if (col < 15){
          addstr("Worm");
          move(0,8);
          nextCol = 8;
     }
     else if (col < 21){
          addstr("Worm");
          move(0,col-8);
          nextCol = col - 8;
     }
     else{
          move(0,3);
          addstr("Worm");
          move(0,col-11);
          nextCol = col - 11;
     }
     addstr("Score  ");
     return nextCol;
}






void drawScore( int score ){
     for (auto letter : std::to_string(score))
          addch(letter);
}






void drawBorder( int row, int col ){
     for (int r = 1; r <= row; r++){
          for (int c = 0; c < col; c++){
               move(r, c);
               if (r == 1 || c == 0 || r == row || c == col - 1){
                    addch('*');
               }
          }
     }
}






std::tuple<int,int,int> generateNewMunchie(Screen &screen){
     std::pair<int,int> munchieCell = screen.generateRandomFreeCell();
     int newRow = std::get<0>(munchieCell);
     int newCol = std::get<1>(munchieCell);
     srand (time(NULL));
     int munchieValue = rand() % 9 + 1;
     char munchie = std::to_string(munchieValue)[0];
     mvaddch(newRow, newCol, munchie);
     return std::make_tuple(newRow,newCol,munchieValue);
}