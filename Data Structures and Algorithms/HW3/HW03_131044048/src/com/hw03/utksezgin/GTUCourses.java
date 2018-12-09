package com.hw03.utksezgin;

/**
 * This class stores Gebze Technical University Computer Science Engineering Course informations.
 */
public class GTUCourses {

    /**
     * Semester number.
     */
    private int semester;
    /**
     * Course code.
     */
    private String courseCode;
    /**
     * Course title.
     */
    private String courseTitle;
    /**
     * ECTS Credit number of the course.
     */
    private int ectsCredit;
    /**
     * GTU Credit number of the course.
     */
    private int gtuCredit;
    /**
     * H+T+L Information of the course.
     */
    private String courseHTL;

    /**
     * Copy constructor
     * @param course Course to get data from.
     */
    GTUCourses(GTUCourses course){
        this.semester = course.getSemester();
        this.courseCode = course.getCourseCode();
        this.courseTitle = course.getCourseTitle();
        this.ectsCredit = course.getEctsCredit();
        this.gtuCredit = course.gtuCredit;
        this.courseHTL = course.courseHTL;
    }

    /**
     * Creates a new course with given input.
     * @param semester Semester No.
     * @param courseCode Course Code.
     * @param courseTitle Course Title.
     * @param ectsCredit ECTS Credit.
     * @param gtuCredit GTU Credit.
     * @param courseHTL Course HTL Info.
     */
    GTUCourses(int semester, String courseCode, String courseTitle, int ectsCredit, int gtuCredit, String courseHTL){
        this.semester = semester;
        this.courseCode = courseCode;
        this.courseTitle = courseTitle;
        this.ectsCredit = ectsCredit;
        this.gtuCredit = gtuCredit;
        this.courseHTL = courseHTL;
    }

    /**
     * Getter for semester.
     * @return Returns semester.
     */
    public int getSemester() {
        return semester;
    }

    /**
     * Getter for Course code.
     * @return Returns course code of the course.
     */
    public String getCourseCode() {
        return courseCode;
    }

    /**
     * Getter for CourseTıtle
     * @return Returns course title of the course.
     */
    public String getCourseTitle() {
        return courseTitle;
    }

    /**
     * Getter for ectsCredit
     * @return Returns ECTS Credit number of the course.
     */
    public int getEctsCredit() {
        return ectsCredit;
    }

    /**
     * Getter for gtuCredit
     * @return Returns GTU Credit number of the course.
     */
    public int getGtuCredit() {
        return gtuCredit;
    }

    /**
     * Getter for courseHTL
     * @return Returns course H+T+L information
     */
    public String getCourseHTL() {
        return courseHTL;
    }

    @Override
    public String toString() {
        return "Semester: " + semester + " Course Code: " + courseCode + " Course Title: " + courseTitle + " ECTS Credit: "
                + ectsCredit + " GTU Credit: " + gtuCredit + " Course H+T+L: " + courseHTL;
    }

    @Override
    public boolean equals(Object object){
        if(object == null)
            return false;
        GTUCourses course = (GTUCourses) object;

        if(this.semester == course.getSemester()
                && this.courseCode.equals(course.getCourseCode())
                && this.courseTitle.equals(course.getCourseTitle())
                && this.ectsCredit == course.getEctsCredit()
                && this.gtuCredit == course.getGtuCredit()
                && this.courseHTL.equals(course.getCourseHTL()))
            return true;
        else
            return false;
    }
}
