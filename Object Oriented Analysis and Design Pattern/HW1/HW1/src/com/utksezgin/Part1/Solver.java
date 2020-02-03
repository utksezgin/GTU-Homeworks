package com.utksezgin.Part1;


/**
 *Extend this class for impelementing new methods for solving linear equations.
 */
public interface Solver {
    public void solve(double[][] matrix, double[] eq);
}


/**
 *Gaussian Elimination method
 */
class GaussianEliminationSolver implements Solver{
    /**
     * Gaussian Elimination Method for solving linear equations.
     * This method is not actually imlemented!!!!
     * @param matrix the constraint matrix
     * @param eq the right-hand-side vector
     */
    public void solve(double[][] matrix, double[] eq){
        System.out.println("Solution powered by gaussian Elimination method\n");
    }
}

/**
 * Matrix Inversion method
 */
class MatrixInversionSolver implements Solver{
    /**
     * Matrix Inversion method for solving linear equations.
     * This method is not actually imlemented!!!!
     * @param matrix the constraint matrix
     * @param eq the right-hand-side vector
     */
    public void solve(double[][] matrix, double[] eq){
        System.out.println("Solution powered by Matrix Inversion method\n");
    }
}