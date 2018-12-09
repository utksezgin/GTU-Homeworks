import java.io.*;
import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.UnknownFormatConversionException;

/**
 *This is a basic hotel management system that allows you to log-in, book rooms, cancel books as guests
 * and book rooms, cancel books, check-ins and checkouts as receptionist. Store information of guests, receptionists
 * and room informations in a csv file.
 */
public class ManagementSystem {

    /**
     * An array list of Rooms for storing the room informations.
     */
    private ArrayList<HotelRoom> hotelRooms;
    /**
     * An array list of User for storing the receptionist informations.
     */
    private ArrayList<User> recepLoginInfo; //Receptionist login database
    /**
     * An array list of User for storing the regular user informations.
     */
    private ArrayList<User> guestLoginInfo; //Guest login database

    /**
     * 2 Parameter constructor that takes 2 csv file names that holds room and user informations.
     * @param roomFile Name of csv file that holds room informations.
     * @param userFile Name of csv file that holds User database informations.
     */
    ManagementSystem(String roomFile, String userFile){
        hotelRooms = new ArrayList<HotelRoom>();
        parseRoomList(roomFile);
        recepLoginInfo = new ArrayList<User>();
        guestLoginInfo = new ArrayList<User>();
        parseUserList(userFile);
    }

    /**
     * Logs-in user to the system.
     * @param user User that wants to login.
     */
    private void login(User user) {
        if (searchAndMatchUser(user)) {
            if(user.getGuestOrRecep() == 'r' || user.getGuestOrRecep() == 'R' ){
                recepLoginInfo.get(user.getLoginInfoNo()).setIsLoggedIn("Online");
                user.setIsLoggedIn("Online");
            }
            if(user.getGuestOrRecep() == 'g' || user.getGuestOrRecep() == 'G'){
                guestLoginInfo.get(user.getLoginInfoNo()).setIsLoggedIn("Online");
                user.setIsLoggedIn("Online");
            }

            System.out.println("User successfully logged in.");
        }
        else
            System.out.println("Couldn't find the user.");
    }

    /**
     * This method allows you to cancel your book.
     * @param user Guest who's gonna cancel the book.
     * @param roomNo HotelRoom number.
     * @return Returns true if Canceling was successful.
     * @throws InvalidParameterException Throws exception if guestID doesn't match or roomNo is invalid.
     */
    private boolean guestCancelBook(User user, int roomNo) throws InvalidParameterException{
        int roomN = roomNo -1; //HotelRoom Number's equivalent in array
        boolean isRoomCanceled = false;
        if(roomN < 0 || roomN >= hotelRooms.size()){
            System.out.println("Invalid room number.");
            throw new InvalidParameterException("Invalid room number");
        }
        else if(guestLoginInfo.get(user.getLoginInfoNo()).getIsLoggedIn().equals("Online")) { //Is user logged-in.
            if (hotelRooms.get(roomN).getIsBooked() && hotelRooms.get(roomN).getOwnerID() == user.getLoginInfoNo()) {
                hotelRooms.get(roomN).setIsEmpty(true);
                hotelRooms.get(roomN).setIsBooked(false);
                hotelRooms.get(roomN).setOwnerID(0);
                isRoomCanceled = true;
                System.out.println("Book successfully canceled!");
                return isRoomCanceled;
            }
            else
                System.out.println("Canceling the book failed. Please check your information.");
        }
        else{
            System.out.println("You have to log-in to book a room");
        }
        return isRoomCanceled;
    }

    /**
     * This method allows receptionist to cancel the book.
     * @param user  Guest who's gonna cancel the book.
     * @param guestID Guest's ID who booked the room.
     * @param roomNo HotelRoom number.
     * @return Returns true if Canceling was successful.
     * @throws InvalidParameterException Throws exception if guestID doesn't match or roomNo is invalid.
     */
    private boolean recepCancelBook(User user, int guestID, int roomNo) throws InvalidParameterException{
        int roomN = roomNo -1; //HotelRoom Number's equivalent in array
        boolean isRoomCanceled = false;
        if(roomN < 0 || roomN >= hotelRooms.size()){
            throw new InvalidParameterException("Invalid room number");
        }
        else if(recepLoginInfo.get(user.getLoginInfoNo()).getIsLoggedIn().equals("Online")) { //Is user logged-in.
            if (hotelRooms.get(roomN).getIsBooked() && hotelRooms.get(roomN).getOwnerID() == guestID) {
                hotelRooms.get(roomN).setIsEmpty(true);
                hotelRooms.get(roomN).setIsBooked(false);
                hotelRooms.get(roomN).setOwnerID(0);
                isRoomCanceled = true;
                System.out.println("Book successfully canceled!");
                return isRoomCanceled;
            }
            else
                System.out.println("Canceling the book failed. Please check your information.");
        }
        else{
            System.out.println("You don't have authorization to cancel the book.");
        }
        return isRoomCanceled;
    }

