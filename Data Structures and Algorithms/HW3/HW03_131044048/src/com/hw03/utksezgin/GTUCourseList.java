package com.hw03.utksezgin;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.NoSuchElementException;


/**
 *  Class to hide unnecessary classes, enable hidden classes and show disabled classes.
 */
public class GTUCourseList extends LinkedList{
    /**
     * ArrayList of disabled courses and their index.
     */
    private ArrayList<Integer> disabledCoursePosition;
    private ArrayList<GTUCourses> disabledCourse;

    /**
     * One parameter constructor to get course information from given Collection.
     * @param c Stores course data.
     */
    GTUCourseList(Collection c){
        super(c);
        disabledCourse = new ArrayList<>();
        disabledCoursePosition = new ArrayList<>();
    }

    /**
     * Disables a course from the list.
     * @param index position of the course.
     * @return true if course is disabled successfuly.
     * @throws IllegalArgumentException if index is out of bounds.
     */
    public boolean disable(int index) throws IllegalArgumentException{
        if(index<0 || index>this.size())
            throw new IllegalArgumentException();

        disabledCoursePosition.add(index);
        disabledCourse.add( (GTUCourses) this.remove(index) );
        return true;
    }

    /**
     * Enables a disabled course.
     * @param courseCode Code of disabled course.
     * @return Returns true if course is enabled.
     * @throws NoSuchElementException if course code is not found.
     */
    public boolean enable(String courseCode) throws NoSuchElementException{
        for(int i=0; i<disabledCourse.size(); ++i){
            if(courseCode.equals(disabledCourse.get(i).getCourseCode())){
                this.add(disabledCoursePosition.get(i), disabledCourse.get(i));
                return true;
            }
        }
        throw new NoSuchElementException("Couldn't find the disabled course.");
    }

    /**
     * Prints disabled courses.
     */
    public void showDisabled(){
        if(disabledCourse.size() < 1)
            System.out.println("There's no disabled nodes.");
        else
            System.out.println("Disabled courses:");
            for(int i=0; i<disabledCourse.size(); ++i){
                System.out.println(disabledCourse.get(i).toString());
            }
    }

    /**
     * Prints course information.
     */
    public void printList(){
        for(int i=0; i<this.size(); ++i){
            System.out.println(get(i).toString());
        }
    }
}
