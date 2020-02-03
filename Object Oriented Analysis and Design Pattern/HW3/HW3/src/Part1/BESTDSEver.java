package Part1;

public class BESTDSEver {
    Object[] bestArray;
    void insert(Object o){
        System.out.println("Insert");
    }
    void remove(Object o){
        System.out.println("Remove");
    }
    Object get(int index){
        System.out.println("Get");
        return bestArray[index];
    }
}