    /**
     * This method allows guests to book rooms.
     * @param user Guest who's gonna cancel the book.
     * @param roomNo HotelRoom number.
     * @return Returns true if Canceling was successful.
     * @throws InvalidParameterException Throws exception if match or roomNo is invalid.
     */
    private boolean guestBookRoom(User user, int roomNo) throws InvalidParameterException{
        int roomN = roomNo -1; //HotelRoom Number's equivalent in array
        boolean isRoomBooked = false;
        if(roomN < 0 || roomN >= hotelRooms.size()){
            System.out.println("Invalid room number.");
            throw new InvalidParameterException("Invalid room number");
        }
        else if(guestLoginInfo.get(user.getLoginInfoNo()).getIsLoggedIn().equals("Online")) { //Is user logged-in.
            if( !hotelRooms.get(roomN).getIsBooked() && hotelRooms.get(roomN).getIsEmpty()){
                hotelRooms.get(roomN).setIsEmpty(false);
                hotelRooms.get(roomN).setIsBooked(true);
                hotelRooms.get(roomN).setOwnerID(user.getLoginInfoNo());
                isRoomBooked = true;
                System.out.println("The room successfully booked");
                return isRoomBooked;
            }
            else
                System.out.println("Booking the room failed. Please check your information.");
        }
        else{
            System.out.println("You have to log-in to book a room");
        }
        return isRoomBooked;
    }

    /**
     * This method allows receptionist to book rooms.
     * @param user Receptionist who books the room.
     * @param guestID Guest's ID who wants to book the room.
     * @param roomNo HotelRoom number.
     * @return Returns true if booking was successful.
     * @throws InvalidParameterException Throws exception if guestID doesn't match or roomNo is invalid.
     */
    private boolean recepBookRoom(User user, int guestID, int roomNo) throws InvalidParameterException{
        int roomN = roomNo -1; //HotelRoom Number's equivalent in array
        boolean isRoomBooked = false;
        if(roomN < 0 || roomN >= hotelRooms.size()){
            System.out.println("Invalid room number.");
            throw new InvalidParameterException("Invalid room number");
        }
        else if(recepLoginInfo.get(user.getLoginInfoNo()).getIsLoggedIn().equals("Online")) { //Is user logged-in.
            if( !hotelRooms.get(roomN).getIsBooked() && hotelRooms.get(roomN).getIsEmpty()){
                hotelRooms.get(roomN).setIsEmpty(false);
                hotelRooms.get(roomN).setIsBooked(true);
                hotelRooms.get(roomN).setOwnerID(guestID);
                isRoomBooked = true;
                System.out.println("The room successfully booked");
                return isRoomBooked;
            }
            else
                System.out.println("Booking the room failed. Please check your information.");
        }
        else{
            System.out.println("You don't have authorization to book a room");
        }
        return isRoomBooked;
    }

