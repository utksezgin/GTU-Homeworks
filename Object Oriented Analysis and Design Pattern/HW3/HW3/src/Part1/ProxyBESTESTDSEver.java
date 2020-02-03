package Part1;

/**
 * A proxy for using non thread-safe BestDSEver class as a thread-safe class
 */
public class ProxyBESTESTDSEver extends BESTDSEver {
    /**
     * Thread-safe linear time insertion.
     * @param o object to insert.
     */
    public void safeInsert(Object o){
        synchronized (this){
            System.out.println("Safe Insert");
            this.insert(o);
        }
    }

    /**
     * Thread-safe linear time removal.
     * @param o object to remove
     */
    public void safeRemove(Object o){
        synchronized (this){
            System.out.println("Safe Remove");
            this.remove(o);
        }
    }

    /**
     * Thread-safe linear time access.
     * @param index index to access.
     * @return returns the element in linear time.
     */
    public Object safeGet(int index){
        synchronized (this){
            System.out.println("Safe Get");
            return this.get(index);
        }

    }
}
