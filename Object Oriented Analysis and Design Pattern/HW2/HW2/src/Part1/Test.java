package Part1;

import java.util.Arrays;
import java.util.concurrent.TimeUnit;

public class Test {
    public static void main(String[] args){
        long start;
        long end;

        SelectionAndCrossover roulette = new RouletteOne();
        SelectionAndCrossover tournament = new TournamentOne();
        SelectionAndCrossover rank = new RankTwo();
        GeneticAlgorithm gaRoulette = new GeneticAlgorithm(roulette);
        GeneticAlgorithm gaTourny = new GeneticAlgorithm(tournament);
        GeneticAlgorithm gaRank = new GeneticAlgorithm(rank);

        start = System.nanoTime();
        System.out.println("Roulette with One Point xover: " + Arrays.toString(gaRoulette.maximize()));
        end = System.nanoTime();
        System.out.println("Time elapsed: " + TimeUnit.NANOSECONDS.toMillis(end - start) + "ms.");

        start = System.nanoTime();
        System.out.println("Tournament with One Point xover: " + Arrays.toString(gaTourny.maximize()));
        end = System.nanoTime();
        System.out.println("Time elapsed: " + TimeUnit.NANOSECONDS.toMillis(end - start) + "ms.");

        start = System.nanoTime();
        System.out.println("Rank with Two Point xover: " + Arrays.toString(gaRank.maximize()));
        end = System.nanoTime();
        System.out.println("Time elapsed: " + TimeUnit.NANOSECONDS.toMillis(end - start) + "ms.");
    }
}