    /**
     * This method allows receptionists to check-in guests.
     * @param user Receptionist who checks-in the guest.
     * @param guestID Guest's ID who wants to check-in.
     * @param roomNo HotelRoom number.
     * @return Return true if check-in is successful.
     * @throws InvalidParameterException Throws exception if guestID doesn't match or roomNo is invalid.
     */
    private boolean recepCheckIn(User user, int guestID, int roomNo) throws InvalidParameterException{
        int roomN = roomNo -1; //HotelRoom Number's equivalent in array
        boolean isCheckedIn = false;
        if(roomN < 0 || roomN >= hotelRooms.size()){
            System.out.println("Invalid room number.");
            throw new InvalidParameterException("Invalid room number");
        }
        else if(recepLoginInfo.get(user.getLoginInfoNo()).getIsLoggedIn().equals("Online")) { //Is user logged-in.
            //If the room isn't booked and empty
            if( hotelRooms.get(roomN).getIsEmpty() && !hotelRooms.get(roomN).getIsBooked() && !hotelRooms.get(roomN).getIsCheckedIn()){
                hotelRooms.get(roomN).setIsEmpty(true);
                hotelRooms.get(roomN).setIsCheckedIn(true);
                hotelRooms.get(roomN).setOwnerID(guestID);
                isCheckedIn = true;
                System.out.println("User Checked-in Successfully!");
                return isCheckedIn;
            }
            //If the room is booked
            else if(!hotelRooms.get(roomN).getIsEmpty() && hotelRooms.get(roomN).getIsBooked() && hotelRooms.get(roomN).getOwnerID() == guestID &&
                    !hotelRooms.get(roomN).getIsCheckedIn()) {
                hotelRooms.get(roomN).setIsEmpty(false);
                hotelRooms.get(roomN).setIsCheckedIn(true);
                hotelRooms.get(roomN).setIsBooked(false);
                hotelRooms.get(roomN).setOwnerID(guestID);
                isCheckedIn = true;
                System.out.println("User Checked-in Successfully!");
                return isCheckedIn;
            }
            else
                System.out.println("Check-in operation failed. Please check your information.");
        }
        else{
            System.out.println("You don't have authorization to use Check-out");
        }
        return isCheckedIn;
    }

    /**
     * This method allows receptionists to check-out guests.
     * @param user Receptionist who checks-out the guest.
     * @param guestID Guest's ID who wants to check-out.
     * @param roomNo HotelRoom number.
     * @return Return true if check-out is successful.
     * @throws InvalidParameterException Throws exception if guestID doesn't match or roomNo is invalid.
     */
    private boolean recepCheckOut(User user, int guestID, int roomNo) throws InvalidParameterException{
        int roomN = roomNo -1; //HotelRoom Number's equivalent in array
        boolean isCheckedOut = false;
        if(roomN < 0 || roomN >= hotelRooms.size()){
            System.out.println("Invalid room number.");
            throw new InvalidParameterException("Invalid room number");
        }
        else if(recepLoginInfo.get(user.getLoginInfoNo()).getIsLoggedIn().equals("Online")) { //Is user logged-in.
            if( hotelRooms.get(roomN).getOwnerID() == guestID && hotelRooms.get(roomN).getIsCheckedIn()){
                hotelRooms.get(roomN).setIsEmpty(true);
                hotelRooms.get(roomN).setIsCheckedIn(false);
                isCheckedOut = true;
                System.out.println("User Checked-out Successfully!");
                return isCheckedOut;
            }
            else
                System.out.println("Check-out operation failed. Please check your information.");
        }
        else{
            System.out.println("You don't have authorization to use Check-out");
        }
        return isCheckedOut;
    }

    /**
     * This method searches for user inside their database and matches their log-in number if it's found.
     * @param user User who wants to log-in
     * @return returns true if user exists in the database.
     */
    private boolean searchAndMatchUser(User user){
        boolean isSuccessful = false;
        for(int i=0; i<recepLoginInfo.size(); ++i){
            if(user.getUsername().equals(recepLoginInfo.get(i).getUsername()) && user.getPassword().equals(recepLoginInfo.get(i).getPassword())){
                user.setLoginInfoNo(i);
                isSuccessful = true;
            }
        }
        for(int i=0; i<guestLoginInfo.size(); ++i){
            if(user.getUsername().equals(guestLoginInfo.get(i).getUsername()) && user.getPassword().equals(guestLoginInfo.get(i).getPassword())){
                user.setLoginInfoNo(i);
                isSuccessful = true;
            }
        }
        return isSuccessful;
    }

