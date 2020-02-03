package ThreadsIncorporated;

/**
 * Class for representing complex numbers.
 */
class Complex {
    double re;   // the real part
    double im;   // the imaginary part

    /**
     * Creates a complex number from given real and imaginary parts.
     * @param real Real part of the complex number
     * @param imag Imaginary part of the complex number
     */
    // create a new object with the given real and imaginary parts
    public Complex(double real, double imag) {
        re = real;
        im = imag;
    }

    /**
     * Gets two complex numbers and returns the sum.
     * @param a left hand side complex number
     * @param b right hand side complex number
     * @return sum of a and b
     */
    public static Complex plus(Complex a, Complex b) {
        double real = a.re + b.re;
        double imag = a.im + b.im;
        Complex sum = new Complex(real, imag);
        return sum;
    }

    /**
     * @return String representation of the complex number.
     */
    // return a string representation of the invoking Complex object
    public String toString() {
        if (im == 0) return re + "";
        if (re == 0) return im + "i";
        if (im <  0) return re + " - " + (-im) + "i";
        return re + " + " + im + "i";
    }
}