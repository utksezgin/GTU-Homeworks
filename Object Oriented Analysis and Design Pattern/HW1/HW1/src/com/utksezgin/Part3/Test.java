package com.utksezgin.Part3;

public class Test {
    public static void main(String[] args){
        ExoSuit suit1 = new dec();
        suit1 = new Flamethrower(suit1);
        suit1 = new AutoRifle(suit1);

        ExoSuit suit2 = new ora();
        suit2 = new Laser(suit2);
        suit2 = new RocketLauncher(suit2);

        ExoSuit suit3 = new tor();
        suit3 = new Flamethrower(suit3);
        suit3 = new AutoRifle(suit3);
        suit3 = new RocketLauncher(suit3);
        suit3 = new Laser(suit3);

        System.out.println("Suit1 Specs:");
        System.out.println("Description: " + suit1.getDescription());
        System.out.println("Cost: " + suit1.getCost() + "k");
        System.out.println("Weight: " + suit1.getWeight() + "kg");

        System.out.println("Suit2 Specs:");
        System.out.println("Description: " + suit2.getDescription());
        System.out.println("Cost: " + suit2.getCost() + "k");
        System.out.println("Weight: " + suit2.getWeight() + "kg");

        System.out.println("Suit3 Specs:");
        System.out.println("Description: " + suit3.getDescription());
        System.out.println("Cost: " + suit3.getCost() + "k");
        System.out.println("Weight: " + suit3.getWeight() + "kg");

    }
}