    /**
     * Parses the given csv file that holds room informations and stores them in 'hotelRooms'.
     * @param roomFile csv File that holds the room information.
     */
    private void parseRoomList(String roomFile){
        String lineBuffer;
        boolean boolBuffer = true;
        String stringToInt = "";
        int intBuffer = 0;
        int index = 0;
        int j=0;
        //Parsing roomList.csv
        try {
            HotelRoom newHotelRoom;
            File roomsFile = new File(roomFile);
            Scanner roomScan = new Scanner(roomsFile);
            while (roomScan.hasNext()) {
                newHotelRoom = new HotelRoom();
                lineBuffer = roomScan.next();
                int i = 0;
                while(i<lineBuffer.length() && lineBuffer.charAt(i) != '\n' && lineBuffer.charAt(i)!='\r'){
                    //roomNo
                    while(lineBuffer.charAt(i)!=','){
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                        ++j;
                    }
                    if(Integer.parseInt(stringToInt) <0){
                        throw new InvalidParameterException("RoomNo cannot be a negative number");
                    }
                    newHotelRoom.setRoomNo(Integer.parseInt(stringToInt));
                    j=0;
                    stringToInt = "";
                    ++i;//Skipping coma

                    //IsEmpty
                    if(lineBuffer.charAt(i) == '0')
                        newHotelRoom.setIsEmpty(false);
                    else if(lineBuffer.charAt(i) == '1')
                        newHotelRoom.setIsEmpty(true);
                    else
                        throw new UnknownFormatConversionException("Cannot convert " + lineBuffer.charAt(i) + " to boolean");
                    i += 2; //Skipping coma and value

                    //IsBooked
                    if(lineBuffer.charAt(i) == '0')
                        newHotelRoom.setIsBooked(false);
                    else if(lineBuffer.charAt(i) == '1')
                        newHotelRoom.setIsBooked(true);
                    else
                        throw new UnknownFormatConversionException("Cannot convert " + lineBuffer.charAt(i) + " to boolean");
                    i += 2; //Skipping coma and value

                    //IsCheckedIn
                    if(lineBuffer.charAt(i) == '0')
                        newHotelRoom.setIsCheckedIn(false);
                    else if(lineBuffer.charAt(i) == '1')
                        newHotelRoom.setIsCheckedIn(true);
                    else
                        throw new UnknownFormatConversionException("Cannot convert " + lineBuffer.charAt(i) + " to boolean");
                    i += 2; //Skipping coma and value

                    //ownerID
                    while(i<lineBuffer.length() && lineBuffer.charAt(i)!='\n' && lineBuffer.charAt(i)!='\r'){
                        stringToInt += lineBuffer.charAt(i);
                        ++j;
                        ++i;
                    }
                    if(Integer.parseInt(stringToInt) < 0){
                        throw new InvalidParameterException("ownerID cannot be a negative number");
                    }
                    newHotelRoom.setOwnerID(Integer.parseInt(stringToInt));
                    j=0;
                    stringToInt = "";
                }
                hotelRooms.add(newHotelRoom);
                i=0;
            }
        }
        catch (Exception e){
            e.printStackTrace();
            System.err.println(e.toString());
        }
    }

    /**
     * Parses the given csv file that holds Log-in informations and stores them in 'recepLoginInfo, guestLoginInfo'
     * @param userFile csv File that holds the user information.
     */
    private void parseUserList(String userFile){
        String lineBuffer;
        String stringToInt = "";
        String tempStr = "";
        int intBuffer = 0;
        int j = 0;
        try {
            User newUser;
            File usersFile = new File(userFile);
            Scanner roomScan = new Scanner(usersFile);
            while (roomScan.hasNext()) {
                newUser = new User("Empty", "Empty", "Empty", "Empty", 'g'); //Creating empty temp user
                lineBuffer = roomScan.nextLine();
                int i = 0;
                while(i<lineBuffer.length() && lineBuffer.charAt(i) != '\n' && lineBuffer.charAt(i)!='\r') {
                    while (lineBuffer.charAt(i) != ',') {
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                        ++j;
                    }
                    if(Integer.parseInt(stringToInt) < 1)
                        throw new InvalidParameterException("Login No cannot be a negative number");
                    newUser.setLoginInfoNo(Integer.parseInt(stringToInt));
                    stringToInt = "";
                    j = 0;
                    intBuffer = 0;
                    ++i;//Skipping coma

                    //Name
                    while (lineBuffer.charAt(i) != ',') {
                        tempStr += lineBuffer.charAt(i);
                        ++i;
                    }
                    newUser.setName(tempStr);
                    tempStr = ""; //Clearing temp
                    ++i;//Skipping coma

                    //Surname
                    while (lineBuffer.charAt(i) != ',') {
                        tempStr += lineBuffer.charAt(i);
                        ++i;
                    }
                    newUser.setSurname(tempStr);
                    tempStr = ""; //Clearing temp
                    ++i;//Skipping coma

                    //Username
                    while (lineBuffer.charAt(i) != ',') {
                        tempStr += lineBuffer.charAt(i);
                        ++i;
                    }
                    newUser.setUserName(tempStr);
                    tempStr = ""; //Clearing temp
                    ++i;//Skipping coma

                    //Password
                    while (lineBuffer.charAt(i) != ',') {
                        tempStr += lineBuffer.charAt(i);
                        ++i;
                    }
                    newUser.setPassword(tempStr);
                    tempStr = ""; //Clearing temp
                    ++i;//Skipping coma

                    //GuestOrRecep
                    newUser.setGuestOrRecep(lineBuffer.charAt(i));
                    ++i;
                }
                if(newUser.getGuestOrRecep() == 'g')
                    guestLoginInfo.add(newUser);
                else if(newUser.getGuestOrRecep() == 'r')
                    recepLoginInfo.add(newUser);
                i = 0;
            }
        }
        catch(Exception e){
            System.err.println(e.toString());
        }
    }

