package com.hw03.utksezgin;

import java.security.InvalidParameterException;
import java.util.LinkedList;
import java.util.NoSuchElementException;

/**
 * A tag interface for GTUCSECourse.
 */
interface GTUCSECourseInterface {
    /**
     * Returns the course of given Code.
     * @param Code Course code
     * @return Returns the course of given Code.
     * @throws NoSuchElementException if course couldn't be found.
     */
    GTUCourses getByCode(String Code) throws NoSuchElementException;

    /**
     * Creates a list of courses in same semester of given semester number
     * @param semester semester number.
     * @return returns a list of courses that are in the same semester.
     * @throws NoSuchElementException if there's no course in that semester.
     */
    LinkedList<GTUCourses> listSemesterCourses(int semester) throws NoSuchElementException;

    /**
     * Creates a new list from given range.
     * @param start_index start index of new list.
     * @param last_index end index of new list.
     * @return Returns created new linked list.
     * @throws InvalidParameterException if indexes are illegal/outofrange.
     */
    LinkedList<GTUCourses> getByRange(int start_index, int last_index) throws InvalidParameterException;
}
