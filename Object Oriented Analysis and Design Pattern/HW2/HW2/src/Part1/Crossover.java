package Part1;

import java.util.Random;

/**
 * Crossover method used for Genetic Algorithm.
 * Strategy Design utilized to introduce new crossover methods by creating new concrete classes.
 */
public abstract class Crossover {
    protected int POPULATION_COUNT   = 6;
    protected int CHROMOSOME_NUMBER  = 6;
    protected double crossoverChance = 0.6;

    /**
     * Applies crossover on the offsprings
     * @param offsprings Crossover to apply on.
     */
    public abstract void crossover(int[][] offsprings);
}

/**
 * Implements One point crossover.
 */
class OnePointCrossover extends Crossover{
    public void crossover(int[][] offsprings){
    for(int i = 0; i < POPULATION_COUNT/2; ++i) {
            if (Math.random() >= crossoverChance) {
                int crossPoint = new Random().nextInt(CHROMOSOME_NUMBER - 1) + 1;
                for (int j = 0; j < crossPoint; ++j) {
                    offsprings[i + 1][j] = offsprings[i][j];
                }
                for (int j = crossPoint; j < CHROMOSOME_NUMBER; ++j) {
                    offsprings[i][j] = offsprings[i + 1][j];
                }
            }
        }
    }
}

/**
 * Implements Two point crossover.
 */
class TwoPointCrossover extends Crossover{
    public void crossover(int[][] offsprings){
        for(int i = 0; i < POPULATION_COUNT/2; ++i){
            if (Math.random() >= crossoverChance) {
                int crossPoint1 = new Random().nextInt(CHROMOSOME_NUMBER - 1) + 1;
                int crossPoint2 = new Random().nextInt(CHROMOSOME_NUMBER - 1) + 1;

                while (crossPoint1 == crossPoint2)
                    crossPoint2 = new Random().nextInt(CHROMOSOME_NUMBER - 1) + 1;

                if (crossPoint2 > crossPoint1) {
                    int temp = crossPoint2;
                    crossPoint2 = crossPoint1;
                    crossPoint1 = temp;
                }

                for (int j = 0; j < crossPoint1; ++j) {
                    offsprings[i + 1][j] = offsprings[i][j];
                }
                for (int j = crossPoint1; j < crossPoint2; ++j) {
                    offsprings[i][j] = offsprings[i][j];
                }
                for (int j = crossPoint2; j < CHROMOSOME_NUMBER; ++j) {
                    offsprings[i + 1][j] = offsprings[i + 1][j];
                }
            }
        }
    }
}