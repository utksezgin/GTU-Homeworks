package com.hw03.utksezgin;

import java.io.File;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.security.InvalidParameterException;

/**
 * A class to store courses with useful methods to extract data from it.
 */
public class GTUCSECourse extends AbstractGTUCSCourse {

    GTUCSECourse(String courseFile){
        try {
            courseList = new LinkedList<>();
            parseCourses(courseFile);
        }
        catch(Exception e){
            System.out.println(e.toString());
        }

    }

    /**
     * Returns the course of given Code.
     * @param Code Course code
     * @return Returns the course of given Code.
     * @throws NoSuchElementException if course couldn't be found.
     */
    @Override
    public GTUCourses getByCode(String Code) throws NoSuchElementException{
        GTUCourses matchedCourse;
        for(int i=0; i<courseList.size();++i){
            if((matchedCourse = courseList.get(i)).getCourseCode().equals(Code))
                return matchedCourse;
        }
        throw new NoSuchElementException("There's no match for that Code");
    }

    /**
     * Creates a list of courses in same semester of given semester number
     * @param semester semester number.
     * @return returns a list of courses that are in the same semester.
     * @throws NoSuchElementException if there's no course in that semester.
     */
    @Override
    public LinkedList<GTUCourses> listSemesterCourses(int semester) throws NoSuchElementException{
        int courseCount = 0;
        LinkedList<GTUCourses> semesterCourses = new LinkedList<>();
        for(int i=0; i<courseList.size();++i) {
            if (courseList.get(i).getSemester() == semester) {
                ++courseCount;
                semesterCourses.add(courseList.get(i));
            }
        }
            if(courseCount >0)
                return semesterCourses;
            else
                throw new NoSuchElementException("No courses found in that semester.");
    }

    /**
     * Creates a new list from given range.
     * @param start_index start index of new list.
     * @param last_index end index of new list.
     * @return Returns created new linked list.
     * @throws InvalidParameterException if indexes are illegal/outofrange.
     */
    @Override
    public LinkedList<GTUCourses> getByRange(int start_index, int last_index) throws InvalidParameterException{
        LinkedList<GTUCourses> courseRange = new LinkedList<>();

        if(start_index <0 || start_index > courseList.size()-1 || last_index <1 || last_index>courseList.size()){
            throw new InvalidParameterException("Invalid range");
        }
        for(int i=start_index; i<last_index;++i) {
            courseRange.add(courseList.get(i));
        }

        return courseRange;
    }

    /**
     * Reads and parses information from the source file.
     * @param courseFile csv file that contains course data.
     * @throws InvalidParameterException if file is empty.
     */
    private void parseCourses(String courseFile) throws InvalidParameterException{
        String lineBuffer = "";
        String stringToInt = "";

        //New Course Variables
        int semester = 0;
        String courseCode = "";
        String courseTitle = "";
        int ectsCredit = 0;
        int gtuCredit = 0;
        String courseHTL = "";

        try{
            GTUCourses newCourse;
            File inputFile = new File(courseFile);
            Scanner scanCourse = new Scanner(inputFile, "UTF-8");
            if(scanCourse.hasNextLine())
                lineBuffer = scanCourse.nextLine(); //Skipping first line.
            else
                throw new InvalidParameterException("Empty file");

            while (scanCourse.hasNextLine()) {
                int i = 0;
                lineBuffer = scanCourse.nextLine();
                while(i<lineBuffer.length() && lineBuffer.charAt(i) != '\n' && lineBuffer.charAt(i)!='\r') {
                    //Reading Semester
                    while (lineBuffer.charAt(i)!=';' && lineBuffer.charAt(i)!=','){
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                    }
                    if(Integer.parseInt(stringToInt) <0)
                        throw new InvalidParameterException("Semester number cannot be a negative number");
                    else
                        semester = Integer.parseInt(stringToInt);
                    stringToInt = ""; //Clearing the variable.
                    ++i; //Skipping coma.
                    //Reading Course Code
                    while (lineBuffer.charAt(i)!=';' && lineBuffer.charAt(i)!=','){
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                    }
                    courseCode = stringToInt;
                    stringToInt = ""; //Clearing the variable.
                    ++i; //Skipping coma.
                    //Reading courseTitle
                    while (lineBuffer.charAt(i)!=';' && lineBuffer.charAt(i)!=','){
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                    }
                    courseTitle = stringToInt;
                    stringToInt = ""; //Clearing the variable.
                    ++i; //Skipping coma.
                    //Reading ECTSC Credit
                    while (lineBuffer.charAt(i)!=';' && lineBuffer.charAt(i)!=','){
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                    }
                    if(Integer.parseInt(stringToInt) <0)
                        throw new InvalidParameterException("Semester number cannot be a negative number");
                    else
                        ectsCredit = Integer.parseInt(stringToInt);
                    stringToInt = ""; //Clearing the variable.
                    ++i; //Skipping coma.
                    //Reading GTUCredit
                    while (lineBuffer.charAt(i)!=';' && lineBuffer.charAt(i)!=','){
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                    }
                    if(Integer.parseInt(stringToInt) <0)
                        throw new InvalidParameterException("Semester number cannot be a negative number");
                    else
                        gtuCredit = Integer.parseInt(stringToInt);
                    stringToInt = ""; //Clearing the variable.
                    ++i; //Skipping coma.
                    //Reading Course HTL
                    while ( i< lineBuffer.length() && (lineBuffer.charAt(i)!=';'  && lineBuffer.charAt(i)!=',')){
                        stringToInt += lineBuffer.charAt(i);
                        ++i;
                    }
                    courseHTL = stringToInt;
                    stringToInt = ""; //Clearing the variable.
                    ++i; //Skipping coma.
                }
                newCourse = new GTUCourses(semester, courseCode, courseTitle, ectsCredit, gtuCredit, courseHTL);
                courseList.add(newCourse);
            }
        }
        catch(Exception e){
            System.err.println(e.toString());
            e.printStackTrace();
        }
    }

    /**
     * @return size of the list.
     */
    public int size(){
        return courseList.size();
    }

    /**
     * Prints the Course informations
     */
    public void printList(){
        for(int i=0; i<courseList.size(); ++i){
            System.out.println(courseList.get(i).toString());
        }
    }

}