package Q4;

import Q3.DLLMergeSort;
import Q3.KWLinkedList;
import Q5.HeapSort;
import Q5.InsertionSort;
import Q5.MergeSort;
import Q5.QuickSort;

import java.util.Random;

public class Main {
        public static void main(String[] args) {
            //******************************************************************************************//
            //I couldn't get double array working so i had to do it this way as i didn't have much time.//
            //******************************************************************************************//
            int arrayCount = 10;
            int testCount = 10;
            Integer[] arraySizes = new Integer[] {5, 10, 25, 50, 100, 250, 500, 1000, 2500, 5000};
            Integer[] testArray0 = new Integer[arraySizes[0]];
            Integer[] testArray1 = new Integer[arraySizes[1]];
            Integer[] testArray2 = new Integer[arraySizes[2]];
            Integer[] testArray3 = new Integer[arraySizes[3]];
            Integer[] testArray4 = new Integer[arraySizes[4]];
            Integer[] testArray5 = new Integer[arraySizes[5]];
            Integer[] testArray6 = new Integer[arraySizes[6]];
            Integer[] testArray7 = new Integer[arraySizes[7]];
            Integer[] testArray8 = new Integer[arraySizes[8]];
            Integer[] testArray9 = new Integer[arraySizes[9]];
            long mergeDLLAvg = 0;
            long mergeAvg = 0;
            long heapAvg = 0;
            long insertionAvg = 0;
            long quickAvg = 0;
            long timeBefore, timeAfter;
            Integer[] tempArr;

            //Array0
            for(int j=0; j<arraySizes[0]; ++j){
                Random rngNum = new Random();
                testArray0[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array1
            for(int j=0; j<arraySizes[1]; ++j){
                Random rngNum = new Random();
                testArray1[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array2
            for(int j=0; j<arraySizes[2]; ++j){
                Random rngNum = new Random();
                testArray2[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array3
            for(int j=0; j<arraySizes[3]; ++j){
                Random rngNum = new Random();
                testArray3[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array4
            for(int j=0; j<arraySizes[4]; ++j){
                Random rngNum = new Random();
                testArray4[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array5
            for(int j=0; j<arraySizes[5]; ++j){
                Random rngNum = new Random();
                testArray5[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array6
            for(int j=0; j<arraySizes[6]; ++j){
                Random rngNum = new Random();
                testArray6[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array7
            for(int j=0; j<arraySizes[7]; ++j){
                Random rngNum = new Random();
                testArray7[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array8
            for(int j=0; j<arraySizes[8]; ++j){
                Random rngNum = new Random();
                testArray8[j] = Math.abs(rngNum.nextInt())%5000;
            }
            //Array9
            for(int j=0; j<arraySizes[9]; ++j){
                Random rngNum = new Random();
                testArray9[j] = Math.abs(rngNum.nextInt())%5000;
            }

            //Sortings
            Integer[] inputArrays[] = new Integer[arrayCount][];
            inputArrays[0] = testArray0;
            inputArrays[1] = testArray1;
            inputArrays[2] = testArray2;
            inputArrays[3] = testArray3;
            inputArrays[4] = testArray4;
            inputArrays[5] = testArray5;
            inputArrays[6] = testArray6;
            inputArrays[7] = testArray7;
            inputArrays[8] = testArray8;
            inputArrays[9] = testArray9;


            //HeapSort
            for(int i=0; i<arrayCount; ++i){
                for(int j=0; j<testCount; ++j){
                    tempArr = inputArrays[j].clone();
                    timeBefore = System.nanoTime();
                    HeapSort.sort(tempArr);
                    timeAfter = System.nanoTime();
                    heapAvg += timeAfter - timeBefore;
                }
            }
            heapAvg = heapAvg/(arrayCount*testCount);

            //InsertSort
            for(int i=0; i<arrayCount; ++i){
                for(int j=0; j<testCount; ++j){
                    tempArr = inputArrays[i].clone();
                    timeBefore = System.nanoTime();
                    InsertionSort.sort(tempArr);
                    timeAfter = System.nanoTime();
                    insertionAvg += timeAfter - timeBefore;
                }
            }
            insertionAvg = insertionAvg/(arrayCount*testCount);

            //Merge Sort
            for(int i=0; i<arrayCount; ++i){
                for(int j=0; j<testCount; ++j){
                    tempArr = inputArrays[i].clone();
                    timeBefore = System.nanoTime();
                    MergeSort.sort(tempArr);
                    timeAfter = System.nanoTime();
                    mergeAvg += timeAfter - timeBefore;
                }
            }
            mergeAvg = mergeAvg/(arrayCount*testCount);

            KWLinkedList<Integer> dll = new KWLinkedList<>();
            //Merge Sort
            for(int i=0; i<arrayCount; ++i){
                for(int j=0; j<testCount; ++j){
                    tempArr = inputArrays[i].clone();
                    dll = new KWLinkedList<>();
                    dll.putArray(tempArr);
                    timeBefore = System.nanoTime();
                    DLLMergeSort.sort(dll);
                    timeAfter = System.nanoTime();
                    mergeDLLAvg += timeAfter - timeBefore;
                }
            }
            mergeDLLAvg = mergeDLLAvg/(arrayCount*testCount);

            //Quick Sort
            for(int i=0; i<arrayCount; ++i){
                for(int j=0; j<testCount; ++j){
                    tempArr = inputArrays[i].clone();
                    timeBefore = System.nanoTime();
                    QuickSort.sort(tempArr);
                    timeAfter = System.nanoTime();
                    quickAvg += timeAfter - timeBefore;
                }
            }
            quickAvg = quickAvg/(arrayCount*testCount);

            System.out.println("Average runtimes for 5 sorting algorithms calculated for 10 different sizes in 10 different runs.\n");
            System.out.println("Heap Sort Average runtime: " + heapAvg);
            System.out.println("Insertion Sort Average runtime: " + insertionAvg);
            System.out.println("Merge Sort Average runtime: " + mergeAvg);
            System.out.println("Merge Sort for DLL Average runtime: " + mergeDLLAvg);
            System.out.println("quick Sort Average runtime: " + quickAvg);
        }
}
