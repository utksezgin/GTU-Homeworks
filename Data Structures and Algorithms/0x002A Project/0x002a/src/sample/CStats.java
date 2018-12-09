package sample;

import javafx.util.Pair;
import java.util.HashMap;
import java.util.Set;

/**
 * A class for 0x002a game.
 * It's job is saving and updating characteristic info.
 */
public class CStats
{
    /**
     * User defined characteristic information
     * field and their values.
     */
    private HashMap<String, Integer> status;
    /**
     * Max acceptable characteristic info field.
     */
    private static final int MAX_VALUE = 4;
    /**
     * Default values for characteristic info.
     */
    private static final int DEFAULT = 0;

    /**
     * Creates a new empty Stats field.
     */
    public CStats()
    {
        this(new HashMap<>());
    }

    /**
     * Creates a new Cstats from the input string.
     * @param input a special string to read a Cstats info.
     */
    public CStats(String input)
    {
        status = new HashMap<>();
        String[] array = input.split("<");
        array = array[0].split(">");
        if(!array[0].isEmpty())
        {
            array = array[0].split(",");
            for (String parser : array)
                status.put(parser.split(":")[0], Integer.valueOf(parser.split(":")[1]));
        }
    }

    /**
     * Copy constructor.
     * @param other item to be copied.
     */
    public CStats(CStats other)
    {
        this(other.status);
    }

    /**
     * Creat a Cstats with given HashMap
     * @param input a HashMap for necessary field.
     */
    public CStats(HashMap<String, Integer> input)
    {
        status = new HashMap<>();
        Set<String> other = input.keySet();
        for(String temp : other)
            addParam(temp, input.get(temp));
    }

    /**
     * Take a HashMap with the value of Char-Integer pair.
     * Update the actual value of Cstats's status field value by the pair's declaration.
     * @param input string for characteristic info name, char and int are for the update operation declaration.
     * @return if the operation made or not.
     */
    public boolean updateAllStats(HashMap<String, Pair<Character, Integer>> input)
    {
        boolean ret_val = true;
        if(input.size() > status.size())
            ret_val = false;
        else
        {
            Set<String> temp = input.keySet();
            for(String search : temp)
                if(!(ret_val = updateStats(new Pair<>(search, input.get(search)))))
                    break;
        }
        return ret_val;
    }

    /**
     * Updating a stat with given info.
     * @param name updating field's name.
     * @param opt updating with witch operation, +, -, *, /, %, =.
     * @param number updating the field with this parameter.
     * @return if operation made or not.
     */
    public boolean updateStats(String name, Character opt, Integer number)
    {
        return updateStats(new Pair<>(name, new Pair<>(opt, number)));
    }

    /**
     * Update stats with given input.
     * @param input pair-String, Pair-Character, Integer--
     * @return if operation made or not.
     */
    private boolean updateStats(Pair<String, Pair<Character, Integer>> input)
    {
        boolean ret_val = true;
        if(status.containsKey(input.getKey()))
            switch (input.getValue().getKey())
            {
                case '+':
                    status.put(input.getKey(), status.get(input.getKey()) + input.getValue().getValue());
                    break;
                case '-':
                    status.put(input.getKey(), status.get(input.getKey()) - input.getValue().getValue());
                    break;
                case '*':
                    status.put(input.getKey(), status.get(input.getKey()) * input.getValue().getValue());
                    break;
                case '/':
                    status.put(input.getKey(), status.get(input.getKey()) / input.getValue().getValue());
                    break;
                case '%':
                    status.put(input.getKey(), status.get(input.getKey()) % input.getValue().getValue());
                    break;
                case '=':
                    status.put(input.getKey(),  input.getValue().getValue());
                    break;
                default:
                ret_val = false;
                break;
            }
        else
            ret_val = false;
        return ret_val;
    }

    /**
     * Add a new stat value with default value.
     * @param key name of the stat.
     * @return if operation made or not.
     */
    public boolean addParam(String key)
    {
        return this.addParam(key, DEFAULT);
    }

    /**
     * Add a stat to the status table with given value.
     * @param key Stat's name
     * @param Value Value of the stat.
     * @return if operation made or not.
     */
    public boolean addParam(String key, Integer Value)
    {
        boolean ret_val = false;
        if(status.size() < MAX_VALUE)
        {
            if(!status.containsKey(key))
            {
                status.put(key, Value);
                ret_val = true;
            }
        }
        return ret_val;
    }

    /**
     * Oyuncu karakteri verilen ön şartı karşılayıp, bir sonraki node'a erişebiliyor mu diye kontrol eder.
     * Eğer gerekli ön şartları sağlıyorsa true, sağlamıyorsa false döner.
     * @param preRequisite Ön şart
     * @return  Ön şart sağlanıyorsa true, sağlanmıyorsa false
     */
    public boolean canAccess(HashMap<String, Pair<Character, Integer>> preRequisite){
        Set<String> keyVal = preRequisite.keySet();

        for(String cpr : keyVal) {
            if(status.containsKey(cpr)) {
                Integer currStat = status.get(cpr);
                switch (preRequisite.get(cpr).getKey()) {
                    case '<':
                        if (currStat < preRequisite.get(cpr).getValue());
                        else return false;
                    case '>':
                        if (currStat > preRequisite.get(cpr).getValue());
                        else return false;
                    case '=':
                        if (currStat.equals(preRequisite.get(cpr).getValue()));
                        else return false;
                }
            }
            else return false;
        }

        return true;
    }

    /**
     * Get all the stat's name with set of stats.
     * @return A set of all stat nemes.
     */
    public Set<String> getStats()
    {
        return status.keySet();
    }

    /**
     * A printable way of all characteristic infos and their values.
     * @return String version of map.
     */
    @Override
    public String toString() {
        String ret_val = "";
        if(!status.isEmpty())
        {
            Set<String> keyV = status.keySet();
            for(String outp : keyV)
                ret_val += "{" + outp + ": " + status.get(outp).toString() + "}";
        }
        return ret_val;
    }

    /**
     * Check all the stat's existence in the map.
     * @param other CStats object to compare
     * @return There is all stat names are exist.
     */
    @Override
    public boolean equals(Object other)
    {
        return ((CStats) other).getStats().containsAll(this.getStats());
    }

    /**
     * Create a String as saveable format.
     * @return a string to save.
     */
    public String toSave()
    {
        String ret_val = "<";
        if(!status.isEmpty())
        {
            Set<String> keyV = status.keySet();
            for(String outp : keyV)
                ret_val += outp + ":" + status.get(outp).toString() + ",";
        }
        ret_val += ">";
        return ret_val;
    }
}