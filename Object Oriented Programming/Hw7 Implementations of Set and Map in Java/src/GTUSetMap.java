import javafx.util.Pair;

/**
 *<b>class GTUSetMap&lt;K, V&gt;</b><br>
 *This Class extends GTUSet&lt;javafx.util.Pair&lt;K,V&gt;&gt; and has the following extra method
 *<ul>
 *<li> V at(K key)
 *</ul>
 *
 * 
 * @param <K> Type of key that pairs with a value in map
 * @param <V> Type of value that pairs with a key in map
 */
public class GTUSetMap<K, V> extends GTUSet<javafx.util.Pair<K,V>>{
	
	GTUSetMap(){
		super();
	}
	
	/**
	 * public V at(K key) &lt;br&gt;
	 * Gets a key as parameter and returns value of the key in the map.
	 * @param key: compares key with every key in pair 
	 * @return
	 * 	Value that pairs with key, throws exception if not found.
	 * @throws java.lang.IllegalArgumentException
	 * 	Throws IllegalArgumentException if the key does not exist.
	 */
	public V at(K key) throws  java.lang.IllegalArgumentException {
		V value;
		int isExist = -1;
		javafx.util.Pair<K,V> tempPair;
		java.util.Iterator<javafx.util.Pair<K,V>> it = this.begin();
		tempPair = it.next();//To avoid may not have been initialized error. In that case method already throws exception.
		
		it = this.begin();
		while(it.hasNext() && isExist == -1) {
			tempPair = it.next();
			if(tempPair.getKey().equals(key)) {
				isExist = 1;
			}
		}
		if(isExist == -1) {
			throw new java.lang.IllegalArgumentException("Could not found the value of the key");
		}
		else
			value = tempPair.getValue();
		
		return value;
	}
	
}