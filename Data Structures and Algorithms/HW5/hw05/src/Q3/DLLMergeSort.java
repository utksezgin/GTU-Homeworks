package Q3;
import java.util.*;

/** Implements the recursive merge sort algorithm. In this version, copies
 *   of the subtables are made, sorted, and then merged.
 *   @author Koffman and Wolfgang
 */

public class DLLMergeSort {
    /**
     * Sort the array using the merge sort algorithm.
     * pre: table contains Comparable objects.
     * post: table is sorted.
     *
     * @param table The array to be sorted
     */
    public static < T
            extends Comparable < T >> void sort(KWLinkedList<T> table) {
        // A table with one element is sorted already.
        if (table.size() > 1) {
            // Split table into halves.
            int halfSize = Math.round( (float)table.size() / 2);
            KWLinkedList<T> leftTable = new KWLinkedList<>();
            KWLinkedList<T> rightTable = new KWLinkedList<>();

            ListIterator<T> tableItr = table.listIterator();

            for(int i=0; tableItr.hasNext(); ++i){
                if(i < halfSize)
                    leftTable.addLast(tableItr.next());
                else
                    rightTable.addLast(tableItr.next());
            }

            // Sort the halves.
            sort(leftTable);
            sort(rightTable);

            // Merge the halves.
            merge(table, leftTable, rightTable);
        }
    }

    /**
     * Merge two sequences.
     * pre: leftSequence and rightSequence are sorted.
     * post: outputSequence is the merged result and is sorted.
     *
     * @param outputSequence The destination
     * @param leftSequence   The left input
     * @param rightSequence  The right input
     */
    private static <T
            extends Comparable<T>> void merge(KWLinkedList<T> outputSequence,
                                              KWLinkedList<T> leftSequence,
                                              KWLinkedList<T> rightSequence) {
        int i = 0; // Index into the left input sequence.
        int j = 0; // Index into the right input sequence.
        int k = 0; // Index into the output sequence.

        // While there is data in both input sequences
        while (i < leftSequence.size() && j < rightSequence.size()) {
            // Find the smaller and
            // insert it into the output sequence.
            if (leftSequence.get(i).compareTo(rightSequence.get(j)) < 0) {
                outputSequence.setIndex(k++, leftSequence.get(i++));
            } else {
                outputSequence.setIndex(k++, rightSequence.get(j++));
            }
        }
        // assert: one of the sequences has more items to copy.
        // Copy remaining input from left sequence into the output.
        while (i < leftSequence.size()) {
            outputSequence.setIndex((k++), leftSequence.get(i++));
        }
        // Copy remaining input from right sequence into output.
        while (j < rightSequence.size()) {
            outputSequence.setIndex((k++), rightSequence.get(j++));
        }
    }
}