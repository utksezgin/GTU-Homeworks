package com.hw03.utksezgin;

import java.util.LinkedList;

public class courseTest {

    public static void main(String Args[]){
        try{
            LinkedList<GTUCourses> testList;
            System.out.println("----------Testing Part1----------");
            System.out.println();
            GTUCSECourse coursesTest = new GTUCSECourse("./Resources/Courses.csv");
            System.out.println("Complete list of courses:");
            coursesTest.printList();
            System.out.println();
            System.out.println("Testing getByCode method with CSE101 code:");
            System.out.println(coursesTest.getByCode("CSE 101").toString());
            System.out.println();
            System.out.println("Testing listSemesterCourses Method:");
            testList = coursesTest.listSemesterCourses(5);
            for(int i=0;i<testList.size();++i)
                System.out.println(testList.get(i).toString());
            System.out.println();
            System.out.println("Testing getByRange method from 8 to 15:");
            testList = coursesTest.getByRange(8, 15);
            for(int i=0;i<testList.size();++i)
                System.out.println(testList.get(i).toString());

            System.out.println();
            System.out.println("----------Testing Part2----------");
            System.out.println();
            //Testing disable/showDisabled/Enable
            GTUCourseList modifiedList = new GTUCourseList(coursesTest.getByRange(0, 8));
            System.out.println("List before disabling:");
            modifiedList.printList();
            modifiedList.disable(2);
            System.out.println("List after disabling:");
            modifiedList.printList();
            modifiedList.showDisabled();
            System.out.println();
            modifiedList.enable("CSE 107");
            System.out.println("List after enabling the node back");
            modifiedList.printList();
            System.out.println();


            System.out.println("----------Testing Part3----------");
            System.out.println();
            //*******Add Method used in the constructor of this class*******
            MyLinkedList myList = new MyLinkedList(coursesTest.getByRange(0, 15));
            while(myList.hasNext()){
                System.out.println(myList.next().toString());
            }
            System.out.println();
            System.out.println("Removing CSE 107 from the list");
            myList.remove(coursesTest.getByCode("CSE 107"));
            myList.printList();
            System.out.println();
            System.out.println("List Size: " + myList.size());

        }
        catch (Exception e){
            e.printStackTrace();
            System.out.println(e.toString());
        }
    }
}
