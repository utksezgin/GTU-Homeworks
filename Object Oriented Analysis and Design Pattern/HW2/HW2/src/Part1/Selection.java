package Part1;

import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

/**
 * Selection method used for Genetic Algorithm.
 * Strategy Design utilized to introduce new selection methods by creating new concrete classes.
 */
public abstract class Selection {
    protected int POPULATION_COUNT   = 6;
    protected int CHROMOSOME_NUMBER  = 6; // 3 for x1 3 for x2 as we need 3 bits for representing 5

    /**
     * Selects offsprings from the population.
     * @param population population to select from.
     * @param fitness fitness array of the population.
     * @return returns offsprings.
     */
    public abstract int[][] selection(int[][] population, int[] fitness);
}

/**
 * Implements roulette selection.
 */
class RouletteSelection extends Selection{

    public int[][] selection(int[][] population, int[] fitness) {
        int totalFitness = 0;
        double probability[] = new double[POPULATION_COUNT];
        for(int i = 0; i < POPULATION_COUNT; ++i){
            if(fitness[i] > 0){
                totalFitness += fitness[i];
            }
        }
        for(int i = 0; i < POPULATION_COUNT; ++i){
            if(fitness[i] <= 0){
                probability[i] = 0;
            }
            else{
                probability[i] = (double)(fitness[i]) / (double)(totalFitness);
            }
        }
        int offsprings[][] = new int[POPULATION_COUNT][CHROMOSOME_NUMBER];
        int i = 0;
        while(i < POPULATION_COUNT) {
            double r = Math.random();
            for(int j=0; j<POPULATION_COUNT; ++j){
                if(probability[j] >= r){
                    offsprings[i] = population[i];
                    ++i;
                    break;
                }
            }
        }
        return offsprings;
    }
}


/**
 * Implements Tournament selection.
 */
class TournamentSelection extends Selection{
    int NUM_OF_CHAMPIONS = 3; //This is referred as k in most of the sources on this topic.
    int offsprings[][] = new int[POPULATION_COUNT][CHROMOSOME_NUMBER];
    int arena[] = new int[NUM_OF_CHAMPIONS];
    public int[][] selection(int[][] population, int[] fitness) {
        for(int i = 0; i<POPULATION_COUNT; ++i){
            for(int j = 0; j<NUM_OF_CHAMPIONS; ++j){
                arena[j] = new Random().nextInt(NUM_OF_CHAMPIONS);
            }
            int best = Integer.MAX_VALUE * -1;
            int indexOfBest = -1;
            for(int j = 0; j<NUM_OF_CHAMPIONS; ++j ){
                if(fitness[arena[j]] > best){
                    best = fitness[arena[j]];
                    indexOfBest = arena[j];
                }
            }
            offsprings[i] = population[indexOfBest];
        }
        return offsprings;
    }
}


/**
 * Implements Rank selection.
 */
class RankSelection extends Selection{
    public int[][] selection(int[][] population, int[] fitness) {
        int offsprings[][] = new int[POPULATION_COUNT][CHROMOSOME_NUMBER];
        int[] sortedFitness = new int[POPULATION_COUNT];
        int[] rankArray = new int[POPULATION_COUNT];
        System.arraycopy(fitness, 0, sortedFitness, 0, POPULATION_COUNT);
        Arrays.sort(sortedFitness);
        List<Integer> tempList = Arrays.stream(fitness).boxed().collect(Collectors.toList());
        for(int i = 0; i<POPULATION_COUNT; ++i){
            int index = tempList.indexOf(sortedFitness[i]);
            rankArray[index] = sortedFitness[i];
        }
        int sumOfRanks = (POPULATION_COUNT+1) * POPULATION_COUNT / 2; //Sum of ranks from 1 to POPULATION_COUNT

        int i = 0;
        while(i < POPULATION_COUNT) {
            double r = Math.random();
            for(int j=0; j<POPULATION_COUNT; ++j){
                if( (double)(rankArray[j])/(double)(sumOfRanks) >= r){
                    offsprings[i] = population[i];
                    ++i;
                    break;
                }
            }
        }

        return offsprings;
    }
}