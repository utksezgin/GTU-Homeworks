package hw08;

import javax.swing.JPanel;

/**
 * public class Cell
 * extends JPanel
 * An extended version of JPanel to hold information of game cells <br>
 * Cell class holds Status information, height and width.
 * <br> <br>
 * @author Azmi Utku Sezgin 131044048
 */
public class Cell extends JPanel{
    
    private int winnerCell; //1 if one of the 4 cells otherwise 0
    private int width;	 //A,B,C,....,Z ** 0-26
    private int height;	    //0,1,2,3...
    private String status;  //Empty, User1, User2, Computer
    
    
    Cell(){ //Default constructor Sets Column to A, row to 0 and status to empty.
	width = 0;
	height = 0;
	winnerCell =0;
	status = "Empty";
    } 
    Cell(int w, int h){ // Sets col to column, row to row and status to empty.
	if(w>= 0 && w <26 && h<0 && h!=w)
		width = w;
	else{
            throw new java.lang.IllegalArgumentException("Illegal height or width");
        }
        
        height = h;
        winnerCell =0;
    } 

    /**
     * Getter for height information of Cell
     * @return Returns height position of cell
     */
    public int getH() { return height; };

    /**
     * Getter for width information of Cell
     * @return Returns width position of cell
     */
    public int getW() { return width; };

    /**
     * Getter for status information of Cell
     * @return Returns status position of cell
     */
    public String getStatus() { return status; };

    /**
     * Changes the winnerCell variable
     * @param w new value of winnerCell variable
     */
    public void setWinnerCell(int w) { winnerCell = w; };
    
    /**
     * Changes width of the cell
     * @param w new width for the cell
     */
    public void setWidth(int w){
	if(w>= 0 && w <26)
		width = w;
	else{
            throw new java.lang.IllegalArgumentException("Illegal width");
	}
}
	
    /**
     * Changes height of the cell
     * @param w new height for the cell
     */
    public void setHeight(int w){
            if(w>=0)
                    height = w;	
    }

    /**
     * Changes status of the cell
     * @param x new status for the cell
     */
    public void setStatus(String x){
            if(x.equals("Empty") || x.equals("User1") || x.equals("User2") || x.equals("Computer"))
                    status = x;
            else{
                throw new java.lang.IllegalArgumentException("Illegal Status");
            }
    }
}
