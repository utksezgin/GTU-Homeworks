/**
 * An abstract class for room which holds room number
 */
public abstract class AbstractRoom implements Room {
    /**
     * Number of the room
     */
    protected int roomNo;

    /**
     * No-parameter constructor, sets roomNo 0 by default.
     */
    AbstractRoom(){
        roomNo = 0; //Default
    }

    /**
     * Getter method for room number.
     * @return Returns room number.
     */
    @Override
    public abstract int getRoomNo();

}