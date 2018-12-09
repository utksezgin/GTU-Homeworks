/**
 * An abstract class that holds Name and Surname of a person.
 */
public abstract class AbstractPerson implements Person {
    /**
     * Name of the user.
     */
    protected String name;
    /**
     * Surname of the user.
     */
    protected String surname;

    AbstractPerson(){
        this.name = "Empty";
        this.surname = "Empty";
    }

    /**
     * 2 Parameter constructor.
     * @param name Name of the person.
     * @param surname Surname of the person.
     */
    AbstractPerson(String name, String surname){
        this.name = name;
        this.surname = surname;
    }
}
