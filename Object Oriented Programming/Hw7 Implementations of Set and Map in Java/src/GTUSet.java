/**	
 * <b>class GTUSet&lt;T&gt;</b> <br>
 * <b>SuperInterfaces</b><br>
 * GTUSetInt&lt;T&gt;
 *
 * 
 * A collection that contains no duplicate elements.<br> <br>
 * 
 * This class has following methods,
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
 * @param <T> the type of elements maintained by this set.
 * 
 * 
 */
public class GTUSet<T> implements GTUSetInt<T> {
	
    /**
     *The size of container.
     */
    protected int cSize;

    /**
     *The capacity of container
     */
    protected int mSize;

    /**
     *Holds T type values in Java.Arrays
     */
    protected T[] container;
	
	//GTUIterator class implementation
	/**
	 *  class GTUIterator implements java.util.Iterator&lt;T&gt;
	 *  
	 *  This class implements java.util.Iterator&lt;T&gt;  and has following methods,
	 *  <ul>
	 *  <li> boolean hasNext()		-&gt;Returns true if there's a next element.
	 *  <li> T next() throws java.util.NoSuchElementException	-&gt;Returns the next element.
	 *  <li>  boolean hasPrevious()		-&gt;Returns true if there's a previous element.
	 *  <li> T previous() throws java.util.NoSuchElementException		-&gt;Returns the previous element.
	 *  </ul>
	 *  
	 */
	public class GTUIterator implements java.util.Iterator<T>{
		
		int index;
		
		//No parameter constructor sets index to first element
		/**
		 * GTUIterator()<br>
		 * No parameter constructor that makes iterator point to first element
		 */
		GTUIterator(){
			index = 0;
		}
		
		/**
		 * GTUIterator(int lastElement)
		 * This constructor takes any integer and regardless of the value of integer, iterator points to last element
		 * @param lastElement
		 * Regardless of the value of lastElement this constructor constructs the iterator that points to the last element
		 */
		//Constructor with an integer argument sets index to last element
		GTUIterator(int lastElement){
			index = cSize-1;
		}
		
		////Checks if container has element after the current one
		/* (non-Javadoc)
		 * @see java.util.Iterator#hasNext()
		 */
		@Override
		public boolean hasNext() {
			if(index < cSize)
				return true;
			else
				return false;
		}
		
		//Returns the current element and moves iterator to next element
		/* (non-Javadoc)
		 * @see java.util.Iterator#next()
		 */
		@Override
		public T next() throws java.util.NoSuchElementException{
			T temp; //Initialization
			if(!hasNext()) {
				throw new java.util.NoSuchElementException("Iteration has no reachable element");
			}
			
			temp = container[index];
			++index;
			return temp;			
		}	
		/**
		 *  boolean hasPrevious()<br>
		 *  Returns True if the iteration has more elements	
		 * @return
		 *    True if the iteration has more elements.
		 */
		public boolean hasPrevious() {
			if(index>0)
				return true;
			else
				return false;
		}
		
		/**
		 * T previous() <br>
		 * Returns the previous element in the iteration
		 * @return
		 * True if the iteration has more elements.
		 * @throws java.util.NoSuchElementException
		 * Throws exception when theres no previous element
		 */
		//Returns the current element and moves iterator to previous element
		public T previous() throws java.util.NoSuchElementException {
			T temp; //Initialization
			if(!hasPrevious()) {
				throw new java.util.NoSuchElementException("Iteration has no reachable element");
			}
				
			
			temp = container[index];
			--index;
			return temp;			
		}	
		
	}
	
	//End of GTUIterator class implementation
	

	/**
	 *  GTUSet() <br>
	 *  No parameter constructor increases capacity and size stays as 0
	 */
	GTUSet(){//No parameter constructor of GTUSet
		cSize = 0;	//Default
		mSize = 5; //Default
		
		container = (T[]) new Object[mSize];
	}
	
