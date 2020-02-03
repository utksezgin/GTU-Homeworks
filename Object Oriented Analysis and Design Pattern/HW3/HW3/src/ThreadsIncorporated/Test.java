package ThreadsIncorporated;

import java.util.Random;

public class Test {

    public static void main(String args[]){
        //Matrix size
        int MATRIX_SIZE = 128;
        Random r = new Random();
        Complex[][] A = new Complex[MATRIX_SIZE][MATRIX_SIZE];
        Complex[][] B = new Complex[MATRIX_SIZE][MATRIX_SIZE];
        for(int i=0; i<MATRIX_SIZE; ++i){
            for(int j=0; j<MATRIX_SIZE; ++j){
                A[i][j] = new Complex(r.nextInt(101), r.nextInt(101));
                B[i][j] = new Complex(r.nextInt(101), r.nextInt(101));
            }
        }


        SumDFTMutex cm = new SumDFTMutex();
        long start = System.currentTimeMillis();
        Complex[][] result = cm.DFTOfSum(A, B);
        long end = System.currentTimeMillis();


        //Print result
        /*for(int i = 0; i < result.length; ++i){
            for(int j = 0; j < result[0].length; ++j){
                System.out.println(result[i][j]);
            }
        }*/

        System.out.println(end - start + "ms");

    }
}
