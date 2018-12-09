package sample;

/**
 * This BinarySearchTree class is used for searching questions. Question class implements Comparable interface
 * so that it can search by their ID which is what makes BinarySearchTree very efficient here.
 * @param <E> Data type of the Tree nodes
 */
public class BinarySearchTree<E extends Comparable> implements BinarySearchTreeInterface<E> {
    /**
     * Root of the tree
     */
    private Node<E> root;
    /**
     * Return value of add method.
     */
    private boolean addReturn;

    /**
     * Nodes are used to store data, left and right children to create the Tree structure
     * @param <E> Data type of the node.
     */
    private static class Node<E extends Comparable>{
        private E data;
        private Node<E> left;
        private Node<E> right;

        /**
         * No parameter constructor to create an empty node.
         */
        Node(){
            this.data = null;
            this.left = null;
            this.right = null;
        }

        /**
         * Constructor that gets a data and creates a node holding that data.
         * @param data
         */
        Node(E data){
            this.data = data;
            this.left = null;
            this.right = null;
        }

        /**
         * Copy constructor that copies the values of the given node.
         * @param n Node to copy from.
         */
        Node(Node<E> n){
            this.data = n.data;
            this.left = n.left;
            this.right = n.right;
        }
    }

    /**
     * No parameter constructor that creates an empty tree.
     */
    BinarySearchTree(){
        this.root = null;
    }

    /**
     * Constructor that gets a data as parameter and creates a tree with root holding the given data.
     * @param data Value of Root on tree.
     */
    BinarySearchTree(E data){
        this.root = new Node<E>(data);
    }

    /**
     * Constructor that gets a Node as parameter and creates a Tree and sets it's Root to that Node
     * @param root Root of craeted tree.
     */
    BinarySearchTree(Node<E> root){
        this.root = root;
    }

    /**
     * Copy constructor for Tree, creates a new tree and sets root to given tree's root.
     * @param searchTree Tree to copy root from.
     */
    BinarySearchTree(BinarySearchTree<E> searchTree){
        this.root = searchTree.root;
    }


    /**
     * Adds an item to the tree. Returns true if the insertion is successful.
     * @param item Item to add into tree
     * @return Returns true if the insertion is successful, otherwise false.
     */
    @Override
    public boolean add(E item){
        root = add(root, item);
        return addReturn;
    }

    /**
     * Helper method for add which recursively finds the right place for the given item and inserts it into the tree.
     * @param localRoot Root to add the item into.
     * @param item Item to add into the tree.
     * @return Returns the Node that item inserted.
     */
    private Node<E> add(Node<E> localRoot, E item){
        if(localRoot == null){
            addReturn = true;
            return new Node<E>(item);
        }
        else if(item.compareTo(localRoot.data) == 0){
            addReturn = false;
            return localRoot;
        }
        else if(item.compareTo(localRoot.data) < 0){
            localRoot.left = add(localRoot.left, item);
            return localRoot;
        }
        else{
            localRoot.right = add(localRoot.right, item);
            return localRoot;
        }
    }

    /**
     * Performs a binary search to find target inside the tree.
     * @param target Data to search inside the tree
     * @return
     */
    @Override
    public E search(E target){
        Node<E> ret_val = search(root, target);
        if(ret_val == null)
            return null;
        return ret_val.data;
    }

    /**
     * Helper method for search which performs a binary search recursively and returns the Node of item if found.
     * @param localRoot Node to search target inside.
     * @param target Target to find inside the tree.
     * @return Returns the Node if the target is found, otherwise null.
     */
    private Node<E> search(Node<E> localRoot, E target){
        if(localRoot == null)
            return null;
        int compareResult = target.compareTo(localRoot.data);

        if(compareResult == 0)
            return localRoot;
        else if(compareResult< 0)
            return search(localRoot.left, target);
        else
            return search(localRoot.right, target);
    }


    /**
     * Deletes the target from the tree.
     * @param target Data to delete from the tree.
     * @return Returns the deleted item if the item was found, otherwise null.
     */
    @Override
    public E delete(E target){
        return delete(root, target).data;
    }

    /**
     * Helper method for delete which searches for target inside tree and deletes recursively.
     * @param localRoot Node to remove target from.
     * @param target Data to remove from tree.
     * @return Returns the node of target if found, otherwise null.
     */
    public Node<E> delete(Node<E> localRoot, E target){
        Node<E> localNode = localRoot;
        if(root == null)
            return localNode;

        if(target.compareTo(localRoot.data) < 0)
            localNode.left = delete(localNode.left, target);
        else if(target.compareTo(localRoot.data) > 0)
            localNode.right = delete(localNode.right, target);
        else{
            if(isLeaf(localRoot)){
                localNode = null;
            }
            else if(localRoot.right == null)
                localNode = localNode.left;
            else if(localRoot.left == null)
                localNode = localNode.right;
            else{
                Node<E> temp = minFromRight(localNode.right);
                localNode.data = temp.data;
                localNode.right = delete(localNode.right, temp.data);
            }
        }
        return localNode;
    }

    /**
     * Checks if the Node is a leaf. Leaf node is a node that has no children.
     * @param node Node to check if it's a leaf.
     * @return Returns true if node has no children, otherwise false.
     */
    public boolean isLeaf(Node <E> node){
        if(node.left == null && node.right == null)
            return true;
        else
            return false;
    }

    /**
     * Helper method for delete finds the Node to replace deleted Node.
     * @param node Node to start going left child.
     * @return Returns the left most node.
     */
    private Node<E> minFromRight(Node<E> node){
        while(node.left != null)
            node = node.left;

        return node;
    }

}
