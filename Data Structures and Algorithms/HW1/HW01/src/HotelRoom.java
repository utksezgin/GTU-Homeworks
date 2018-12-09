/**
 * HotelRoom class extends AbstractRooom class and contains informations of hotel rooms.
 */
public class HotelRoom extends AbstractRoom {
    /**
     * Whether the room is available or not.
     */
    private boolean isEmpty;
    /**
     * Whether the room is booked or not.
     */
    private boolean isBooked;
    /**
     * Whether someone is checked-in or not.
     */
    private boolean isCheckedIn;
    /**
     * ID of the user who booked it or checked-in. 0 means room is empty.
     */
    private int ownerID; //0 If the room is empty.

    /**
     * No parameter constructor that generates an empty room with room number being 0.
     */
    HotelRoom(){ //Empty room. You can add rooms via editing roomSave.csv file.
        super();
        this.isEmpty = true;
        this.isBooked = false;
        this.isCheckedIn = false;
        this.ownerID = 0;
    }

    /**
     * @return Returns room number.
     */
    @Override
    public int getRoomNo(){
        return roomNo;
    }

    /**
     * @return Returns true if the room is booked.
     */
    public boolean getIsBooked(){
        return isBooked;
    }

    /**
     * @return Returns true if a guest is checked-in.
     */
    public boolean getIsCheckedIn(){
        return isCheckedIn;
    }

    /**
     * @return Returns true if the room is empty.
     */
    public boolean getIsEmpty(){
        return isEmpty;
    }

    /**
     * @return Returns the ID Number of guest who booked or checked in to the room.
     */
    public int getOwnerID(){
        return ownerID;
    }

    /**
     * @param roomNo New room number.
     */
    public void setRoomNo(int roomNo){
        this.roomNo = roomNo;
    }

    /**
     * @param isEmpty New isEmpty value.
     */
    public void setIsEmpty(boolean isEmpty){
        this.isEmpty = isEmpty;
    }

    /**
     * @param isBooked New isBooked value.
     */
    public void setIsBooked(boolean isBooked){
        this.isBooked = isBooked;
    }

    /**
     * @param isCheckedIn New isCheckedIn value.
     */
    public void setIsCheckedIn(boolean isCheckedIn){
        this.isCheckedIn = isCheckedIn;
    }

    /**
     * @param ownerID new ownerID value.
     */
    public void setOwnerID(int ownerID){
        this.ownerID = ownerID;
    }
}