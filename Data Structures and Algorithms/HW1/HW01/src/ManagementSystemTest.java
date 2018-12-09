import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Unit testing class fo ManagementSystem
 */
//FIXME Since the methods are private, in order for this to work, you need to set these method's privilege to public.
//Important note: Please note that room numbers start from 1 and getRoom method starts from 0 so they match as 1=0, 2=1... etc.
class ManagementSystemTest {/*

    User guest1 = new User("Utk", "sezgin", "us",
            "us95",'g');
    User recep1 = new User("utku", "sezgn", "usezgin",
            "utk123", 'r');

    ManagementSystem hotelTest = new ManagementSystem("roomSave.csv", "userSave.csv");

    @Test
    void login() {
        System.out.println("Log-in status before operation: " + recep1.getIsLoggedIn());
        hotelTest.login(recep1);
        assertEquals("Online", recep1.getIsLoggedIn());
    }

    @Test
    void guestBookRoom() {
        hotelTest.login(guest1);
        System.out.println("HotelRoom isBooked status before booking operation: " + hotelTest.getRoom(0).getIsBooked());
        hotelTest.guestBookRoom(guest1, 1);
        assertEquals(true, hotelTest.getRoom(0).getIsBooked());
    }

    @Test
    void guestCancelBook() {
        hotelTest.login(guest1);
        hotelTest.guestBookRoom(guest1, 1);
        System.out.println("HotelRoom isBooked status before canceling the book operation: " + hotelTest.getRoom(0).getIsBooked());
        hotelTest.guestCancelBook(guest1, 1);
        assertEquals(false, hotelTest.getRoom(0).getIsBooked());

    }

    @Test
    void recepBookRoom() {
        hotelTest.login(recep1);
        System.out.println("HotelRoom isBooked status before booking operation: " + hotelTest.getRoom(0).getIsBooked());
        hotelTest.recepBookRoom(recep1, 1, 1);
        assertEquals(true, hotelTest.getRoom(0).getIsBooked());
    }

    @Test
    void recepCancelBook() {
        hotelTest.login(recep1);
        hotelTest.recepBookRoom(recep1, 1, 1);
        System.out.println("HotelRoom isBooked status before canceling the book operation: " + hotelTest.getRoom(0).getIsBooked());
        hotelTest.recepCancelBook(recep1, 1, 1);
        assertEquals(false, hotelTest.getRoom(0).getIsBooked());
    }

    @Test
    void recepCheckIn() {
        hotelTest.login(recep1);
        System.out.println("HotelRoom isCheckedIn status before Check-in operation: " + hotelTest.getRoom(0).getIsCheckedIn());
        hotelTest.recepCheckIn(recep1, 1, 1);
        assertEquals(true, hotelTest.getRoom(0).getIsCheckedIn());
    }

    @Test
    void recepCheckOut() {
        hotelTest.login(recep1);
        hotelTest.recepCheckIn(recep1, 1, 1);
        System.out.println("HotelRoom isCheckedIn status before Check-out operation: " + hotelTest.getRoom(0).getIsCheckedIn());
        hotelTest.recepCheckOut(recep1, 1, 1);
        assertEquals(false, hotelTest.getRoom(0).getIsCheckedIn());
    }*/
}