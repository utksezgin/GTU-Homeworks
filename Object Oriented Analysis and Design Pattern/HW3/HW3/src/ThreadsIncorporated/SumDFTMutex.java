package ThreadsIncorporated;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Class for calculating sum of two matrices and applies DFT on them.
 */
public class SumDFTMutex {
    /**
     * Calculates the sum of A and B and applies dft on result using 4 threads. Used mutex, condition variable,
     * signalAll and awaitNanos
     * @param A Complex matrix
     * @param B Complex matrix
     * @return DFT of A + B
     */
    public Complex[][] DFTOfSum(Complex[][] A, Complex[][] B){
        int NUM_OF_THREADS = 4;
        Complex[][] result = new Complex[A.length][A[0].length];

        Thread threadPool[] = new Thread[NUM_OF_THREADS];
        MatrixSumAndDFTMutex runnablePool[] = new MatrixSumAndDFTMutex[NUM_OF_THREADS];
        for(int i = 0; i < NUM_OF_THREADS; ++i){
            runnablePool[i] = new MatrixSumAndDFTMutex(A, B, i, result);
            threadPool[i] = new Thread(runnablePool[i]);
        }
        for(int i = 0; i < NUM_OF_THREADS; ++i){
            threadPool[i].start();
        }
        try {
            for (int i = 0; i < NUM_OF_THREADS; ++i) {
                threadPool[i].join();
            }
        }
        catch(Exception e){
            e.printStackTrace();
        }
        return result;
    }
}
//Every thread has gets 1 mutex, notifies all and waits for all.
/**
 * Runnable class that threads run.
 */
class MatrixSumAndDFTMutex implements Runnable{
    Complex[][] A;
    Complex[][] B;
    Complex[][] result;
    private static final nonSynchronizedCounter counter = new nonSynchronizedCounter(4);
    private final Lock mutex = new ReentrantLock();
    private final Condition barrierReached = mutex.newCondition();

    int threadID;
    int startX, startY, endX, endY;

    /**
     * The part that thread will work on is calculated here,
     * @param A Complex matrix
     * @param B Complex matrix
     * @param threadID ID of the thread
     * @param outResult Result of DFT
     */
    public MatrixSumAndDFTMutex(Complex[][] A, Complex[][] B, int threadID, Complex[][] outResult){
        this.A = A;
        this.B = B;
        this.threadID = threadID;
        result = outResult;
        startX = threadID%2 * result.length / 2;
        startY = (int)(threadID/2.0) * result.length / 2;
        endX = startX + result.length / 2;
        endY = startY + result.length / 2;
    }

    public void run() {
        //Matrix Sum Stage.
        for (int i = 0; i < A.length; ++i) {
            for (int j = 0; j < A[0].length; ++j) {
                result[i][j] = Complex.plus(A[i][j], B[i][j]);
            }
        }

        //Synchronization Barrier
        try {
            mutex.lock();
            counter.decrement();
            barrierReached.signalAll();
            while (counter.value() != 0) {
                barrierReached.awaitNanos(100);
            }
            mutex.unlock();
        }
        catch(Exception e) {
            System.out.println(e.toString());
        }

        //DFT of A+B
        double sqrtMN = Math.sqrt(result.length * result[0].length);
        for(int k = startX; k < endX; ++k){
            for(int l = startY; l < endY; ++l){
                for(int m = startX; m < endX; ++m){
                    for(int n = startY; n < endY; ++n){
                        result[k][l].re += (result[m][n].re * Math.sin( 2.0 * Math.PI * (((double)l * (double)n / (double)A.length)
                                + ((double)k * (double)m / (double)A.length)))) / sqrtMN;
                        result[k][l].im -= (result[m][n].im * Math.cos( 2.0 * Math.PI * (((double)l * (double)n / (double)A.length)
                                + ((double)k * (double)m / (double)A.length)))) / sqrtMN;
                    }
                }
            }
        }
    }
}

/**
 * Thread-safe counter that is used in synchronization barrier.
 */
class nonSynchronizedCounter {

    public nonSynchronizedCounter(int counter){
        c = counter;
    }

    private int c = 4;

    /**
     * Decrements the counter.
     */
    public void decrement() {
        c--;
    }

    /**
     * @return Value of the counter.
     */
    public int value() {
        return c;
    }
}

