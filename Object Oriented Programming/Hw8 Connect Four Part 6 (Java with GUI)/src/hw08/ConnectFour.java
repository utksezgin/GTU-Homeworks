package hw08;

import java.util.Random;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

/**
 * public class ConnectFour
 * extends JFrame
 * An extended version of JFrame to play game called Connect Four. <br>
 * In Connect Four you can choose tou play against an AI or human on a square board with size of your choose of number more than 4.
 * <br> <br>
 * <b>Known Bugs:</b><br>
 * Can only choose to play against AI or Human on start, have to restart the program in order to change it.
 * 
 * @author Azmi Utku Sezgin 131044048
 */
public class ConnectFour extends JFrame{
    
    private JButton singleP;
    private JButton multiP;
    private JTextField boardSize;
    private ConnectFour newGame;
    private String textOutp;
    private int newSize;
    private int isGameOver; //0:Game not over 1: Game over -> 2:Draw
    private int whosTurn; //Holds the information of who's turn to play 1 or 2
    private int isAI;	//Holds if player's chosen to play against AI or Player
    private int maxWidth; //4 Min - 26 Max   //Can be changed via constant integers
    private int maxHeight; //4 Min - 50 Max //i.e MIN_HEIGHT, MAX_WIDTH etc.
    private Cell[][] gameCells; //Holds information of cells on the board in Cell class objects

    /**
     * Non-parameter constructor that asks user the play mode and size initially.
     */
    ConnectFour(){//Creates a 4x4 board game
        //GUI
        super("Connect Four");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        getContentPane().setBackground(Color.lightGray);
        setLocationRelativeTo(null);

        setLayout(null);

        singleP = new JButton("Single Player");
        multiP = new JButton("Multi Player");


        singleP.setToolTipText("Single Player");


        singleP.setBounds(0, 500, 100, 100);
        singleP.setLocation(220, 220);
        singleP.setToolTipText("Single Player");
        singleP.setVisible(true);

        multiP.setBounds(0, 500, 100, 100);
        multiP.setLocation(420, 220);
        multiP.setToolTipText("Multi Player");
        multiP.setVisible(true);

        add(singleP);
        add(multiP);   

        ActionHandler actionH = new ActionHandler();

        singleP.addActionListener(actionH);
        multiP.addActionListener(actionH);
        
        //Class
        setVisible(true);
	whosTurn = 1;
	isAI = 0;
	maxHeight = 4;
	maxWidth = 4;
        isGameOver = 0;
	resizeBoard(maxHeight);
        
	//Initializing cells	
	for(int i=0; i<maxHeight; ++i){
            for(int j=0; j<maxWidth; ++j){
                gameCells[i][j].setHeight(i);
                gameCells[i][j].setHeight(j);
                gameCells[i][j].setStatus("Empty");
            }
	}
		
    } 
    
    /**
     * Method that returns width size of the board.
     * @return
     * Returns the width of the board.
     */
    public int getMaxWidth(){ return maxWidth; }; //Returns maxWidth//Returns maxWidth

    /**
     * Method that returns height size of the board.
     * @return
     * Returns the height of the board.
     */
    public int getMaxHeight() { return maxHeight; }; //Returns maxHeight//Returns maxHeight

    /**
     * Method that returns the width of given cell throws exception for illegal arguments.
     * @param height height of the cell.
     * @param width width of the cell.
     * @return
     * Returns the width of the cell
     *<br> 
     * Throws java.lang.IllegalArgumentException on out of ranged input.
     */
    public int getCellWidth(int height, int width){ //returns cell row
	if(width > maxWidth || height > maxHeight){
            throw new java.lang.IllegalArgumentException("Out of boundary");
	}
	else
            return gameCells[height][width].getWidth();
    }

    /**
     * Method that returns the height of given cell throws exception for illegal arguments.
     * @param height height of the cell.
     * @param width width of the cell.
     * @return
     * Returns the height of the cell
     *<br> 
     * Throws java.lang.IllegalArgumentException on out of ranged input.
     */
    public int getCellHeight(int height, int width){ //Returns Cell column
	if(width >= maxWidth || height >= maxHeight){
            throw new java.lang.IllegalArgumentException("Out of boundary");
	}
	else
            return gameCells[height][width].getHeight();
    } 
    
    /**
     * Method that returns the status of given cell throws exception for illegal arguments.
     * @param height height of the cell.
     * @param width width of the cell.
     * @return
     * Returns the status of the cell
     *<br> 
     * Throws java.lang.IllegalArgumentException on out of ranged input.
     */
    public String getCellStatus(int height, int width) { //Returns cell status
	if(width > maxWidth || height > maxHeight){	
            throw new java.lang.IllegalArgumentException("Out of boundary");
	}
	else
            return gameCells[height][width].getStatus();
    } 

