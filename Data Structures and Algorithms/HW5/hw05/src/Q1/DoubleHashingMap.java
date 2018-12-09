package Q1;

/**
 * This is a HashMap where conflictions handled by double hashing.
 * @param <K> Key.
 * @param <V> Value.
 */
public class DoubleHashingMap<K, V> implements MapInterface<K, V> {
    private Entry<K, V>[] table;
    private final Entry<K, V> deletedEntry = new Entry<>();
    private int size;
    private int numKeys = 0;
    private int capacity;
    private static final int START_CAPACITY = 101;
    private double LOAD_THRESHOLD = 0.75;

    /**
     * DoubleHashingMap stores an array of entries to store data.
     * @param <K> Key.
     * @param <V> Value.
     */
    private static class Entry<K, V>{
        private K key;
        private V value;

        /**
         * No parameter Constructor creates an empty entry.
         */
        Entry(){
            this.key = null;
            this.value = null;
        }

        /**
         * Creates an entry with given key, value
         * @param key Key.
         * @param value Value.
         */
        Entry(K key, V value){
            this.key = key;
            this.value = value;
        }

        /**
         * @return Returns the key of the entry.
         */
        private K getKey(){
            if(key == null)
                return null;
            else
                return key;
        }

        /**
         * @return Returns the value of the entry.
         */
        private V getValue(){
            return value;
        }

        /**
         * Setter for the value of entry.
         * @param val new Value.
         * @return
         */
        //Returns old val
        private V setValue(V val){
            V oldVal = value;
            value = val;
            return oldVal;
        }

    }


    /**
     * No parameter constructor that creates an empty DoubleHashingMap with default table size which is 101.
     */
    DoubleHashingMap(){
        table = new Entry[START_CAPACITY];
        for(int i=0; i< START_CAPACITY; ++i)
            table[i] = null;

        capacity = START_CAPACITY;
        size = 0;
    }

    /**
     * Creates a map with given table size.
     * @param size Table size of the hashmap.
     */
    DoubleHashingMap(int size){
        table = new Entry[size];
        for(int i=0; i< size; ++i)
            table[i] = null;

        capacity = size;
        size = 0;
    }

    /**
     * @param key key to search in map.
     * @return Returns the value of given key.
     */
    //Returns null if key not found.
    @Override
    public V get(K key){
        V returnVal = null;
        int index = key.hashCode();
        int firstHash = firstHashing(index);
        int newHash;
        int secondHashingTries = 1;
        if(table[firstHash] == null)
            return null;
        else if(table[firstHash].getKey().equals(key))
            returnVal = (V) table[firstHash].getValue();
        else{ //If the item is deleted
            boolean isFound = false;
            while(!isFound){
                newHash = firstHash + secondHashing(firstHash)*secondHashingTries;
                ++ secondHashingTries;
                if(table[newHash] == null)
                    return null;
                else if(table[newHash].getKey().equals(key)){
                    isFound = true;
                    returnVal = (V) table[newHash].getValue();
                }
                //Couldn't find.
                if(secondHashingTries == size)
                    return null;
            }
        }
        return returnVal;
    }

    /**
     * Returns the value of entry at given index. This method is for testing purposes only and throws Exception if index is out of bounds.
     * @param index Position in table.
     * @return Returns the value of Entry at given index in the map.
     * @throws IndexOutOfBoundsException Throws exception if the index is out of bounds.
     */
    public V getIndex(int index) throws IndexOutOfBoundsException {
        if(index < 0 || index > capacity)
            throw new IndexOutOfBoundsException();
        else
            return table[index].getValue();

    }

    /**
     * @return Returns true if there are no keys in the table.
     */
    @Override
    public boolean isEmpty(){
        if(size == 0)
            return true;
        else
            return false;
    }

