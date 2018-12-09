package com.hw4.Utku;

public class TreeTest {
    public static void main(String args[]){
        GTUBinarySearchTree<Integer> tree1 = new GTUBinarySearchTree<>();
        GTUBinarySearchTree<Integer> tree2 = new GTUBinarySearchTree<>();

        tree1.postOrderAdd(null,10);
        tree1.postOrderAdd(10,5);
        tree1.postOrderAdd(10,15);
        tree1.postOrderAdd(15,20);
        tree1.postOrderAdd(20,30);
        tree1.postOrderAdd(10,12);
        tree1.postOrderAdd(30,40);
        tree1.postOrderAdd(20,41);
        tree1.postOrderAdd(10,13);
        tree1.postOrderAdd(10,7);
        tree1.postOrderAdd(15,100);
        tree1.postOrderAdd(41,0);
        tree1.postOrderAdd(4561,42); //Should fail.


        tree2.levelOrderAdd(null, 10);
        tree2.levelOrderAdd(10, 6);
        tree2.levelOrderAdd(10, 3);
        tree2.levelOrderAdd(6, 5);
        tree2.levelOrderAdd(6, 10);
        tree2.levelOrderAdd(3, 20);
        tree2.levelOrderAdd(5, 15);
        tree2.levelOrderAdd(20, 12);
        tree2.levelOrderAdd(15, 35);
        tree2.levelOrderAdd(15, 88);
        tree2.levelOrderAdd(12, 21);
        tree2.levelOrderAdd(10, 8);
        tree1.postOrderAdd(4561,42); //Should fail.

        System.out.println("Tree1 Pre-order from main: \n" + tree1);
        System.out.println("Tree2 Pre-order from main: \n" + tree2);

        //Remove these comments and the comment from postOrderTraversal method to test ***
        /*System.out.println("Tree1 Pre-order: \n" + tree1 + "\nPost Order Test");
        tree1.postOrderSearch(tree1, 42); // Searching for an item that doesn't exist so that it can go through every item  */

        //Remove these comments and the comment from levelOrderTraversal to test levelOrderSearch ***
        /*System.out.println("Tree2 Pre-order: \n" + tree2 + "\nLevel Order Test");
        tree2.levelOrderSearch(tree2, 35); // Searching for an item that doesn't exist so that it can go through every item */
    }
}