    /**
     * This method returns 1 if the game mode is PvC and 0 for PvP
     * @return Returns the game mode.
     */
    public int getIsAI(){ return isAI; };	//Returns iSAI member//Returns iSAI member

    /**
     * This method returns the current status of the game. -1 if the game is still going, 2 for draw, 1 if either player won.
     * @return Current status of the game.
     */
    public int getIsGameOver() { return isGameOver; }; //Returns isGameOver member

    /**
     * This method returns 1 if it's player 1s turn, 2 for player2
     * @return
     * Returns the value of whosTurn
     */
    public int getWhosTurn(){ return whosTurn; }; //Returns whosTurn member//Returns whosTurn member

    /**
     * Changes the size of board. Cannot be overridden.
     * @param newSize New size for the board.
     */
    
    public final void resizeBoard(int newSize){ //Resizes the board
        
	gameCells = new Cell[newSize][newSize];
        for(int i=0; i<newSize; ++i){
            for(int j=0; j<newSize; ++j){
                gameCells[i][j] = new Cell();
            }
        }
        
        
	maxHeight = newSize;
	maxWidth = newSize;
      }   
    
    /**
     * Makes the move on the board.
     * @param player User1 for Player1, User2 for player2, Computer for AI.
     * @param w column of the play
     * @return returns -1 if unsuccessful or the row of the play.
     */
    public int makeMove(String player, int w){//Checks if the move is legal and makes the move.
	int row = -1;
	for(int i=maxHeight-1; i>-1; --i){
            if(gameCells[i][w].getStatus().equals("Empty")){
                row = i;
                i = -1;
            }
	}
        Color playerColor;
        if(whosTurn == 1)
            playerColor = Color.BLUE;
        else
            playerColor = Color.RED;
	if(checkIllegalMove(w)){
            gameCells[row][w].setStatus(player);
            gameCells[row][w].setBackground(playerColor);
        }
        return row;
    }
    
    /**
     * Checks if there's an empty row on given column.
     * @param w column from the board to check for an empty cell
     * @return Returns true for legal move, false for illegal move.
     */
    public boolean checkIllegalMove(int w){
	boolean isIllegal = false;
	if(maxWidth > w && w>=0){
            for(int i=maxHeight-1; i>=0; --i){
                if(gameCells[i][w].getStatus().equals("Empty")){
                    isIllegal = true;
                }
            }
	}
	if(isIllegal == false && isAI == 0)
		System.out.println("Illegal Move");
	return isIllegal;		
    } //Checks if the move is illegal

