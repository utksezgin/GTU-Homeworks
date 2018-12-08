/**
 * <b>interface GTUSetInt&lt;T&gt;</b> <br>
 * 
 * This interface has the following methods,<br>
 *  <ul>
 *  <li>boolean empty();
 *  <li>int size();
 *  <li>int max_size();
 *  <li>boolean insert(T element)
 *  <li>GTUSetInt&lt;T&gt; intersection(GTUSetInt&lt;T&gt; other);
 *  <li>void erase(T element);
 *  <li>void clear();
 *  <li>java.util.Iterator&lt;T&gt; find(T element);
 *  <li>int count(T value);
 *  <li>java.util.Iterator&lt;T&gt; begin();
 *  <li>java.util.Iterator&lt;T&gt; end();
 *  </ul>
 *
 * @param &lt;T&gt; the type of elements maintained by this set
 * 
 * @author <b>Azmi Utku Sezgin 131044048</b>
 */

interface GTUSetInt<T> {
	/**
	 * boolean empty() <br>
	 * Returns true if the container is empty.
	 * @return
	 * 	True if the container is empty.
	 */		
	boolean empty();
	
	/**
	 * 	size() <br>
	 *  This method returns the size of the container.
	 * @return
	 * 		Returns the size of the container.
	 */	
	int size();
	
	/**
	 * int max_size() <br>
	 * This method returns the capacity of the container
	 * @return
	 * Capacity of the container
	 */
	int max_size();
	
	/**
	 * boolean insert(T element) <br>
	 * Inserts element into the container and returns true if insertion is successful. Throws exception if the element already exists.
	 * @param element : T typed variable to insert into container
	 * @return
	 * Returns true if insertion is successful
	 * @throws java.lang.IllegalArgumentException
	 * If argument exists.
	 */
	boolean insert(T element) throws java.lang.IllegalArgumentException;
	
	/**
	 * GTUSetInt&lt;T&gt; intersection(GTUSetInt&lt;T&gt; other) <br>
	 * Returns an object that contains elements that are both in this and other object.
	 * @param other : Contains elements to examine
	 * 
	 * @return
	 * Returns an object that contains elements that exist in this and other objects.
	 */
	GTUSetInt<T> intersection(GTUSetInt<T> other);
	
	/**
	 * void erase(T element) <br>
	 * Erases element from the container if it exists.
	 * 
	 * @param element : T typed argument to remove from container.
	 */
	void erase(T element);
	
	/**
	 * void clear() <br>
	 * Clears the container completely.
	 * 
	 */
	void clear();
	
	
	/**
	 * Iterator&lt;T&gt; find(T element) <br>
	 * Searches element in container and returns an iterator points to that element.
	 * @param element : T typed argument to search in the container.
	 * @return
	 * Returns an iterator that points to the element. If the element doesn't exist, iterator points to last element
	 */
	java.util.Iterator<T> find(T element);
	
	/**
	 * int count(T value) <br>
	 * Counts how many values are there in the container
	 * @param value : 
	 * @return
	 * Returns the count of value.
	 */
	int count(T value);
	
	/**
	 * Iterator&lt;T&gt; begin(); <br>
	 * This method returns an iterator that points to first element of the container.
	 * @return
	 * 	 Returns an iterator that points to first element of the container.
	 */
	java.util.Iterator<T> begin();
	
	/**
	 * Iterator&lt;T&gt; begin(); <br>
	 * This method returns an iterator that points to last element of the container.
	 * @return
	 * 	 Returns an iterator that points to last element of the container.
	 */
	java.util.Iterator<T> end();
}