/**
 * Main class to test Management System
 */
public class GTUHotelTest {
    public static void main(String args[]){
        ManagementSystem hotelSystem = new ManagementSystem("roomSave.csv", "userSave.csv");
        hotelSystem.hotelTest();
    }
}