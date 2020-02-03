package com.utksezgin.Part2;

/**
 * Subscribers of the subscribee.
 *
 * @author Azmi Utku Sezgin
 */
public class Subscriber {
    String subscriberName = "";

    /**
     * @param name Name of the subscriber
     */
    public Subscriber(String name){
        subscriberName = name;
    }

    /**
     * Action to do when notify received from subscriber. This may be for example, visit the notifier site with
     * a small change to parameter or receive the updated content via parameter.
     */
    public void update(){
        System.out.println("Update received by " + subscriberName);
    }
}
