package Part1;

import java.util.Arrays;
import java.util.Random;

/**
 * Implementaion of metaheuristic Genetic Algorithm optimization method to maximize
 * f(x1, x2)=20*x1*x2 + 16*x2 −2*x1^2 −x2^2 − (x1+x2)^2 function.
 */
public class GeneticAlgorithm {

    SelectionAndCrossover selectionxover;

    /**
     * @param s Concrete class that extends SelectionAndCrossover which defines the selection and crossover behaviours.
     */
    public GeneticAlgorithm(SelectionAndCrossover s) {
        selectionxover = s;
    }

    private int POPULATION_COUNT = 6;
    private int CHROMOSOME_NUMBER = 6; // 3 for x1 3 for x2 as we need 3 bits for representing 5
    private int MAX_ITERATION_WITH_NO_CHANGE = 10;


    private double mutationChance = 1/((double)POPULATION_COUNT);
    private int population[][] = new int[POPULATION_COUNT][CHROMOSOME_NUMBER];
    private int populationInt[][] = new int[POPULATION_COUNT][2];
    private int fitness[] = new int[POPULATION_COUNT];

    /**
     * Computes the fitness.
     */
    private void computeFitness(){
        int x1 = 0;
        int x2 = 0;
        for(int i = 0; i < POPULATION_COUNT; ++i){

            x1 = populationInt[i][0];
            x2 = populationInt[i][1];
            fitness[i] = objectiveFunction(x1, x2);
        }
    }

    /**
     * @param isReturnVal a flag which changes the return type where if it's true, it returns value, index otherwise.
     * @return returns value of the Maximum of the given function from the population if the parameter is true, index otherwise.
     */
    private int getMaxOfPopulation(boolean isReturnVal){
        int currMax = Integer.MAX_VALUE * -1;
        int currMaxIndex = 0;
        int result;
        for(int i = 0; i<POPULATION_COUNT; ++i){
            result = fitness[i];
            if(result > currMax){
                currMax = result;
                currMaxIndex = i;
            }
        }
        if(isReturnVal)
            return currMax;
        else
            return currMaxIndex;
    }

    /**
     * Function to maximize -  f(x1, x2)=20*x1*x2 + 16*x2 −2*x1^2 −x2^2 − (x1+x2)^2
     * @param x1 first parameter of the function to maximize.
     * @param x2 second parameter of the function to maximize.
     * @return returns the result of the function with given parameters.
     */
    private int objectiveFunction(int x1, int x2) {
        return (20 * x1 * x2) + (16 * x2) - (2 * x1 * x1) - (x2 * x2) - ((x1 + x2) * (x1 + x2));
    }

    /**
     * Checks for the following constraints - x1+x2 &gt;= 5; 0&gt;=x1&gt;=5; 0&gt;=x2&gt;=5
     * @param x1 first parameter
     * @param x2 second parameter
     * @return returns true if the constraints are satisfied.
     */
    private boolean checkConstraint(int x1, int x2) {
        if (x1 + x2 <= 5 && x1 <= 5 && x2 <= 5)
            return true;
        return false;
    }

    /**
     * Checks if all the offsprings satisfies the constraints.
     * @param offsprings offsprings of to check.
     * @return returns true if the offsprings don't have any illegal chromosome.
     */
    private boolean checkOffspringsForConstraint(int[][] offsprings){
        String bit1;
        String bit2;
        int x1;
        int x2;
        for (int i = 0; i < POPULATION_COUNT; ++i) {
            bit1 = "";
            bit2 = "";
            bit1 += population[i][0];
            bit1 += population[i][1];
            bit1 += population[i][2];

            x1 = Integer.parseInt(bit1, 2);

            bit2 += population[i][3];
            bit2 += population[i][4];
            bit2 += population[i][5];
            x2 = Integer.parseInt(bit2, 2);
            if(!checkConstraint(x1, x2))
                return false;
        }
        return true;
    }

    /**
     * Randomly generates population. The number is POPULATION_COUNT defined in the class.
     */
    private void generatePopulation() {
        Random r = new Random();
        int x1 = 0;
        int x2 = 0;
        for (int i = 0; i < POPULATION_COUNT; ++i) {
            while(true) {
                x1 = r.nextInt(5 + 1);
                x2 = r.nextInt(5 + 1);
                if(checkConstraint(x1, x2)){
                    String s1 = Integer.toBinaryString(x1);
                    String s2 = Integer.toBinaryString(x2);
                    int k = 0;
                    for(int j = 0; j<s1.length(); ++j){
                        population[i][j+3-s1.length()] = Character.getNumericValue(s1.charAt(j));
                    }
                    k = 0;
                    for(int j = 0; j<s2.length(); ++j){
                        population[i][j+3+3-s2.length()] = Character.getNumericValue(s2.charAt(j));
                    }

                    populationInt[i][0] = x1;
                    populationInt[i][1] = x2;
                    break;
                }
            }
        }
    }

    /**
     * Replaces current population with the offsprings.
     * @param offsprings offsprings to replace population.
     */
    private void replacePopulation(int[][] offsprings) {
        population = Arrays.stream(offsprings).map(int[]::clone).toArray(int[][]::new);

        String bit1 = "";
        String bit2 = "";
        for (int i = 0; i < POPULATION_COUNT; ++i) {
            bit1 = "";
            bit2 = "";
            bit1 += offsprings[i][0];
            bit1 += offsprings[i][1];
            bit1 += offsprings[i][2];
            populationInt[i][0] = Integer.parseInt(bit1, 2);

            bit2 += offsprings[i][3];
            bit2 += offsprings[i][4];
            bit2 += offsprings[i][5];
            populationInt[i][1] = Integer.parseInt(bit2, 2);
        }
    }

    /**
     * Randomly flips the bits of offsprings with a chance.
     * @param offsprings offsprings to flip bits.
     */
    private void mutation(int[][] offsprings){
        for(int[] offspring : offsprings){
            for(int i = 0; i < CHROMOSOME_NUMBER; ++i){
                if(Math.random() < mutationChance){
                    //Bit flip
                    offspring[i] = (offspring[i]+1) % 2;
                }
            }
        }
    }

    /**
     * Public function to find maximized result of the function. Prints maximized value and returns corresponding x1 and x2.
     * @return returns an array with the size of 2 which contains x1 as it's first index and x2 as second.
     */
    public int[] maximize() {
        int currMax = Integer.MAX_VALUE * -1;
        int max1 = 0;
        int max2 = 0;
        int localMax;
        int iterationCount = 0;
        int[][] offsprings;
        generatePopulation();
        computeFitness();
        while(true){
            while(true){
                offsprings = selectionxover.crossAndSelect(population, fitness);
                mutation(offsprings);
                if(checkOffspringsForConstraint(offsprings))
                    break;
            }
            replacePopulation(offsprings);
            computeFitness();
            localMax = getMaxOfPopulation(true);
            if(currMax < localMax){
                currMax = localMax;
                max1 = populationInt[getMaxOfPopulation(false)][0];
                max2 = populationInt[getMaxOfPopulation(false)][1];
            }
            else{
                ++iterationCount;
                if(iterationCount==MAX_ITERATION_WITH_NO_CHANGE)
                    break;
            }
        }
        System.out.println("Max found: " + currMax);
        int result[] = {max1, max2};
        return result;
    }
}