    /**
     * Saves HotelRoom and user informations under given file names. Please not that those files must be csv file.
     * @param roomCSV csv file that will hold room informations.
     * @param userCSV csv file that will hold user informations.
     * @throws InvalidParameterException Throws InvalidParameterException if file format is not csv.
     * @throws FileNotFoundException Throws FileNotFoundException if the file doesn't exist
     */
    private void saveData(String roomCSV, String userCSV) throws InvalidParameterException, FileNotFoundException{
        //Checking csv format
        if ( !(roomCSV.charAt(roomCSV.length() - 3) == 'c' && roomCSV.charAt(roomCSV.length() - 2) == 's' && roomCSV.charAt(roomCSV.length() - 1) == 'v')
                || !(userCSV.charAt(userCSV.length() - 3) == 'c' && userCSV.charAt(userCSV.length() - 2) == 's' && userCSV.charAt(userCSV.length() - 1) == 'v') ){
            System.out.println("Save files must be csv format");
            throw new InvalidParameterException();
        }
        else{
            try {
                File roomFile = new File(roomCSV);
                File userFile = new File(userCSV);

                //Deleting old save files.
                roomFile.delete();
                userFile.delete();

                //Creating new save files.
                roomFile.createNewFile();
                userFile.createNewFile();

                FileWriter roomFW = new FileWriter(roomFile);
                FileWriter userFW = new FileWriter(userFile);

                for (int i = 0; i < hotelRooms.size(); ++i) {
                    roomFW.append(hotelRooms.get(i).getRoomNo() + "");
                    roomFW.append(',');
                    roomFW.append(boolToInt(hotelRooms.get(i).getIsEmpty()) + "");
                    roomFW.append(',');
                    roomFW.append(boolToInt(hotelRooms.get(i).getIsBooked()) + "");
                    roomFW.append(',');
                    roomFW.append(boolToInt(hotelRooms.get(i).getIsCheckedIn()) + "");
                    roomFW.append(',');
                    roomFW.append(hotelRooms.get(i).getOwnerID() + "");
                    roomFW.append('\n');
                    roomFW.flush();
                }
                roomFW.close();

                for (int i = 0; i < recepLoginInfo.size(); ++i) {
                    userFW.append(recepLoginInfo.get(i).getLoginInfoNo() + "");
                    userFW.append(',');
                    userFW.append(recepLoginInfo.get(i).getName());
                    userFW.append(',');
                    userFW.append(recepLoginInfo.get(i).getSurname());
                    userFW.append(',');
                    userFW.append(recepLoginInfo.get(i).getUsername());
                    userFW.append(',');
                    userFW.append(recepLoginInfo.get(i).getPassword());
                    userFW.append(',');
                    userFW.append(recepLoginInfo.get(i).getGuestOrRecep());
                    userFW.append('\n');
                    userFW.flush();
                }
                for (int i = 0; i < guestLoginInfo.size(); ++i) {
                    userFW.append(guestLoginInfo.get(i).getLoginInfoNo() + "");
                    userFW.append(',');
                    userFW.append(guestLoginInfo.get(i).getName());
                    userFW.append(',');
                    userFW.append(guestLoginInfo.get(i).getSurname());
                    userFW.append(',');
                    userFW.append(guestLoginInfo.get(i).getUsername());
                    userFW.append(',');
                    userFW.append(guestLoginInfo.get(i).getPassword());
                    userFW.append(',');
                    userFW.append(guestLoginInfo.get(i).getGuestOrRecep());
                    userFW.append('\n');
                    userFW.flush();
                }
                userFW.close();
                System.out.println("Data successfully saved.");

            } catch (Exception e) {
                throw new FileNotFoundException();
            }
        }
    }

