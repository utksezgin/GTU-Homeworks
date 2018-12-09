package com.hw4.Utku;

import java.util.LinkedList;
/**
 * This class is a binary tree representation of general trees in java. Every node can have multiple children.
 * It implements toString() method and prints the tree in pre order traversal.
 * @param <E> Type of value in tree. **Needs to be Comparable.
 */
public class GTUBinarySearchTree<E extends Comparable<E>> extends BinaryTree<E>{
    /**
     * Root of the tree.
     */
    private Node<E> root;
    private boolean isPostFound;
    private Node<E> postNode;


    /**
     * Node class represents nodes in tree. toString() method is overloaded and returns the value of Node in string.
     * @param <E> Type of value in Node. **Must be Comparable.
     */
    private static class Node<E extends Comparable<E>>{

        /**
         * Value of node.
         */
        private E data;
        /**
         * Left child of the node.
         */
        private Node<E> leftChild;
        /**
         * Right child of the node.
         */
        private Node<E> rightChild;

        /**
         * No parameter constructor. All of the data field set to null.
         */
        Node(){
            this.data = null;
            this.leftChild = null;
            this.rightChild = null;
        }

        /**
         * Creates a Node with given value.
         * @param data Value of the node.
         */
        Node(E data){
            this.data = data;
            this.leftChild = null;
            this.rightChild = null;
        }

        /**
         * Creates copy of the given node.
         * @param n node to copy.
         */
        Node(Node<E> n){
            this.data = n.data;
            this.leftChild = n.leftChild;
            this.rightChild = n.rightChild;
        }

        /**
         * Creates a string with the value of node in it.
         * @return Returns the value of Node in string.
         */
        @Override
        public String toString(){
            return this.data.toString();
        }
    }

    /**
     * Noparameter constructor creates an empty tree.
     */
    //Constructors
    GTUBinarySearchTree(){
        root = null;
        isPostFound = false;
        postNode = null;
    }

    /**
     * Creates a tree that has same root as given tree.
     * @param root Tree to get root from.
     */
    GTUBinarySearchTree(GTUBinarySearchTree root){
        this.root = root.root;
        isPostFound = false;
    }

    /**
     * Creates a tree with root with given value and no children.
     * @param item Value of root node.
     */
    GTUBinarySearchTree(E item){
        root = new Node<>(item);
        isPostFound = false;
    }

    /**
     * Creates a root with given node.
     * @param root New tree's node.
     */
    GTUBinarySearchTree(Node<E> root){
        this.root = root;
        isPostFound = false;
    }

    /**
     * Creates a tree with root and 2 children. Root's value is data and left, right children are leftTree and rightTree respectively.
     * @param data Value of the root node.
     * @param leftTree left child.
     * @param rightTree right child.
     */
    public GTUBinarySearchTree(E data, GTUBinarySearchTree < E > leftTree, GTUBinarySearchTree < E > rightTree) {
        root = new Node < E > (data);
        root.leftChild = leftTree.root;
        root.rightChild = rightTree.root;
    }


    /**
     * Helper method for levelOrderAdd and postOrderAdd. After those methods finds the node of the given item,
     * they call this method to insert the given value to the tree.
     * @param localRoot Node or branch to add the value.
     * @param childItem Value of the new node.
     * @return returns true if the insertion was successful.
     */
    private boolean add(Node<E> localRoot, E childItem){
        if(localRoot == null)
            return false;
        if(localRoot.leftChild == null){
            localRoot.leftChild = new Node<>(childItem);
            return true;
        }
        else{
            Node<E> tempNode = localRoot.leftChild;
            while(tempNode.rightChild != null)
                tempNode = tempNode.rightChild;
            tempNode.rightChild = new Node<>(childItem);
            return true;
        }
    }

    /**
     * Finds the location of parentItem via level order traversal, if it doesn't exist, returns false else inserts the
     * new node with the value of childItem.
     * @param parentItem Value of the node to make insertion.
     * @param childItem Value to insert to the tree.
     * @return
     */
    public boolean levelOrderAdd(E parentItem, E childItem){
        if(root == null) {
            root = new Node<>(childItem);
            return true;
        }
        else if(parentItem == null){
            System.out.println("Invalid parent item.");
            return false;
        }

        Node<E> tempNode = levelOrderTraversal(root, parentItem);
        if(tempNode == null){
            System.out.println("Failed to add " + childItem + " to tree\n" + this.toString());
            return false;
        }

        if(add(tempNode, childItem)) {
            System.out.println(childItem + " successfully added to tree, new overview: \n" + toString());
            return true;
        }
        else
            return false;
    }

    /**
     * Finds the location of parentItem via post order traversal, if it doesn't exist, returns false else inserts the
     * new node with the value of childItem.
     * @param parentItem Value of the node to make insertion.
     * @param childItem Value to insert to the tree.
     * @return
     */
    public boolean postOrderAdd(E parentItem, E childItem){
        if(root == null) {
            root = new Node<>(childItem);
            return true;
        }
        else if(parentItem == null) {
            System.out.println("Invalid parent item.");
            return false;
        }
        Node<E> tempNode;
        if(postOrderTraversal(root, parentItem))
            tempNode = postNode;
        else
            tempNode = null;


        if(tempNode == null){
            System.out.println("Failed to add " + childItem + " to tree\n" + this.toString());
            return false;
        }
        else
            System.out.println(tempNode.toString());

        if(add(tempNode, childItem)){
            postNode = null;
            isPostFound = false;
            System.out.println(childItem + " successfully added to tree, new overview: \n" + toString());
            return true;
        }
        else
            return false;
    }