	/**
	 * void sizeCheck(int newSize) <br>
	 * If newSize is greater than capacity this function expands the capacity without changing any elements 
	 * @param newSize <br>
	 * 	&nbsp; &nbsp; newSize is to check if we want to see expand the capacity
	 * 
	 */
	protected void sizeCheck(int newSize) { //Ts the capacity if size is equal or greater than the capacity
		if(newSize >= mSize) {
			mSize *= 2;
		
			T[] temp = (T[]) new Object[cSize];
			System.arraycopy(container, 0, temp, 0, cSize); //Copies old elements into new one
			
			container = (T[]) new Object[mSize];
			System.arraycopy(temp, 0, container, 0, cSize);
		}
		
	}
	//Checks if the container is empty
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#empty()
	 */
	@Override
	public boolean empty() {
		if(cSize == 0)
			return true;
		else
			return false;
	}
	//Returns size of the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#size()
	 */
	@Override
	public int size() { 
		return cSize; 
	}
	
	
	//Returns max size of the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#max_size()
	 */
	@Override
	public int max_size() {
		return mSize;
	}
	
	//Inserts the element to the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#insert(java.lang.Object)
	 */
	@Override
	public boolean insert(T element) throws java.lang.IllegalArgumentException {
		
		for(int i = 0; i < cSize; ++i) {
			if(container[i].equals(element)) { //Throws java.lang.IllegalArgumentException if element exist
				throw new IllegalArgumentException("Illegal argument");
			}				
		}
		
		sizeCheck( (cSize+1) ); //Size check before inserting operation
		
		container[cSize] = element; //Inserting the element, increasing size and returning true
		++cSize;
		return true;
	}
	
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#intersection(myContainer.GTUSetInt)
	 */
	@Override
	public GTUSetInt<T> intersection(GTUSetInt<T> other) {
		T itTemp1, itTemp2;
		GTUSet<T> temp = new GTUSet<T>();
				
		java.util.Iterator<T> itThis = this.begin();
		java.util.Iterator<T> itOther = other.begin();
		
		
		while(itThis.hasNext()) {
			itTemp1 = itThis.next();
			while(itOther.hasNext()) {
				itTemp2 = itOther.next();
				if( itTemp1.equals(itTemp2) ) {
					temp.insert(itTemp1);					
				}
			}
			itOther = other.begin();
		}
		return temp;
	}
	
	//Erases the element from the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#erase(java.lang.Object)
	 */
	@Override
	public void erase(T element) {
		for(int i=0; i<cSize; ++i) {
			if(container[i].equals(element)) {
				if(i == cSize-1)
					--cSize; //If it's the last element, reduce the size by 1
				else {
					for(int j=i; j<cSize-1; ++j) { //Shifting elements to left and reducing size by 1
						container[j]= container[j+1];
					}
					--cSize;
				}
					
			}
				
		}
	}
	
	@Override
	public void clear() {
		cSize = 0;
	}
	
	//Searches the element inside the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#find(java.lang.Object)
	 */
	@Override
	public GTUIterator find(T element) {
		int isFound = 0;
		GTUIterator it = new GTUIterator();
		
		for(int i=0; i<cSize; ++i) {
			if(container[i].equals(element)) {
				it.index = i;
				isFound = 1;
			}
		}
		
		if(isFound == 0){//If the element doesnt exist iterator points to last element
			it.index = cSize-1; 
		}
		return it;		
	}
	
	//Counts how many 'value' elements in the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#count(java.lang.Object)
	 */
	public int count(T value){
		int elementCount = 0;
		for(int i=0; i<cSize; ++i) {
			if(container[i].equals(value)) {
				++elementCount;
			}
		}
		return elementCount;
	}
	
	//Returns an iterator that points to first element of the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#begin()
	 */
	@Override
	public java.util.Iterator<T> begin() {
		java.util.Iterator<T> it = new GTUIterator();
		return it;
	}
	
	//Returns an iterator that points to last element of the container
	/* (non-Javadoc)
	 * @see myContainer.GTUSetInt#end()
	 */
	@Override
	public java.util.Iterator<T> end() {
		java.util.Iterator<T> it = new GTUIterator(5);
		return it;
	}
	
}