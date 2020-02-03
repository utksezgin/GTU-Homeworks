package ThreadsIncorporated;

/**
 * Class for calculating sum of two matrices and applies DFT on them.
 */
public class SumDFTSynchronized {
    /**
     * Calculates the sum of A and B and applies dft on result using 4 threads. Used synchronized, notifyall and wait
     * for thread-safety
     * @param A Complex matrix
     * @param B Complex matrix
     * @return DFT of A + B
     */
    public Complex[][] DFTOfSum(Complex[][] A, Complex[][] B){
        int NUM_OF_THREADS = 4;
        Complex[][] result = new Complex[A.length][A[0].length];

        Thread threadPool[] = new Thread[NUM_OF_THREADS];
        MatrixSumAndDFTSynch runnablePool[] = new MatrixSumAndDFTSynch[NUM_OF_THREADS];
        for(int i = 0; i < NUM_OF_THREADS; ++i){
            runnablePool[i] = new MatrixSumAndDFTSynch(A, B, i, result);
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

/**
 * Runnable class that threads run.
 */
class MatrixSumAndDFTSynch implements Runnable{
    Complex[][] A;
    Complex[][] B;
    Complex[][] sumResult;
    Complex[][] result;
    static final SynchronizedCounter counter = new SynchronizedCounter(4);

    int threadID;
    int startX, startY, endX, endY;


    /**
     * The part that thread will work on is calculated here,
     * @param A Complex matrix
     * @param B Complex matrix
     * @param threadID ID of the thread
     * @param outResult Result of DFT
     */
    public MatrixSumAndDFTSynch(Complex[][] A, Complex[][] B, int threadID, Complex[][] outResult){
        this.A = A;
        this.B = B;
        this.threadID = threadID;
        sumResult = new Complex[A.length][A[0].length];
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
                sumResult[i][j] = Complex.plus(A[i][j], B[i][j]);
                result[i][j] = new Complex(0, 0);
            }
        }
        //Synchronization Barrier
        System.out.println(threadID + ": Before barrier");
        synchronized(counter){
            try {
                counter.decrement();
                counter.notifyAll();
                while (counter.value() != 0) {
                    counter.wait(100);
                }
            } catch (Exception e) {
                System.out.println(e.toString());
            }
        }
        System.out.println(threadID + ": is here");
        //DFT of A+B
        double sqrtMN = Math.sqrt(result.length * result[0].length);
        for(int k = startX; k < endX; ++k){
            for(int l = startY; l < endY; ++l){
                for(int m = startX; m < endX; ++m){
                    for(int n = startY; n < endY; ++n){
                        result[k][l].re += (sumResult[m][n].re * Math.sin( 2.0 * Math.PI * (((double)l * (double)n / (double)A.length)
                                + ((double)k * (double)m / (double)A.length)))) / sqrtMN;
                        result[k][l].im -= (sumResult[m][n].im * Math.cos( 2.0 * Math.PI * (((double)l * (double)n / (double)A.length)
                                + ((double)k * (double)m / (double)A.length)))) / sqrtMN;
                    }
                }
            }
        }
        System.out.println(threadID + ": is finished");
    }
}

/**
 * Thread-safe counter that is used in synchronization barrier.
 */
class SynchronizedCounter {

    /**
     * @param counter Should be
     */
    public SynchronizedCounter(int counter){
        c = counter;
    }

    private int c = 4;

    /**
     * Decrements the counter.
     */
    public synchronized void decrement() {
        c--;
    }

    /**
     * @return Value of the counter.
     */
    public synchronized int value() {
        return c;
    }
}