    /**
     * @return Returns the left child of the tree.
     */
    @Override
    public BinaryTree<E> getLeftSubTree(){
        if(root != null & root.leftChild != null)
            return new GTUBinarySearchTree<E>(root.leftChild);
        else
            return null;
    }

    /**
     * @return Returns the right child of the tree.
     */
    @Override
    public BinaryTree<E> getRightSubTree(){
        if(root != null & root.rightChild != null)
            return new GTUBinarySearchTree<E>(root.rightChild);
        else
            return null;
    }

    /**
     * @return returns the value of root of the tree.
     */
    @Override
    public E data(){
        if(root!=null)
            return root.data;
        else
            return null;
    }

    /**
     * @return Returns true if tree has no child.
     */
    public boolean isLeaf(){
        if(root.leftChild == null && root.rightChild == null)
            return true;
        else
            return false;
    }

    /**
     * Converts tree into string in pre order.
     * @return Returns a string with values of tree in pre order
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 1, sb);
        return sb.toString();
    }

    /**
     * Traverses through the tree in pre order and creates a string of the tree in pre order. Helper for toString method.
     * @param node Root node of the tree.
     * @param depth Spaces between values and levels.
     * @param sb String representation of the tree.
     */
    private void preOrderTraverse(Node <E> node, int depth, StringBuilder sb){
        /*for(int i=1; i< depth; ++i)
            sb.append(" ");

        if (node == null)
            sb.append("null\n");*/
        if(node != null){
            sb.append(node.toString());
            sb.append(" ");
            //sb.append("\n");
            preOrderTraverse(node.leftChild, depth +1, sb);
            preOrderTraverse(node.rightChild, depth +1, sb);
        }
    }

    /**
     * Traverses through the tree in level order and searches for item, returns a new tree which starts from the found
     * item, if item doesn't exist returns null.
     * @param binaryTree Tree to search the item.
     * @param item Item to search in tree.
     * @return Returns a new tree with found item's node being the root or returns null if the item doesn't exist.
     */
    public GTUBinarySearchTree<E> levelOrderSearch(GTUBinarySearchTree<E> binaryTree, E item){
        Node<E> nodeFound = new Node<E>();
        nodeFound = levelOrderTraversal(binaryTree.root, item);
        if(nodeFound == null)
            return null;

        return new GTUBinarySearchTree<>(nodeFound);


    }

    /**
     * Traverses through the tree in post order and searches for item, returns a new tree which starts from the found
     * item, if item doesn't exist returns null.
     * @param binaryTree Tree to search the item.
     * @param item Item to search in tree.
     * @return Returns a new tree with found item's node being the root or returns null if the item doesn't exist.
     */
    public GTUBinarySearchTree postOrderSearch(GTUBinarySearchTree<E> binaryTree, E item){
        Node<E> nodeFound = postNode;
        if(postOrderTraversal(binaryTree.root, item)) {
            if (nodeFound == null)
                return null;
            else
                return new GTUBinarySearchTree<>(nodeFound);
        }
        else
            return null;

    }

    /**
     * Traverses through the tree in level order and searches the item.
     * @param localRoot root of the tree.
     * @param item Item to look for in tree.
     * @return Returns the Node of item if it's found else returns null.
     */
    private Node<E> levelOrderTraversal(Node<E> localRoot, E item){
        if(localRoot == null)
            return null;
        LinkedList<Node<E>> levelOrderList = new LinkedList<>();
        levelOrderList.push(localRoot);

        while( !levelOrderList.isEmpty() ){

            int size = levelOrderList.size();
            while(size > 0){
                Node<E> tempNode = levelOrderList.pollLast();
                //System.out.println(tempNode); //Remove '//' to test search order.
                if(item.compareTo(tempNode.data) == 0)
                    return tempNode;

                if(tempNode.leftChild != null) {
                    tempNode = tempNode.leftChild;
                    levelOrderList.push(tempNode);
                }
                while(tempNode.rightChild != null) {
                    tempNode = tempNode.rightChild;
                    levelOrderList.push(tempNode);
                }

                --size;
            }
        }

        System.out.print(item +  " not found, ");
        return null;
    }



    /**
     * Recursively traverses through the tree in post order and searches the item.
     * @param localRoot root of the tree.
     * @param item Item to look for in tree.
     * @return Returns the Node of item if it's found else returns null.
     */
    private boolean postOrderTraversal(Node<E> localRoot, E item){
        if(localRoot == null)
            return false;

        Node<E> tempNode;
        postOrderTraversal(localRoot.leftChild, item);
        postOrderTraversal(localRoot.rightChild, item);
        tempNode = localRoot;
        //System.out.println(tempNode.toString()); //Remove "//" to test search order.
        if(item.compareTo(tempNode.data) == 0){
            isPostFound = true;
            postNode = tempNode;
        }

        return isPostFound;

    }

}

