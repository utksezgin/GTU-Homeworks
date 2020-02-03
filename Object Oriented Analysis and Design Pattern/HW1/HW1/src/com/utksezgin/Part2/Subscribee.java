package com.utksezgin.Part2;

import java.util.HashSet;
import java.util.Set;

/**
 * Subscribee class is used for adding and removing subscribers to its content and notify them on changes.
 *
 *
 * @author Azmi Utku Sezgin
 */
public class Subscribee {
    //Set is used because each subscriber must be unique as they shouldn't be allowed to subscribe twice
    //as they may forget about their subscription and try to subscribe again
    private Set<Subscriber> subscribers = new HashSet<>();
    private Content content;

    public Subscribee(contentType type){
        switch(type){
            case text:
                content = new TextContent();
                break;
            case audio:
                content = new AudioContent();
                break;
            case photo:
                content = new PhotoContent();
                break;
        }
    }

    /**
     * Adds a new subscriber to itself
     * @param sub New subscriber
     */
    public void addSubscriber(Subscriber sub){
        subscribers.add(sub);
    }

    /**
     * Removes the subscriber from itself
     * @param sub Subscriber to be removed.
     */
    public void removeSubscriber(Subscriber sub){
        subscribers.remove(sub);
    }

    /**
     * Notifies it's subscribers.
     */
    public void notifySubscribers(){
        for(Subscriber sub : subscribers){
            sub.update();
        }
    }
}