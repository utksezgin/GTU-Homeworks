package Q1;

public class Main {

    public static void main(String[] args){
        DoubleHashingMap<Integer, String> doubleHashingMap1 = new DoubleHashingMap<>(10);

        doubleHashingMap1.put(5, "CSE222");
        doubleHashingMap1.put(15, "CSE312");
        doubleHashingMap1.put(13, "CSE344");

        System.out.println("First double hashing map tests");
        System.out.println("Get by key: " + doubleHashingMap1.get(5));
        System.out.println("Get by key: " + doubleHashingMap1.get(15));
        System.out.println("Get by key: " + doubleHashingMap1.get(13));
        System.out.println("Get by index: " + doubleHashingMap1.getIndex(5));
        System.out.println("Get by index: " + doubleHashingMap1.getIndex(6));
        System.out.println("Get by index: " + doubleHashingMap1.getIndex(3));

        System.out.println("\nSecond double hashing map tests");
        DoubleHashingMap<Integer, Double> doubleHashingMap2 = new DoubleHashingMap<>(5);

        doubleHashingMap2.put(5, 5.5);
        doubleHashingMap2.put(9, 9.5);
        doubleHashingMap2.put(6, 6.5);
        doubleHashingMap2.put(2, 2.5);
        doubleHashingMap2.put(15, 15.5);
        doubleHashingMap2.put(88, 88.5);

        System.out.println("Get by key: " + doubleHashingMap2.get(5));
        System.out.println("Get by key: " + doubleHashingMap2.get(9));
        System.out.println("Get by key: " + doubleHashingMap2.get(6));
        System.out.println("Get by key: " + doubleHashingMap2.get(2));
        System.out.println("Get by key: " + doubleHashingMap2.get(15));
        System.out.println("Get by key: " + doubleHashingMap2.get(88));
        //Since there's a rehashing, indexes will be changed.
        //Node: Normally there shouldn't be a getIndex method, these are just for testing purposes.
        System.out.println("Get by index: " + doubleHashingMap2.getIndex(5));
        System.out.println("Get by index: " + doubleHashingMap2.getIndex(9));
        System.out.println("Get by index: " + doubleHashingMap2.getIndex(6));
        System.out.println("Get by index: " + doubleHashingMap2.getIndex(2));
        System.out.println("Get by index: " + doubleHashingMap2.getIndex(5));
        System.out.println("Get by index: " + doubleHashingMap2.getIndex(8));

    }
}
