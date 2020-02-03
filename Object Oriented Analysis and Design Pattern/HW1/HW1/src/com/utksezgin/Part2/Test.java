package com.utksezgin.Part2;

public class Test {
    public static void main(String[] args) {
        Subscribee textCenter = new Subscribee(contentType.text);
        Subscribee audioCenter = new Subscribee(contentType.audio);
        Subscribee photoCenter = new Subscribee(contentType.photo);

        Subscriber arthas = new Subscriber("Arthas");
        Subscriber illidan = new Subscriber("Illidan");
        Subscriber medivh = new Subscriber("Medivh");
        Subscriber khadgar = new Subscriber("Khadgar");
        Subscriber sylvanas = new Subscriber("Sylvanas");
        Subscriber varian = new Subscriber("Varian");
        Subscriber anduin = new Subscriber("Anduin");

        textCenter.addSubscriber(medivh);
        textCenter.addSubscriber(khadgar);
        textCenter.addSubscriber(varian);
        textCenter.addSubscriber(anduin);
        textCenter.addSubscriber(sylvanas);

        audioCenter.addSubscriber(illidan);
        audioCenter.addSubscriber(arthas);
        audioCenter.addSubscriber(varian);
        audioCenter.addSubscriber(anduin);
        audioCenter.addSubscriber(sylvanas);

        photoCenter.addSubscriber(arthas);
        photoCenter.addSubscriber(illidan);
        photoCenter.addSubscriber(sylvanas);

        System.out.println("Text center released the new patch notes for WoW!");
        textCenter.notifySubscribers();

        System.out.println("\nAudio center released the soundtrack of the newest raid in WoW!");
        audioCenter.notifySubscribers();

        System.out.println("\nPhoto Center shared the leaked concept arts from the newest WoW expansion");
        photoCenter.notifySubscribers();

        System.out.println("\nSylvanas unsubscribed from text center as she is rumored to die in next expansion");
        textCenter.removeSubscriber(sylvanas);

        System.out.println("Text Center reveals the fate of Azeroth");
        textCenter.notifySubscribers();

        System.out.println("\nSylvanas is ready to face her destiny and she subscribes to text center again.");
        textCenter.addSubscriber(sylvanas);
        System.out.println("Characters to be killed off in the next expansion are leaked on Text Center");
        textCenter.notifySubscribers();

    }
}
