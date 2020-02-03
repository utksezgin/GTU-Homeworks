package com.utksezgin.Part1;


public class Test {

    public static void main(String[] args) {
        GaussianEliminationSolver gaussianSolver = new GaussianEliminationSolver();
        MatrixInversionSolver inversionSolver = new MatrixInversionSolver();

        LinearSolvingDeluxe problemSolver = new LinearSolvingDeluxe(gaussianSolver);

        double[][] matrix = { {0, 1, 2}, {1, 2, 0}, {2, 3, 0}};
        double[] eq = { 1, 2, 0};

        System.out.println("Solving linear equation using gaussian elimination");
        problemSolver.solveProblem(matrix, eq);
        problemSolver.changeSolver(inversionSolver);
        System.out.println("Solving linear equation using matrix inversion");
        problemSolver.solveProblem(matrix, eq);
    }
}