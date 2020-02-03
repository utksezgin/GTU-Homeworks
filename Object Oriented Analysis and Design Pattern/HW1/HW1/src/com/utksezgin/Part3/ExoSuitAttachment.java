package com.utksezgin.Part3;

/**
 * Decorator class for decorating suits.
 */
public abstract class ExoSuitAttachment implements ExoSuit{
    /**
     * Reference for wrapping the suit with decorators.
     */
    protected ExoSuit suit;
    /**
     * description of the suit
     */
    protected String description = "Unknown";
    public ExoSuitAttachment(ExoSuit s){ suit = s;}

    /**
     * @return Cost of the decorator-wrapped suit.
     */
    public abstract int getCost();

    /**
     * @return Weight of the decorator-wrapped suit.
     */
    public abstract float getWeight();

    /**
     * @return description of the decorator-wrapped suit.
     */
    public String getDescription(){
        return suit.getDescription() + description;
    }
}

/**
 * Flamethrower decorator for suits
 */
class Flamethrower extends ExoSuitAttachment{
    public Flamethrower(ExoSuit s) {
        super(s);
        description = "Flamethrower ";
    }

    @Override
    public int getCost() {
        return 50 + suit.getCost();
    }

    @Override
    public float getWeight() {
        return 2 + suit.getWeight();
    }
}

/**
 * AutoRifle decorator for suits
 */
class AutoRifle extends ExoSuitAttachment{
    public AutoRifle(ExoSuit s) {
        super(s);
        description = "AutoRifle ";
    }

    @Override
    public int getCost() {
        return 30 + suit.getCost();
    }

    @Override
    public float getWeight() {
        return 1.5f + suit.getWeight();
    }
}

/**
 * RocketLauncher decorator for suits.
 */
class RocketLauncher extends ExoSuitAttachment{
    public RocketLauncher(ExoSuit s) {
        super(s);
        description = "RocketLauncher ";
    }

    @Override
    public int getCost() {
        return 150 + suit.getCost();
    }

    @Override
    public float getWeight() {
        return 7.5f + suit.getWeight();
    }
}

/**
 * Laser decorator for suits.
 */
class Laser extends ExoSuitAttachment{
    public Laser(ExoSuit s) {
        super(s);
        description = "Laser ";
    }

    @Override
    public int getCost() {
        return 200 + suit.getCost();
    }

    @Override
    public float getWeight() {
        return 5.5f + suit.getWeight();
    }
}