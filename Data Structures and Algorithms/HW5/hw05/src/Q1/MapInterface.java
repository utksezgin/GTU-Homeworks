package Q1;

/**
 * Map interface to store a key and it's value.
 * @param <K> Key
 * @param <V> Value
 */
public interface MapInterface<K, V>{
    /**
     * @param key Key to search in map.
     * @return Returns the value of key.
     */
    V get(K key);

    /**
     * @return Returns true if the map is empty.
     */
    boolean isEmpty();

    /**
     * Inserts a new element inside the map.
     * @param key Key of new element.
     * @param value Value of new element.
     * @return Returns the old value if the key existed else the new value.
     */
    V put(K key, V value);

    /**
     * @param key Key of element to remove.
     * @return Returns the removed elemeent's value.
     */
    V remove(K key);

    /**
     * @return Returns the size of the map.
     */
    int size();
}
