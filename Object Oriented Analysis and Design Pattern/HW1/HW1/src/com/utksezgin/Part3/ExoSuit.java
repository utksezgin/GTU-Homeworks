package com.utksezgin.Part3;

/**
 * Exo suits fpr ZirHan A.S
 *
 * @author Azmi Utku Sezgin
 */
public interface ExoSuit {
    /**
     * Returns the cost of the suit.
     * @return cost of the suit.
     */
    public abstract int getCost();

    /**
     * Returns the weight of the suit.
     * @return Weight of the suit.
     */
    public abstract float getWeight();

    /**
     * Returns the description of the suit
     * @return Description of the suit
     */
    public abstract String getDescription();
}

/**
 * dec type Exo suit.
 */
class dec implements ExoSuit{
    @Override
    public int getCost(){
        return 500;
    }
    @Override
    public float getWeight(){
        return 25f;
    }

    @Override
    public String getDescription() {
        return "dec ";
    }
}

/**
 * ora type Exo suit
 */
class ora implements ExoSuit{
    @Override
    public int getCost(){
        return 1500;
    }

    @Override
    public float getWeight(){
        return 30f;
    }

    @Override
    public String getDescription() {
        return "ora ";
    }
}

/**
 * tor type Exo suit.
 */
class tor implements ExoSuit{
    @Override
    public int getCost(){
        return 5000;
    }
    @Override
    public float getWeight(){
        return 50f;
    }

    @Override
    public String getDescription() {
        return "tor ";
    }
}