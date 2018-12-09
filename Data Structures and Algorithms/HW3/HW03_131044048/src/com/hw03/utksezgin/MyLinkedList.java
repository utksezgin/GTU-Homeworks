package com.hw03.utksezgin;

import java.security.InvalidParameterException;
import java.util.LinkedList;
        import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Linked list data structure to store course data.
 */
public class MyLinkedList {
    private int size;
    private int currentNode;
    private Node headNode;
    private Node tailNode;

    //Inner Node<GTUCourses> Class
    private class Node {

        private GTUCourses courseData;
        private Node previousCourse;
        private Node nextCourse;
        private Node nextSemester;
        private Node previousInSemester;

        private Node() {
            this.courseData = null;
            this.nextCourse = null;
            this.nextSemester = null;
            this.previousInSemester = null;
            this.previousCourse = null;
        }

        private Node(Node n) {
            this.courseData = new GTUCourses(n.courseData);
            this.nextCourse = n.nextCourse;
            this.nextSemester = n.nextSemester;
            this.previousInSemester = n.previousInSemester;
            this.previousCourse = n.previousCourse;
        }

        private Node(GTUCourses course) {
            this.courseData = course;
            this.nextCourse = null;
            this.nextSemester = null;
            this.previousInSemester = null;
            this.previousCourse = null;
        }

        private Node(GTUCourses course, Node nextCourse) {
            this.courseData = course;
            this.nextCourse = nextCourse;
            this.nextSemester = null;
            this.previousCourse = null;
        }

        private Node(GTUCourses course, Node nextCourse, Node nextCourseInSemester) {
            this.courseData = course;
            this.nextCourse = nextCourse;
            this.nextSemester = nextCourseInSemester;
            this.previousCourse = null;
        }
    }

    public class courseIter implements Iterator<Node> {
        private Node currentItr;
        private Node currentSemester;

        courseIter(Node headNode) {
            if (headNode == null)
                throw new NullPointerException();
            currentItr = headNode;
        }

        public boolean hasNext() {
            if (currentItr.nextCourse != null && currentItr.nextCourse!=headNode)
                return true;
            else
                return false;
        }

        public boolean hasNextSemester() {
            if (currentItr.nextSemester != null && currentItr.nextSemester!=headNode)
                return true;
            else
                return false;
        }

        public Node next() {
            if (hasNext()) {
                Node nextNode = currentItr.nextCourse;
                currentItr = currentItr.nextCourse;
                return nextNode;
            } else
                throw new NoSuchElementException();
        }

        public Node nextSemesterCourse() {
            if (hasNextSemester()) {
                Node nextNode = currentSemester.nextSemester;
                currentItr = currentSemester.nextSemester;
                return nextNode;
            } else
                throw new NoSuchElementException();
        }
    }

    /**
     * Stores course information gathered from inputList.
     * @param inputList course information.
     */
    MyLinkedList(LinkedList<GTUCourses> inputList) {
        size = 0;
        currentNode = 0;
        if (inputList.size() < 1)
            throw new InvalidParameterException();
        try {
            Node newNode;
            headNode = new Node(inputList.get(0));
            tailNode = new Node(inputList.get(inputList.size() - 1));
            for (int i = 1; i < inputList.size() - 1; ++i) {
                newNode = new Node(inputList.get(i));
                newNode = this.add(newNode.courseData);
                get(i - 1).nextCourse = newNode;
                newNode.previousCourse = get(i - 1);
                headNode.previousCourse = tailNode;
                tailNode.nextCourse = headNode;
            }
            currentNode = 0;
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println(e.toString());
        }
    }

    /**
     * Returns an iterator which starts from the head.
     * @return returns an iterator which starts from the head.
     */
    public courseIter listIterator(){
        courseIter newIter = new courseIter(headNode);
        return newIter;
    }

