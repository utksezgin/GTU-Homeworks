public class Driver {
	public static void main(String[] args) {
		
		
		GTUSetInt<Double> setObj1 = new GTUSet<Double>();
		GTUSetInt<Double> setObj2 = new GTUSet<Double>();
		
		GTUSetMap<String, Integer> mapObj1 = new GTUSetMap<String, Integer>();
		GTUSetMap<String, Integer> mapObj2 = new GTUSetMap<String, Integer>();
		
		GTUSetInt<Double> setIntersection = new GTUSet<Double>();
		GTUSetInt<javafx.util.Pair<String, Integer>> mapIntersection = new GTUSetMap<String, Integer>();
		
		//Inserting part catches IllegalArgumentException if the element exists.
		try {
			setObj1.insert(0.6);
			setObj1.insert(1.3);
			setObj1.insert(1.6);
			setObj1.insert(3.3);
			setObj1.insert(5.9);
			setObj1.insert(10.4);
			
			setObj2.insert(0.6);
			setObj2.insert(6.2);
			setObj2.insert(1.6);
			
			mapObj1.insert(new javafx.util.Pair<>("a1", 5));
			mapObj1.insert(new javafx.util.Pair<>("a2", 2));
			mapObj1.insert(new javafx.util.Pair<>("a5", 8));
			
			mapObj2.insert(new javafx.util.Pair<>("a1", 5));
			mapObj2.insert(new javafx.util.Pair<>("a2", 2));
			mapObj2.insert(new javafx.util.Pair<>("a3", 4));
		}
		catch(java.lang.IllegalArgumentException e) {
			System.out.println(e.toString());
		}
		
		//Testing size and max_size methods
		System.out.println("Size and Max size of setObj1");
		System.out.println(setObj1.size());
		System.out.println(setObj1.max_size());
		
		System.out.println("Size and Max size of mapObj1");
		System.out.println(mapObj1.size());
		System.out.println(mapObj1.max_size());
		
		System.out.println();
		//Testing at function for mapObj1
		System.out.println("Value of a2 key in mapObj1 is:");
		try{
			System.out.println(mapObj1.at("a2"));
		}
		catch(java.lang.IllegalArgumentException e){
			System.out.println(e.toString());
		}
		
		java.util.Iterator<Double> it1 = setObj1.begin(); //Iterator for set object
		java.util.Iterator<javafx.util.Pair<String, Integer>> it2 = mapObj1.begin(); //Iterator for set object
		
		//Printing inserted values to set
		System.out.println("Testing inserted elements for set");
		while(it1.hasNext()) {		
			System.out.println(it1.next());
		}
		
		//Printing inserted values to map
		System.out.println("Testing inserted elements for map");
		while(it2.hasNext()) {		
			System.out.println(it2.next().getValue());
		}
		
		//Output formatting
		System.out.println();
		System.out.println("Intersection Starts");
		System.out.println();
		
		setIntersection =  setObj1.intersection(setObj2);
		mapIntersection =  mapObj1.intersection(mapObj2);
		
		it1 = setIntersection.begin();
		it2 = mapIntersection.begin();
		
		//Printing inserected object of set
		System.out.println("Testing Intersection for set");
		while(it1.hasNext()) {
			System.out.println(it1.next());
		}
				
		System.out.println();
		
		//Printing intersected object of map
		System.out.println("Testing Intersection for map");
		while(it2.hasNext()) {		
			System.out.println(it2.next().getValue());
		}
		
		
		System.out.println();
		
		//Testing find method for set
		System.out.println("Testing find method for set and map");
		it1 = setObj1.find(1.6);
		System.out.println(it1.next());
		
		//Testing find method for map
		javafx.util.Pair<String, Integer> testPair = new javafx.util.Pair<String, Integer>("a1", 5);
		it2 = mapObj1.find(testPair);
		System.out.println(it2.next());

		System.out.println();		
		System.out.println("Testing count method for set and map");
		
		//Testing count method for set
		System.out.println(setObj1.count(1.6));		
		//Testing count method for map
		System.out.println(mapObj1.count(testPair));
		
		System.out.println();
		
		//Testing erase method for set
		System.out.println("Testing erase method for set and map");
		setObj1.erase(1.6);
		it1 = setObj1.find(1.6);
		System.out.println(it1.next());//Should print last element of the object
		
		//Testing erase method for map 
		mapObj1.erase(testPair);
		it2 = mapObj1.find(testPair);
		System.out.println(it2.next());//Should print last element of the object
		
		System.out.println();		
		System.out.println("Testing clear method for set and map");
		System.out.println();	
		//Testing clear for method set
		System.out.println("Size of setObj2 after clear method");
		setObj2.clear();
		System.out.println(setObj2.size());
		
		//Testing clear for method map
		System.out.println("Size of mapObj2 after clear method");
		mapObj2.clear();
		System.out.println(mapObj2.size());
				
	}
}