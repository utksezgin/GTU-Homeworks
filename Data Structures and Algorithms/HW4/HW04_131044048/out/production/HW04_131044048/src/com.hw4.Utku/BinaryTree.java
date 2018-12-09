package com.hw4.Utku;

/**
 * Abstract Binary Tree Class
 * @param <E>
 */
public abstract class BinaryTree<E extends Comparable<E>> {
    /**
     * @return Returns left child of the tree.
     */
    public abstract BinaryTree<E> getLeftSubTree();

    /**
     * @return Returns the right child of the tree.
     */
    public abstract BinaryTree<E> getRightSubTree();

    /**
     * @return Returns the value of root of the tree.
     */
    public abstract E data();
}
