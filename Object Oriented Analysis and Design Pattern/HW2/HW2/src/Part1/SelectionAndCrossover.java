package Part1;

import java.util.Arrays;

/**
 * Abbstract Template method class to easily implement multiple crossover selection combinations.
 * The crossover and selection methods utilizes strategy design pattern to introduce new methods.
 * In order to add a new combination of selection and crossover, create a new concrete class and give it's constructor
 * desired Selection and Crossover objects as parameter.
 */
public abstract class SelectionAndCrossover {
    private Crossover crossover;
    private Selection selection;

    /**
     * @param s selection method.
     * @param c crossover method.
     */
    public SelectionAndCrossover(Selection s, Crossover c){
        selection = s;
        crossover = c;
    }

    /**
     * Template method which first selects then applies crossover to create offsprings.
     * @param population population to create offspring from.
     * @param fitness fitness array of the population.
     * @return Mew offsprings.
     */
    int[][] crossAndSelect(int[][] population, int[] fitness){
        int[][] offsprings = applySelection(population, fitness);
        applyCrossover(offsprings);
        return offsprings;
    }

    /**
     * Applies selection on the population.
     * @param population population to select offsprings from.
     * @param fitness fitness array of the population.
     * @return returns selected offsprings.
     */
    public  int[][] applySelection(int[][] population, int[] fitness){
        return selection.selection(population, fitness);
    }

    /**
     * Applies crossover onto the population. The parameter is us
     * @param offsprings population to crossover.
     */
    public  void applyCrossover(int[][] offsprings){
        crossover.crossover(offsprings);
    }

}

/**
 * Applies Roulette Selection and One point crossover.
 */
class RouletteOne extends SelectionAndCrossover{
    public RouletteOne() {
        super(new RouletteSelection(), new OnePointCrossover());
    }
}

/**
 * Applies Rank Selection and Two point crossover.
 */
class RankTwo extends SelectionAndCrossover{
    public RankTwo() {
        super(new RankSelection(), new TwoPointCrossover());
    }
}

/**
 * Applies Tournament Selection and One point crossover.
 */
class TournamentOne extends SelectionAndCrossover{
    public TournamentOne() {
        super(new TournamentSelection(), new OnePointCrossover());
    }
}