package sample;

/**
 * Interface for BinarySearchTree class.
 * @param <E> Type of data to store.
 */
public interface BinarySearchTreeInterface<E> {
    /**
     * Adds an item to the tree.
     * @param item Item to add to tree
     * @return returns true on successfull insertion.
     */
    boolean add(E item);

    /**
     * Searches target inside the tree.
     * @param target Target to search inside the tree
     * @return returns the element if found, otherwise null.
     */
    E search(E target);

    /**
     * Deletes the target from the tree.
     * @param target Data to delete from the tree.
     * @return Returns the deleted data if the item was found, otherwise null.
     */
    E delete(E target);
}