    /**
     * Returns Node at given index.
     * @param index position of the desired Node.
     * @return the Node at given index.
     * @throws IllegalArgumentException If index is out of bounds.
     * @throws NullPointerException if failed to create the new Node.
     */
    private Node get(int index) throws IllegalArgumentException, NullPointerException {
        if (index < 0 || index > size())
            throw new IllegalArgumentException();
        if (index == 0)
            return headNode;
        Iterator<Node> getItr = new courseIter(headNode);
        Node newNode = new Node();
        for (int i = 0; i < index && getItr.hasNext(); ++i) {
            newNode = getItr.next();
        }
        if (newNode == null)
            throw new NullPointerException();
        return newNode;
    }

    /**
     * Adds new course to end of the list also does the linking.
     * @param newCourse course to be added.
     * @return returns the newly added Node.
     */
    private Node add(GTUCourses newCourse) { //Appends the list
        boolean isHeadFound = false;
        int currentSemester;
        Node semesterHead = null;
        Node tempNode;
        Iterator<Node> addItr = new courseIter(headNode);
        Node newNode = new Node(newCourse);
        newNode.previousCourse = new Node(tailNode);
        currentSemester = newNode.courseData.getSemester();

        //nextInSemester linking.
        courseIter semesterItr = new courseIter(headNode);
        while (semesterItr.hasNext() && isHeadFound == false) {
            tempNode = semesterItr.next();
            if (tempNode.courseData.getSemester() == currentSemester) {
                isHeadFound = true;
                semesterHead = tempNode;
            }
        }
        if (semesterHead != null) {
            semesterItr = new courseIter(semesterHead);
            tempNode = null;
            while (semesterItr.hasNextSemester()) {
                tempNode = semesterItr.nextSemesterCourse();
            }
            if (tempNode != null) {
                tempNode.nextSemester = newNode;
                headNode.previousInSemester = newNode;
                newNode.nextSemester = headNode;
            }
        }
        tailNode = newNode;
        ++size;
        return newNode;
    }

    /**
     * Removes the given course
     * @param course course to remove.
     * @return True if remove operation was successfull
     */
    boolean remove(GTUCourses course) {
        Iterator<Node> removeItr = new courseIter(headNode);
        Node courseNode;
        while (removeItr.hasNext()) {
            courseNode = removeItr.next();
            if (courseNode.courseData.equals(course)) {
                courseNode.previousCourse.nextCourse = courseNode.nextCourse;
                courseNode.nextCourse.previousCourse = courseNode.previousCourse;
                return true;
            }
        }

        return false;
    }

    /**
     * Returns true if nextCourse isn't null.
     * @return returns true if nextCourse isn't null.
     */
    public boolean hasNext() {
        if(get(currentNode).nextCourse != null && currentNode!=size()-1)
            return true;
        else
            return false;
    }

    /**
     * Returns true if NextSemester isn't null.
     * @return returns true if nextSemester isn't null.
     */
    public boolean hasNextInSemester(){
        if(get(currentNode).nextSemester == null)
            return false;
        else
            return true;
    }

    /**
     * Moves to next node in the list.
     * @return returns the next course data.
     * @throws NoSuchElementException if there's no next course.
     */
    public GTUCourses next() throws NoSuchElementException {
        if (hasNext()) {
            Node nextNode = get(currentNode);
            ++currentNode;
            if(currentNode == size())
                currentNode = 0;
            return nextNode.courseData;
        }
        else
            throw new NoSuchElementException();
    }

    /**
     * Moves to next node in same semester.
     * @return returns the next semester data.
     * @throws NoSuchElementException if there's no course in same semester.
     */
    public GTUCourses nextInSemester() throws NoSuchElementException{
        if(hasNextInSemester())
            return get(currentNode).nextSemester.courseData;
        else
            throw new NoSuchElementException();
    }

    /**
     * Returns list size.
     * @return returns list size.
     */
    public int size() {
        return size;
    }

    /**
     * Prints list data.
     */
    public void printList() {
        courseIter printIter = new courseIter(headNode);
        while (printIter.hasNext())
            System.out.println(printIter.next().courseData);
    }
}