    /**
     * This method returns -1 if game is not over, 2 for draw, 1 if there's a winner and highlights the winner cells in yellow.
     * @return Returns -1 if game is not over, 2 for draw, 1
     */
    public int checkWinner(){
	int OFFSET = 3;
	int isWinner = 2; //Set to 2 by default. 2 Stands for draw.
	int winnerCell = 1;
	//Checking for Draw.
	for(int i=0; i<maxHeight; ++i){   //i stands for columns
            for(int j=0; j<maxWidth; ++j){ //j stands for rows
                if(gameCells[i][j].getStatus().equals("Empty")){ //If there's an empty cell, it's not draw
                    isWinner = -1;
                }
            }
	}
	
	for(int i=0; i<maxHeight; ++i){   //i stands for columns
            for(int j=0; j<maxWidth; ++j){ //j stands for rows
                if(!gameCells[i][j].getStatus().equals("Empty")){ //Checks if that cell is empty			
                    if(j<maxWidth-OFFSET){ //Preventing overflow
                        if(gameCells[i][j].getStatus().equals(gameCells[i][j+1].getStatus()) ){       	//Checking rightwards       
                            if(gameCells[i][j].getStatus().equals(gameCells[i][j+2].getStatus()) ){		//horizontal
                                if(gameCells[i][j].getStatus().equals(gameCells[i][j+3].getStatus()) ){
                                isWinner = 1;
                                gameCells[i][j].setWinnerCell(winnerCell);
                                gameCells[i][j+1].setWinnerCell(winnerCell);
                                gameCells[i][j+2].setWinnerCell(winnerCell);
                                gameCells[i][j+3].setWinnerCell(winnerCell);
                                
                                gameCells[i][j].setBackground(Color.yellow);
                                gameCells[i][j+1].setBackground(Color.yellow);
                                gameCells[i][j+2].setBackground(Color.yellow);
                                gameCells[i][j+3].setBackground(Color.yellow);
                                
                            }
                    }
            }
    }
    if(isWinner != 1){
            if(j>OFFSET-1){ //Preventing overflow
                    if(gameCells[i][j].getStatus().equals(gameCells[i][j-1].getStatus()) ){       	//Checking leftwards       
                            if(gameCells[i][j].getStatus().equals(gameCells[i][j-2].getStatus()) ){		//horizontal
                                if(gameCells[i][j].getStatus().equals(gameCells[i][j-3].getStatus()) ){
                                    isWinner = 1;
                                    gameCells[i][j].setWinnerCell(winnerCell);
                                    gameCells[i][j-1].setWinnerCell(winnerCell);
                                    gameCells[i][j-2].setWinnerCell(winnerCell);
                                    gameCells[i][j-3].setWinnerCell(winnerCell);
                                    
                                    gameCells[i][j].setBackground(Color.yellow);
                                    gameCells[i][j-1].setBackground(Color.yellow);
                                    gameCells[i][j-2].setBackground(Color.yellow);
                                    gameCells[i][j-3].setBackground(Color.yellow);
                                } 
                        }
                }
        }
}
if(isWinner != 1){
        if(i<maxHeight-OFFSET){ //Preventing overflow
                if(gameCells[i][j].getStatus().equals(gameCells[i+1][j].getStatus()) ){       	//Checking downwards       
                        if(gameCells[i][j].getStatus().equals(gameCells[i+2][j].getStatus()) ){		//vertical
                                if(gameCells[i][j].getStatus().equals(gameCells[i+3][j].getStatus()) ){
                                    isWinner = 1;
                                    gameCells[i][j].setWinnerCell(winnerCell);
                                    gameCells[i+1][j].setWinnerCell(winnerCell);
                                    gameCells[i+2][j].setWinnerCell(winnerCell);
                                    gameCells[i+3][j].setWinnerCell(winnerCell);
                                    
                                    gameCells[i][j].setBackground(Color.yellow);
                                    gameCells[i+1][j].setBackground(Color.yellow);
                                    gameCells[i+2][j].setBackground(Color.yellow);
                                    gameCells[i+3][j].setBackground(Color.yellow);
                                }
                        }
                }
        }
}
if(isWinner !=1){
        if(i>OFFSET-1){ //Preventing overflow
                if(gameCells[i][j].getStatus().equals(gameCells[i-1][j].getStatus()) ){       	//Checking upwards       
                        if(gameCells[i][j].getStatus().equals(gameCells[i-2][j].getStatus()) ){		//vertical
                                if(gameCells[i][j].getStatus().equals(gameCells[i-3][j].getStatus()) ){
                                    isWinner = 1;
                                    gameCells[i][j].setWinnerCell(winnerCell);
                                    gameCells[i-1][j].setWinnerCell(winnerCell);
                                    gameCells[i-2][j].setWinnerCell(winnerCell);
                                    gameCells[i-3][j].setWinnerCell(winnerCell);
                                    
                                    gameCells[i][j].setBackground(Color.yellow);
                                    gameCells[i-1][j].setBackground(Color.yellow);
                                    gameCells[i-2][j].setBackground(Color.yellow);
                                    gameCells[i-3][j].setBackground(Color.yellow);
                                }
                        }
                }
        }
}
if(isWinner !=1){
        if(i>OFFSET-1 && j<maxWidth - OFFSET){ //Preventing overflow
                if(gameCells[i][j].getStatus().equals(gameCells[i-1][j+1].getStatus()) ){       	//Top-Right      
                        if(gameCells[i][j].getStatus().equals(gameCells[i-2][j+2].getStatus()) ){		//Diagonal
                                if(gameCells[i][j].getStatus().equals(gameCells[i-3][j+3].getStatus()) ){
                                    isWinner = 1;
                                    gameCells[i][j].setWinnerCell(winnerCell);
                                    gameCells[i-1][j+1].setWinnerCell(winnerCell);
                                    gameCells[i-2][j+2].setWinnerCell(winnerCell);
                                    gameCells[i-3][j+3].setWinnerCell(winnerCell);
                                    
                                    gameCells[i][j].setBackground(Color.yellow);
                                    gameCells[i-1][j+1].setBackground(Color.yellow);
                                    gameCells[i-2][j+2].setBackground(Color.yellow);
                                    gameCells[i-3][j+3].setBackground(Color.yellow);
                                }
                        }
                }
        }
}
if(isWinner !=1){
        if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
                if(gameCells[i][j].getStatus().equals(gameCells[i-1][j-1].getStatus()) ){       	//Top-Left     
                        if(gameCells[i][j].getStatus().equals(gameCells[i-2][j-2].getStatus()) ){		//Diagonal
                                if(gameCells[i][j].getStatus().equals(gameCells[i-3][j-3].getStatus()) ){
                                    isWinner = 1;
                                    gameCells[i][j].setWinnerCell(winnerCell);
                                    gameCells[i-1][j-1].setWinnerCell(winnerCell);
                                    gameCells[i-2][j-2].setWinnerCell(winnerCell);
                                    gameCells[i-3][j-3].setWinnerCell(winnerCell);
                                    
                                    gameCells[i][j].setBackground(Color.yellow);
                                    gameCells[i-1][j-1].setBackground(Color.yellow);
                                    gameCells[i-2][j-2].setBackground(Color.yellow);
                                    gameCells[i-3][j-3].setBackground(Color.yellow);
                                }
                        }
                }
        }
}
if(isWinner !=1){
        if(i<maxHeight - OFFSET && j<maxWidth - OFFSET){ //Preventing overflow
                if(gameCells[i][j].getStatus().equals(gameCells[i+1][j+1].getStatus()) ){       	//Bottom-Right      
                        if(gameCells[i][j].getStatus().equals(gameCells[i+2][j+2].getStatus()) ){		//Diagonal
                                if(gameCells[i][j].getStatus().equals(gameCells[i+3][j+3].getStatus()) ){
                                    isWinner = 1;
                                    gameCells[i][j].setWinnerCell(winnerCell);
                                    gameCells[i+1][j+1].setWinnerCell(winnerCell);
                                    gameCells[i+2][j+2].setWinnerCell(winnerCell);
                                    gameCells[i+3][j+3].setWinnerCell(winnerCell);
                                    
                                    gameCells[i][j].setBackground(Color.yellow);
                                    gameCells[i+1][j+1].setBackground(Color.yellow);
                                    gameCells[i+2][j+2].setBackground(Color.yellow);
                                    gameCells[i+3][j+3].setBackground(Color.yellow);
                                }
                            }
                    }
            }
    }
    if(isWinner !=1){
            if(i<maxHeight - OFFSET && j>OFFSET-1){ //Preventing overflow
                    if(gameCells[i][j].getStatus().equals(gameCells[i+1][j-1].getStatus()) ){       	//Bottom-Left     
                            if(gameCells[i][j].getStatus().equals(gameCells[i+2][j-2].getStatus()) ){		//Diagonal
                                    if(gameCells[i][j].getStatus().equals(gameCells[i+3][j-3].getStatus()) ){
                                        isWinner = 1;
                                        gameCells[i][j].setWinnerCell(winnerCell);
                                        gameCells[i+1][j-1].setWinnerCell(winnerCell);
                                        gameCells[i+2][j-2].setWinnerCell(winnerCell);
                                        gameCells[i+3][j-3].setWinnerCell(winnerCell);
                                        
                                        gameCells[i][j].setBackground(Color.yellow);
                                        gameCells[i+1][j-1].setBackground(Color.yellow);
                                        gameCells[i+2][j-2].setBackground(Color.yellow);
                                        gameCells[i+3][j-3].setBackground(Color.yellow);
                                    }
                                }
                            }
                        }
                    }
                }
            }
	}
	return isWinner;
    }
    
    /**
     * Makes a play for a player on given column if it's legal.
     * @param move Players choice of column. 
     */
    public void play(int move){
	String player;
	if(whosTurn == 1)
            player = "User1";
	else
            player = "User2";
	if(checkIllegalMove(move)){
            makeMove(player, move);
	}
	else
            System.out.println("Illegal Move");
    }
    
    /**
     *Calculates a play for AI, checks for game winners, 
     */
    public void play(){
        int aiMove = 0;
	int isMadeMove = 0; //0 If bot haven't made a move yet.
	int OFFSET = 3; //Offset for checking board Vertical/Horizontal

	int moveI = -1;		//Coordinates of move
	int moveJ = -1;		//If these stay as -1 there's no lose threat in the game
	//AI Checks if there's a winning move
        for(int i=0; i<maxHeight; ++i){   //i stands for rows
            for(int j=0; j<maxWidth; ++j){ //j stands for columns
                if(gameCells[i][j].getStatus().equals("Computer")){ //Checks if there's his token	
                    if(j<maxWidth-OFFSET){ //Preventing overflow
                        if(gameCells[i][j].getStatus().equals(gameCells[i][j+1].getStatus())){       	//Checking rightwards       
                            if(gameCells[i][j].getStatus().equals(gameCells[i][j+2].getStatus())){		//horizontal
                                if(gameCells[i][j+3].getStatus().equals("Empty")){
                                    if(i < maxHeight -1){
                                        if(gameCells[i+1][j+3].getStatus().equals("Empty")){
                                            moveI = i;
                                            moveJ = j+3;
                                        }
                                    }
                                    else if( i == maxHeight -1){
                                        moveI = i;
                                        moveJ = j+3;
                                    }
                                }
                            }
                        }
                    }
                if(j>OFFSET-1){ //Preventing overflow
                    if(gameCells[i][j].getStatus().equals(gameCells[i][j-1].getStatus())){   //Checking leftwards 
                        if(gameCells[i][j].getStatus().equals(gameCells[i][j-2].getStatus())){	//horizontal
                            if(gameCells[i][j-3].getStatus().equals("Empty")){
                                if(i < maxHeight -1){
                                    if(!gameCells[i+1][j-3].getStatus().equals("Empty")){
                                        moveI = i;
                                        moveJ = j-3;
                                    }
                                }
                                else if( i == maxHeight -1){
                                    moveI = i;
                                    moveJ = j-3;
                                }
                            }
                        }
                    }
                }
                if(i<maxHeight-OFFSET){ //Preventing overflow
                    if(gameCells[i][j].getStatus().equals(gameCells[i+1][j].getStatus())){   //Checking downwards       
                        if(gameCells[i][j].getStatus().equals(gameCells[i+2][j].getStatus())){ //vertical
                            if(gameCells[i+3][j].getStatus().equals("Empty")){
                                if(i < maxHeight -1){
                                    if(!gameCells[i+3+1][j].getStatus().equals("Empty")){
                                        moveI = i+3;
                                        moveJ = j;
                                    }
                                }
                                else if( i == maxHeight -1){
                                    moveI = i+3;
                                    moveJ = j;
                                }
                            }
                        }
                    }
                }
                if(i>OFFSET-1){ //Preventing overflow
                    if(gameCells[i][j].getStatus().equals(gameCells[i-1][j].getStatus())){       	//Checking upwards       
                        if(gameCells[i][j].getStatus().equals(gameCells[i-2][j].getStatus())){		//vertical
                            if(gameCells[i-3][j].getStatus().equals("Empty")){
                                if(i < maxHeight -1){
                                    if(!gameCells[i-3+1][j].getStatus().equals("Empty")){
                                    moveI = i-3;
                                    moveJ = j;
                                    }
                                }
                                else if( i == maxHeight -1){
                                    moveI = i-3;
                                    moveJ = j;
                                }
                            }
                        }
                    }
                }
                if(i>OFFSET-1 && j<maxWidth - OFFSET){ //Preventing overflow
                    if(gameCells[i][j].getStatus().equals(gameCells[i-1][j+1].getStatus())){       	//Top-Right      
                        if(gameCells[i][j].getStatus().equals(gameCells[i-2][j+2].getStatus())){ //Diagonal
                            if(gameCells[i-3][j+3].getStatus().equals("Empty")){
                                    if(i < maxHeight -1){
                                        if(!gameCells[-3+1][j+3].getStatus().equals("Empty")){
                                            moveI = i-3;
                                            moveJ = j+3;
                                        }
                                    }
                                    else if( i == maxHeight -1){
                                        moveI = i-3;
                                        moveJ = j+3;
                                    }
                                }
                            }
                        }
                    }
                    if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
                        if(gameCells[i][j].getStatus().equals(gameCells[i-1][j-1].getStatus())){       	//Top-Left     
                            if(gameCells[i][j].getStatus().equals(gameCells[i-2][j-2].getStatus())){		//Diagonal
                                if(gameCells[i-3][j-3].getStatus().equals("Empty")){
                                    if(i < maxHeight -1){
                                        if(!gameCells[i-3+1][j-3].getStatus().equals("Empty")){
                                            moveI = i-3;
                                            moveJ = j-3;
                                        }
                                    }
                                    else if( i == maxHeight -1){
                                        moveI = i-3;
                                        moveJ = j-3;
                                    }
                                }
                            }
                        }
                    }
                    if(i<maxHeight - OFFSET && j<maxWidth - OFFSET){ //Preventing overflow
                        if(gameCells[i][j].getStatus().equals(gameCells[i+1][j+1].getStatus())){       	//Bottom-Right      
                            if(gameCells[i][j].getStatus().equals(gameCells[i+2][j+2].getStatus())){		//Diagonal
                                if(gameCells[i+3][j+3].getStatus().equals("Empty")){
                                    if(i < maxHeight -1){
                                        if(!gameCells[i+3+1][j+3].getStatus().equals("Empty")){
                                            moveI = i+3;
                                            moveJ = j+3;
                                        }
                                    }
                                    else if( i == maxHeight -1){
                                        moveI = i+3;
                                        moveJ = j+3;
                                    }
                                }
                            }
                        }
                    }
                    if(i<maxHeight - OFFSET && j>OFFSET-1){ //Preventing overflow
                            if(gameCells[i][j].getStatus().equals(gameCells[i+1][j-1].getStatus())){    //Bottom-Left     
                                    if(gameCells[i][j].getStatus().equals(gameCells[i+2][j-2].getStatus())){ //Diagonal
                                            if(gameCells[i+3][j-3].getStatus().equals("Empty")){
                                                if(i < maxHeight -1){
                                                    if(!gameCells[i+3+1][j-3].getStatus().equals("Empty")){
                                                        moveI = i+3;
                                                        moveJ = j-3;
                                                    }
                                                }
                                                else if( i == maxHeight -1){
                                                    moveI = i+3;
                                                    moveJ = j-3;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }	
	if(moveI != -1 && moveJ != -1){ //If there's a losing threat
                aiMove = moveJ;
		makeMove("Computer", moveJ);
		isMadeMove = 1;
	}
	else if( isMadeMove == 0){ //If there's no losing threat, AI makes it's own move 
	

	//Checks if the enemy has a winning move
        for(int i=0; i<maxHeight; ++i){   //i stands for rows
            for(int j=0; j<maxWidth; ++j){ //j stands for columns
                if(gameCells[i][j].getStatus().equals("User1")){ //Checks if it's enemy token		
                    if(j<maxWidth-OFFSET){ //Preventing overflow
                        if(gameCells[i][j].getStatus().equals(gameCells[i][j+1].getStatus())){       	//Checking rightwards       
                            if(gameCells[i][j].getStatus().equals(gameCells[i][j+2].getStatus())){		//horizontal
                                if(gameCells[i][j+3].getStatus().equals("Empty")){
                                    if(i < maxHeight -1){
                                        if(!gameCells[i+1][j+3].getStatus().equals("Empty")){
                                            moveI = i;
                                            moveJ = j+3;
                                        }
                                    }
                                    else if( i == maxHeight -1){
                                        moveI = i;
                                        moveJ = j+3;
                                    }
                                }
                            }
                        }
                    }
                            if(j>OFFSET-1){ //Preventing overflow
                                if(gameCells[i][j].getStatus().equals(gameCells[i][j-1].getStatus())){       	//Checking leftwards       
                                    if(gameCells[i][j].getStatus().equals(gameCells[i][j-2].getStatus())){		//horizontal
                                        if(gameCells[i][j-3].getStatus().equals("Empty")){
                                            if(i < maxHeight -1){
                                                if(!gameCells[i+1][j-3].getStatus().equals("Empty")){
                                                    moveI = i;
                                                    moveJ = j-3;
                                                }
                                            }
                                            else if( i == maxHeight -1){
                                                moveI = i;
                                                moveJ = j-3;
                                            }
                                        }
                                    }
                                }
                            }
                            if(i<maxHeight-OFFSET){ //Preventing overflow
                                if(gameCells[i][j].getStatus().equals(gameCells[i+1][j].getStatus())){       	//Checking downwards       
                                    if(gameCells[i][j].getStatus().equals(gameCells[i+2][j].getStatus())){		//vertical
                                        if(gameCells[i+3][j].getStatus().equals("Empty")){
                                            if(i < maxHeight -1){
                                                if(!gameCells[i+3+1][j].getStatus().equals("Empty")){
                                                    moveI = i+3;
                                                    moveJ = j;
                                                }
                                            }
                                            else if( i == maxHeight -1){
                                                moveI = i+3;
                                                moveJ = j;
                                            }
                                        }
                                    }
                                }
                            }
                            if(i>OFFSET-1){ //Preventing overflow
                                if(gameCells[i][j].getStatus().equals(gameCells[i-1][j].getStatus())){       	//Checking upwards       
                                    if(gameCells[i][j].getStatus().equals(gameCells[i-2][j].getStatus())){		//vertical
                                        if(gameCells[i-3][j].getStatus().equals("Empty")){
                                            if(i < maxHeight -1){
                                                if(!gameCells[i-3+1][j].getStatus().equals("Empty")){
                                                    moveI = i-3;
                                                    moveJ = j;
                                                }
                                            }
                                            else if( i == maxHeight -1){
                                                moveI = i-3;
                                                moveJ = j;
                                            }
                                        }
                                    }
                                }
                            }
                            if(i>OFFSET-1 && j<maxWidth - OFFSET){ //Preventing overflow
                                if(gameCells[i][j].getStatus().equals(gameCells[i-1][j+1].getStatus())){       	//Top-Right      
                                    if(gameCells[i][j].getStatus().equals(gameCells[i-2][j+2].getStatus())){		//Diagonal
                                        if(gameCells[i-3][j+3].getStatus().equals("Empty")){
                                            if(i < maxHeight -1){
                                                if(!gameCells[i-3+1][j+3].getStatus().equals("Empty")){
                                                    moveI = i-3;
                                                    moveJ = j+3;
                                                }
                                            }
                                            else if( i == maxHeight -1){
                                                moveI = i-3;
                                                moveJ = j+3;
                                            }
                                        }
                                    }
                                }
                            }
                            if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
                                if(gameCells[i][j].getStatus().equals(gameCells[i-1][j-1].getStatus())){ //Top-Left     
                                    if(gameCells[i][j].getStatus().equals(gameCells[i-2][j-2].getStatus())){	 //Diagonal
                                        if(gameCells[i-3][j-3].getStatus().equals("Empty")){
                                            if(i < maxHeight -1){
                                                if(!gameCells[i-3][j-3].getStatus().equals("Empty")){
                                                    moveI = i-3;
                                                    moveJ = j-3;
                                                }
                                            }
                                            else if( i == maxHeight -1){
                                                moveI = i-3;
                                                moveJ = j-3;
                                            }
                                        }
                                    }
                                }
                            }
                            if(i<maxHeight - OFFSET && j<maxWidth - OFFSET){ //Preventing overflow
                                if(gameCells[i][j].getStatus().equals(gameCells[i+1][j+1].getStatus())){       	//Bottom-Right      
                                    if(gameCells[i][j].getStatus().equals(gameCells[i+2][j+2].getStatus())){		//Diagonal
                                        if(gameCells[i+3][j+3].getStatus().equals("Empty")){
                                            if(i < maxHeight -1){
                                                if(!gameCells[i+3+1][j+3].getStatus().equals("Empty")){
                                                    moveI = i+3;
                                                    moveJ = j+3;
                                                }
                                            }
                                            else if( i == maxHeight -1){
                                                moveI = i+3;
                                                moveJ = j+3;
                                            }
                                        }
                                    }
                                }
                            }
                            if(i<maxHeight - OFFSET && j>OFFSET-1){ //Preventing overflow
                                if(gameCells[i][j].getStatus().equals(gameCells[i+1][j-1].getStatus())){       	//Bottom-Left     
                                    if(gameCells[i][j].getStatus().equals(gameCells[i+2][j-2].getStatus())){		//Diagonal
                                        if(gameCells[i+2][j-3].getStatus().equals("Empty")){
                                            if(i < maxHeight -1){
                                                if(!gameCells[i+3+1][j-3].getStatus().equals("Empty")){
                                                    moveI = i+3;
                                                    moveJ = j-3;
                                                }
                                            }
                                            else if( i == maxHeight -1){
                                                moveI = i+3;
                                                moveJ = j-3;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
	
	if(moveI != -1 && moveJ != -1 && isMadeMove == 0){
		if( checkIllegalMove(moveJ) ){
			makeMove("Computer", moveJ);
                        aiMove = moveJ;
		}
	}
	else if( isMadeMove == 0){ //There's no winning or blocking move so Computer makes a random move.
		int randomColumn;
		int isIllegal;
		do{
			Random rndNum = new Random();
                        System.out.println("random number");
                        randomColumn = rndNum.nextInt(newSize);
                        System.out.println(randomColumn);
                        if(checkIllegalMove(randomColumn))
                            isIllegal = 1;
                        else
                            isIllegal = 0;
		}
		while(isIllegal == -1);
		makeMove("Computer", randomColumn);
                aiMove = randomColumn;
	}
    }
   
    //Initializes the board
    private void initializeBoard(){
        MouseHandler mouseH = new MouseHandler();
        setLayout(new GridLayout(newSize, newSize, -1, -1));
        resizeBoard(newSize);
        for(int i=0; i<newSize; ++i){
            for(int j=0; j<newSize; ++j){
                gameCells[i][j] = new Cell();
                gameCells[i][j].setVisible(true);
                gameCells[i][j].addMouseListener(mouseH);
                gameCells[i][j].setBorder(BorderFactory.createLineBorder(Color.black));
                add(gameCells[i][j]);
            }   
        }
        setVisible(true);
    }
    
    //Re-Initializes the board.
    private void newBoardInit(){ //Re-Initializes the board
        try{
            textOutp = JOptionPane.showInputDialog("Please enter a new board size");
            newSize = Integer.parseInt(textOutp);
        }
        catch(Exception exp){
            System.out.println(exp.toString());
            System.exit(-1);
        }
        if(newSize < 4) //Size cannot be less than 4
            System.exit(-1);

        //Removing old panels from the frame
        for(int i=0; i<maxHeight; ++i){
            for(int j=0; j<maxWidth; ++j){
                remove(gameCells[i][j]);
            }
        }
        //Reinitializing board
        whosTurn = 1;
        isGameOver = 0;
        initializeBoard();
    }
    
    //Action Handler Class
    private class ActionHandler implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent event){
            if(event.getSource().equals(singleP) ){ //Singleplayer button handle
                isAI = 0;
                //Removing game mode buttons after player's choice.
                remove(singleP);
                remove(multiP);
                try{
                    //Getting size input from player.
                    textOutp = JOptionPane.showInputDialog("Please enter board size");
                    newSize = Integer.parseInt(textOutp);
                }
                catch(Exception e){//Exception handling
                    System.out.println(e.toString());
                    System.exit(-1);
                }
                if(newSize < 4){ //Size check.
                    System.out.println("Size cannot be less than 4");
                    System.exit(-1);
                }    
                initializeBoard(); //Initializing board.
            }
            if(event.getSource().equals(multiP)){ //Multiplayer button handle
                isAI = 1;
                //Removing game mode buttons after player's choice.
                remove(singleP);
                remove(multiP);
                try{
                    //Getting size input from player.
                    textOutp = JOptionPane.showInputDialog("Please enter board size");
                    newSize = Integer.parseInt(textOutp);
                }
                catch(Exception e){//Exception handling
                    System.out.println(e.toString());
                    System.exit(-1);
                }
                if(newSize < 4){ //Size check.
                    System.out.println("Size cannot be less than 4");
                    System.exit(-1);
                }
                initializeBoard();//Initializing board.
            }
        }
    }
    
    
    //Mouse Handler Class
    private class MouseHandler implements MouseListener{
        @Override
        public void mouseExited(MouseEvent e){}//Left blank on purpose
        @Override
        public void mouseEntered(MouseEvent e){}//Left blank on purpose
        @Override
        public void mouseReleased(MouseEvent e){}//Left blank on purpose
        @Override
        public void mouseClicked(MouseEvent e){}//Left blank on purpose
        @Override
        public void mousePressed(MouseEvent e){
            //Calculating column by dividing board size(without borders) by width of panels divided by panel size.
            int column = (int) Math.round(e.getComponent().getX()/ (getContentPane().getSize().getWidth() / newSize));
            
            isGameOver = checkWinner();//Checking game winner initially.
            if(isGameOver == -1){//Game is not over
                if(whosTurn == 1){//Player 1's Turn
                    play(column);                    
                    isGameOver = checkWinner(); //Checking for a winner after the play
                    if(isGameOver == 1)
                        JOptionPane.showMessageDialog(null, "Player 1 Won!");
                    whosTurn = 2;
                    if(isAI == 1){ //AI makes it's turn after player1's turn
                        play(); 
                        isGameOver = checkWinner(); //Checking for a winner after the play
                        if(isGameOver == 1)
                            JOptionPane.showMessageDialog(null, "AI Won!");
                        whosTurn = 1;
                    }
                }
                else if(whosTurn == 2 && isGameOver == -1){//Player 2's Turn
                    play(column);                    
                    isGameOver = checkWinner();//Checking for a winner after the play
                    if(isGameOver == 1)
                        JOptionPane.showMessageDialog(null, "Player 2 Won!");
                    whosTurn = 1;
                }
            }
            if(isGameOver == 2){ //Game is draw
                JOptionPane.showMessageDialog(null, "Game is Draw");
                newBoardInit(); //Re-initializing board for the next game
            }
            if(isGameOver == 1){ //Game is over.
                JOptionPane.showMessageDialog(null, "Game is over, enter new size to play again");
                newBoardInit(); //Re-initializing board for the next game
            }
        }
    }
}