/*
Name: Abhi Verma
Purpose: Simulates John Conway's Game of Life. Asks user for size of board and cells to set alive and then gives options to print current generation, calculate next generations, check if cell is alive, or print a number of generations.

'.' represents dead cell.
'*' represents alive cell.

Remember coordinate (0,0) starts at the top left corner of the board and increases down and right.

Coordinates to setup glider (becomes the same after 4 generations):
	(1, 0)
  (2, 1)
  (0, 2)
  (1, 2)
  (2, 2)
*/

#include <stdio.h>

//global variables for size of board
int rows;
int cols;

//declaring functions
void setAlive(char board[][cols], int y, int x);
int isAlive(char board[][cols], int y, int x);
void calcNextGen(char board[][cols]);
int calcNeighbours(char board[][cols], int y, int x);
void print(char board[][cols]);

int main(void) {
  
  //declaring needed variables
  int xCoord, yCoord;
  int decision;
  int currentGen=0;
  int gens;
  int newGen;

  printf("Welcome to John Conway's Game of Life. Remember, the coordinate (0,0) starts at the top left corner of the board and increases down and right.\n\n'.' represents a dead cell\n'*' represents an alive cell\n\nHave fun!\n\nP.S. Coordinates to setup glider (becomes the same after 4 generations):\n(1, 0)\n(2, 1)\n(0, 2)\n(1, 2)\n(2, 2)\n\n");
  //makes board of this size
  printf("Enter a positive integer number for rows of the board: \n");
  scanf("%d",&rows);
  printf("\n");
  
  printf("Enter a positive integer number for columns of the board: \n");
  scanf("%d",&cols);
  printf("\n");
  
  char board[rows][cols];
  
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      board[i][j]='.';
    }
  }

  //makes indicated cells alive
  printf("Enter coordinate of cell, within bounds of the board, that you want alive in the form x,y:\n");
  scanf("%d, %d", &xCoord, &yCoord);
  printf("\n");
  setAlive(board, yCoord, xCoord);

  while(yCoord!=-1 && xCoord!=-1){
    
    printf("Continue to enter coordinates of cells that you want alive. Make both coordinates -1 when finished:\n");
    scanf("%d, %d", &xCoord, &yCoord);
    printf("\n");
    setAlive(board, yCoord, xCoord);
  }

  printf("What would you like to do now?:\n");
  printf("[1] Print current generation\n[2] Go forward n generations\n[3] Go forward and print n generations\n[4] Check if cell is alive or dead\n[5] Exit game\n");
  scanf("%d", &decision);
  printf("\n");

  //loops through game until user wants to exit
  while(decision!=5){

    //prints current generation
    if(decision==1){
    
      print(board);
      printf("\n");
      
    }

    //goes forward indicated number of generations
    else if(decision==2){
      
      printf("How many generations would you like to go forward?\n");
      scanf("%d",&gens);
      printf("\n");
  
      newGen = currentGen+gens;
      
      for (currentGen; currentGen < newGen; currentGen++) {
        calcNextGen(board);
  	  }
      
      currentGen = newGen;
      
    }

    //goes forward and prints indicated number of generations
    else if(decision==3){
      
      printf("How many generations would you like to go forward?\n");
      scanf("%d",&gens);
      printf("\n");
  
      newGen = currentGen+gens;
      
      for (currentGen; currentGen < newGen; currentGen++) {
  		  printf("generation: %d\n",currentGen);
        print(board);
        printf("\n");
        calcNextGen(board);
    	}
      
      printf("generation: %d\n",currentGen);
      print(board);
      printf("\n");
      
      currentGen = newGen;
      
    }

    //checks if cell is alive or dead
    else if(decision==4){
      
      printf("Enter the coordinate of the cell would you like to check in the form x,y: \n");
      scanf("%d,%d",&xCoord,&yCoord);
      printf("\n");
  
      if(isAlive(board, yCoord, xCoord)==0){
        printf("The cell is not alive\n");
        printf("\n");
      }
      
      else{
        printf("The cell is alive\n");
        printf("\n");
      }
      
    }

    printf("What would you like to do now?:\n");
    printf("[1] Print current generation   [2] Go forward n generations   [3] Go forward and print n generations   [4] Check if cell is alive or dead   [5] Exit game\n");
    scanf("%d", &decision);
    printf("\n");
  }
  
  return 0;
}

//function to make cell alive
void setAlive(char board[][cols], int y, int x){
  
  //checks if indexes entered are within bounds of board, otherwise does nothing
  if(x>=0 && x<cols && y>=0 && y<rows){
    board[y][x]='*';
  }
}

//checks if cell is alive and returns 1 if it is or 0 if it is not
int isAlive(char board[][cols], int y, int x){
  
  //checks if indexes entered are within bounds of board, otherwise does nothing
  if(x>=0 && x<cols && y>=0 && y<rows){
    
    if(board[y][x]=='.'){
      return 0;
    }
      
    else{
      return 1;
    }
  }
}

//calculates the next generation of cells according to rules of game
void calcNextGen(char board[][cols]){
  
  char newBoard[rows][cols];
  int neighbours;

  //loops through entire board and makes new generation in a new board
  for(int i=0; i<rows; i++){
    
    for(int j=0; j<cols; j++){
      neighbours = calcNeighbours(board,i,j);
      
      if(board[i][j]=='.' && neighbours==3){
        newBoard[i][j]='*';
      }
      else if(board[i][j]=='*' && neighbours>=4){
        newBoard[i][j]='.';
      }
      else if(board[i][j]=='*' && neighbours<=1){
        newBoard[i][j]='.';
      }
      else{
        newBoard[i][j]=board[i][j];
      }
    }
  }

  //copies the new board into the board
  for(int k=0; k<rows; k++){
    
    for(int l=0; l<cols; l++){
      board[k][l] = newBoard[k][l];
    }
  }
}

//calculates neighbours surrounding cell
int calcNeighbours(char board[][cols], int y, int x){
  
  int neighbours=0;
  int ymin = y-1;
  int ymax = y+1;
  int xmin = x-1;
  int xmax = x+1;

  //first row
  if(y==0){
    ymin++;
    
    if(x==0){
      xmin++;
    }
      
    else if(x==cols-1){
      xmax--;
    }
  }

  //last row
  else if(y==rows-1){
    ymax--;
    
    if(x==0){
      xmin++;
    }
      
    else if(x==cols-1){
      xmax--;
    }
  }

  //first column
  else if(x==0){
    xmin++;
  }

  //last column
  else if(x==rows-1){
    xmax--;
  }

  //checks for neighbours
  for(int i=ymin; i<=ymax; i++){
    
    for(int j=xmin; j<=xmax; j++){
      
      if(board[i][j]=='*'){
        neighbours++;
      }
    }
  }

  //subtracts one if cell is alive since it counts itself as neighbour
  if(isAlive(board,y,x)==1){
    neighbours--;
  }
  
  return neighbours;
}

//prints board
void print(char board[][cols]){
  
  for(int i=0; i<rows; i++){
    
    for(int j=0; j<cols; j++){
      printf("%c",board[i][j]);
    }
    
    printf("\n");
  }
}