    /**
     * Converts boolean value to 0 for False, 1 for True
     * @param b integer number.
     * @return 1 for True, 0 for False.
     */
    private int boolToInt(boolean b) {
        if(b)
            return 1;
        else
            return 0;
    }

    /**
     * Prints rooms status.
     */
    private void showRooms(){
        for(int i = 0; i< hotelRooms.size(); ++i){
            System.out.print("RoomNo:" + hotelRooms.get(i).getRoomNo() + "  ");
            if(hotelRooms.get(i).getIsBooked())
                System.out.println("Booked");
            else if(hotelRooms.get(i).getIsEmpty())
                System.out.println("Available");
            else
                System.out.println("Unavailable");
        }
    }

    /**
     * Returns a HotelRoom variable from hotelRooms at given index.
     * @param index Index of the HotelRoom value.
     * @return Returns the HotelRoom value at the specified index.returns HotelRoom
     */
    private HotelRoom getRoom(int index){
        if(index < 0 || index > hotelRooms.size()){
            System.out.println("Invalid index");
            System.exit(-1);
        }

        return hotelRooms.get(index);
    }

    /**
     * Simple test method where 1 guest and 1 reception uses all the system operations.
     */
    public void hotelTest(){
        try {
            User guest1 = new User("Utk", "sezgin", "us",
                    "us95",'g');
            User recep1 = new User("utku", "sezgn", "usezgin",
                    "utk123", 'r');

            System.out.println("Guest signing in.");
            this.login(guest1);
            System.out.println("Receptionist signing in.");
            this.login(recep1);

            this.showRooms();

            //Guest booking room.
            System.out.println("\n isBooked variable before the guest booking the room: " + this.getRoom(0).getIsBooked());
            this.guestBookRoom(guest1, 1);
            System.out.println("isBooked variable after the guest booking the room: " + this.getRoom(0).getIsBooked() + "\n");

            //Guest canceling booked room.
            System.out.println("isBooked variable before the guest cancel the book: " + this.getRoom(0).getIsBooked());
            this.guestCancelBook(guest1, 1);
            System.out.println("isBooked variable after the guest cancel the book: " + this.getRoom(0).getIsBooked() + "\n");

            //Receptionist booking the room
            System.out.println("isBooked variable before the receptionist booking the room: " + this.getRoom(0).getIsBooked());
            this.recepBookRoom(recep1, guest1.getLoginInfoNo(), 1);
            System.out.println("isBooked variable after the receptionist booking the room: " + this.getRoom(0).getIsBooked() + "\n");

            System.out.println("isBooked variable before the receptionist cancel the book: " + this.getRoom(0).getIsBooked());
            this.recepCancelBook(recep1, guest1.getLoginInfoNo(), 1);
            System.out.println("isBooked variable after the receptionist cancel the book: " + this.getRoom(0).getIsBooked() + "\n");


            //Guest booking the room again to check-in.
            this.guestBookRoom(guest1, 1);

            //Check-in to booked room.
            System.out.println("Before Check-in isEmpty: " + this.getRoom(0).getIsEmpty() + " isBooked: " +
                    this.getRoom(0).getIsBooked() + " isCheckedIn: " + this.getRoom(0).getIsCheckedIn());
            this.recepCheckIn(recep1, guest1.getLoginInfoNo(), 1);
            System.out.println("After Check-in isEmpty: " + this.getRoom(0).getIsEmpty() + " isBooked: " +
                    this.getRoom(0).getIsBooked() + " isCheckedIn: " + this.getRoom(0).getIsCheckedIn());

            //After Check-out.
            System.out.println("\nBefore Check-in isEmpty: " + this.getRoom(0).getIsEmpty() + " isBooked: " +
                    this.getRoom(0).getIsBooked() + " isCheckedIn: " + this.getRoom(0).getIsCheckedIn());
            this.recepCheckOut(recep1, guest1.getLoginInfoNo(), 1);
            System.out.println("After Check-in isEmpty: " + this.getRoom(0).getIsEmpty() + " isBooked: " +
                    this.getRoom(0).getIsBooked() + " isCheckedIn: " + this.getRoom(0).getIsCheckedIn() + '\n');

            showRooms();

            this.saveData("roomSave.csv", "userSave.csv");
        }
        catch (Exception e){
            System.out.println(e.toString());
        }
    }

}