    /**
     * Removes the Entry of given key.
     * @param key Key of the entry to remove.
     * @return Value of removed entry.
     */
    @Override
    public V remove(K key){
        int index = key.hashCode();
        int firstHash = firstHashing(index);
        int newHash;
        int secondHashingTries = 1;
        V deletedItem = null;
        if(table[firstHash] == null)//Unknown key
            return null;
        else if(table[firstHash].getKey().equals(key)) {
            deletedItem = (V) table[firstHash].getValue();
            table[firstHash] = deletedEntry; //Sets deleted item's location as deleted.
            --numKeys;
            return deletedItem;
        }
        else{ //If the entry is deleted or not matched
            boolean isFound = false;
            while(!isFound){
                newHash = firstHash + secondHashing(firstHash)*secondHashingTries;
                ++ secondHashingTries;
                if(table[newHash] == null)
                    deletedItem = null;
                else if(table[newHash].getKey().equals(key)){
                    deletedItem = (V) table[newHash].getValue();
                    table[newHash] = deletedEntry;
                    --numKeys;
                    isFound = true;
                }
                if(secondHashingTries == size)
                    return null;
            }
            return deletedItem;
        }


    }

    /**
     * @return Returns the Entry numbers in the map.
     */
    @Override
    public int size(){
        return numKeys;
    }

    /**
     * Inserts a new entry to the map using double hashing.
     * @param key Key of the entry.
     * @param value Value of the entry.
     * @return Returns the value of entry. If the key already exists, returns the old value of key.
     */
    @Override
    public V put(K key, V value){
        int index = key.hashCode();
        int firstHash = firstHashing(index);
        int newHash;
        int secondHashingTries = 1;

        if(table[firstHash] == null || (table[firstHash].getValue() == null && table[firstHash].getKey() == null) ){ //If empty.
            table[firstHash] = new Entry<>(key, value);
            ++size;
            ++numKeys;
            double loadFactor = (double) size / table.length;
            if(loadFactor > LOAD_THRESHOLD)
                rehash();
            return value;
        }
        else if(table[firstHash].getKey() == key ){
            V oldVal = (V) table[firstHash].getValue();
            table[firstHash].setValue(value);
            return oldVal;
        }
        else{
            boolean isEmpty = false;
            while(!isEmpty) {
                newHash = (firstHash + secondHashing(firstHash) * secondHashingTries)%table.length;
                ++secondHashingTries;
                if( table[newHash] != null && table[newHash].getKey()!= null && table[newHash].getKey().equals(key) ){
                    V oldVal = (V) table[newHash].getValue();
                    table[newHash].setValue(value);
                    return oldVal;
                }

                else if(table[newHash] == null || (table[newHash].getValue() == null && table[newHash].getKey() == null) ){
                    isEmpty = true;
                    table[newHash] = new Entry<>(key, value);
                    ++size;
                    ++numKeys;
                    //rehash check
                    return value;
                }
                if(secondHashingTries == size)
                    return null;
            }
        }

        return null;
    }

    /**
     * Calculates the first hashing position for given key. Note that key must be hashcode of your actual key!
     * @param key Hashcode of key to insert.
     * @return Returns the index.
     */
    private int firstHashing(int key){
        int hashCode = Math.abs(key%table.length);
        return hashCode;
    }

    /**
     * Calculates the second hashing position for given key. Node that key must be hashcode of your actual key!
     * @param index Hashcode of key to insert.
     * @return Returns the index.
     */
    private int secondHashing(int index){
        int hashCode = Math.abs(3-index%3);
        return hashCode;
    }

    /**
     * Increases the size of the table and places entries according to new table.
     */
    private void rehash(){
        Entry<K, V>[] oldTable = table;
        capacity = 2*oldTable.length;
        table = new Entry[capacity];

        size = 0;
        numKeys = 0;
        for (Entry<K, V> tempEntry : oldTable) {
            if (tempEntry != null && tempEntry != deletedEntry) {
                put(tempEntry.key, tempEntry.value);
            }
        }

    }
}