/**
 *  User class extends AbstractPerson class and contains informations of System users.
 */
public class User extends AbstractPerson{
    /**
     * Username of the user.
     */
    private String username;
    /**
     * Password of the user.
     */
    private String password;
    /**
     * Log-in status of the user.
     */
    private String isLoggedIn;
    /**
     * loginInfoNo also known as userID of the user
     */
    private int loginInfoNo;
    /**
     * Either 'g' which stands for Guest or 'r' which stands for Receptionist
     */
    private char guestOrRecep;


    /**
     * @param name Name of the user.
     * @param surname Surname of the user.
     * @param username Username of the user.
     * @param password Password of the user.
     * @param guestOrRecep 'g' for guest, 'r' for receptionist
     */
    User(String name, String surname, String username, String password, char guestOrRecep){//Error handle
        super(name, surname);
        this.username = username;
        this.password = password;
        this.isLoggedIn = "Offline";
        this.loginInfoNo = 0;
        this.guestOrRecep = guestOrRecep;

    }

    /**
     * Getter for user's name.
     * @return Returns the name of the user.
     */
    public String getName(){
        return this.name;
    }

    /**
     * Getter for user's surname.
     * @return Returns the surname of the user.
     */
    public String getSurname(){
        return this.surname;
    }

    /**
     * Getter for user's username.
     * @return Returns the username of the user.
     */
    public String getUsername(){
        return this.username;
    }

    /**
     * Getter for user's password.
     * @return Returns the password. of the user.
     */
    public String getPassword(){
        return this.password;
    }


    /**
     * Getter for log-in status.
     * @return Returns the log-in status of the user.
     */
    public String getIsLoggedIn(){
        return this.isLoggedIn;
    }

    /**
     * Getter for user's authorization level.
     * @return returns guestOrRecep value.
     */
    public char getGuestOrRecep(){
        return this.guestOrRecep;
    }

    /**
     * Getter for userID.
     * @return returns the value of loginInfoNo.
     */
    public int getLoginInfoNo(){
        return loginInfoNo;
    }
    //Most of these setter shouldn't exist in an actual Hotel Management System and should be held in a server
    //with a proper sign-up setup but,
    //We need them for initializations and updating informations in this case.

    /**
     * Sets the name of the user.
     * @param name name of the user.
     */
    public void setName(String name){
        this.name = name;
    }


    /**
     * Sets the surname of the user.
     * @param surname Surname of the user.
     */
    public void setSurname(String surname){
        this.surname = surname;
    }

    /**
     * Sets the usaername of the user.
     * @param username Username of the user.
     */
    public void setUserName(String username){
        this.username = username;
    }

    /**
     * Sets the password of the user.
     * @param password Password of the user.
     */
    public void setPassword(String password){
        this.password = password;
    }

    /**
     * @param isLoggedIn Login status of the user "Online" or "Offline".
     * @throws IllegalArgumentException Throws exception for invalid status.
     */
    public void setIsLoggedIn(String isLoggedIn) throws IllegalArgumentException{
        if(isLoggedIn == "Online" || isLoggedIn == "online")
            this.isLoggedIn = "Online";
        else if(isLoggedIn == "Offline" || isLoggedIn == "offline")
            this.isLoggedIn = "Offline";
        else
            throw new IllegalArgumentException();
    }

    /**
     * @param guestOrRecep Can only be 'g' stands for Guest or 'r' stands for Receptionist
     * @throws IllegalArgumentException Throws exception for invalid status.
     */
    public void setGuestOrRecep(char guestOrRecep) throws IllegalArgumentException{
        if(guestOrRecep != 'g' && guestOrRecep != 'G' && guestOrRecep != 'r' && guestOrRecep != 'R'){
            throw new IllegalArgumentException();
        }
        this.guestOrRecep = guestOrRecep;
    }

    /**
     * @param logNo userID, cannot be less than 0.
     * @throws IllegalArgumentException Throws exception for invalid status.
     */
    public void setLoginInfoNo(int logNo) throws IllegalArgumentException{
        if(logNo >= 0)
            loginInfoNo = logNo;
        else
            throw new IllegalArgumentException();
    }

    /**
     * @return "User's Name:" + Name + Surname + Username + guestOrRecep
     */
    @Override
    public String toString() {
        return "User's Name: " + name + " "+ surname + " " + username + " "+ guestOrRecep;
    }
}
