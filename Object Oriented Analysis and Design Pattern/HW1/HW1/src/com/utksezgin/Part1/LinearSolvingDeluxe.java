package com.utksezgin.Part1;

/**
 * LinearSolvingDeluxe is a class for solving linear equations using various methods which can be found under Solver
 * class and new ones can be easily added as it utilizes the Strategy Design pattern.
 * In order to add a new method, you need to create a new class which extends Solver and change the solver of this class
 * by using changeSolver method or with constructor.
 * @author Azmi Utku Sezgin
 */
public class LinearSolvingDeluxe {
    Solver linearSolver;

    /**
     * Constructor that gets Solver as an input and changes the initial solving method.
     * @param initialSolver first solution method
     */
    public LinearSolvingDeluxe(Solver initialSolver){
        linearSolver = initialSolver;
    }


    /**
     * Changes the solution method
     * @param anySolver new solution method.
     */
    public void changeSolver(Solver anySolver){
        linearSolver = anySolver;
    }

    /**
     * Solves the linear equation problem with currently assigned method.
     * @param matrix the constraint matrix
     * @param eq the right-hand-side vector
     */
    public void solveProblem(double[][] matrix, double[] eq){
        linearSolver.solve(matrix, eq);
    }
}