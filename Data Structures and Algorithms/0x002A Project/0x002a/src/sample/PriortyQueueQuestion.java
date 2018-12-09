package sample;

import java.util.ArrayList;

public class PriortyQueueQuestion {
    private ArrayList<Question> questions = new ArrayList<>();
    private ArrayList<Integer> priortys = new ArrayList<>();
    public void add(Question question,Integer priorty){

        questions.add(question);
        priortys.add(priorty);

    }
    public ArrayList<Question> givePriorty(){
        ArrayList<Question> returnValues = new ArrayList<>();
        int maxPriorty = priortys.get(0);
        int i=0;
        for (i=0;i<questions.size();i++){
            if(priortys.get(i)<maxPriorty){
                maxPriorty=priortys.get(i);
            }
        }
        for(int j=0;j<questions.size();j++){
            if (priortys.get(j)==maxPriorty){
                returnValues.add(questions.get(j));
                questions.remove(j);
                priortys.remove(j);
            }
        }
        return returnValues;
    }
    boolean isEmpty(){
        return questions.isEmpty();
    }
}
