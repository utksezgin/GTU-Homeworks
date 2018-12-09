package Q3;

public class Main {

    public static void main(String[] args){
        //Initializing a dll.
        KWLinkedList<Integer> mergeSortDLL = new KWLinkedList<>();
        mergeSortDLL.addLast(10);
        mergeSortDLL.addLast(50);
        mergeSortDLL.addLast(230);
        mergeSortDLL.addLast(0);
        mergeSortDLL.addLast(560);
        mergeSortDLL.addLast(23);
        mergeSortDLL.addLast(16);
        mergeSortDLL.addLast(20);
        mergeSortDLL.addLast(65);
        mergeSortDLL.addLast(6);
        long avgTime = 0;
        int runCount = 10;
        long time1;
        long time2;
        for(int i =0; i<runCount; ++i) {
            time1 = System.nanoTime();
            DLLMergeSort.sort(mergeSortDLL);
            time2 = System.nanoTime();
            System.out.println("Run Time : " + (time2-time1) );
            avgTime+= time2-time1;
        }
        avgTime = avgTime/runCount;
        System.out.println("Running time of merge sorting for Double Linked List with size of 10 is " + avgTime
        + " nanoseconds.");
    }
}
