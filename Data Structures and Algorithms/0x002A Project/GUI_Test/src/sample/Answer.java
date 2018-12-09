package sample;

import javafx.util.Pair;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;

/**
 *  Answer class extended from Node.
 *  Answer's object hold Answer text and result.
 *  (result: Next Question, stats or End Game).
 */
public class Answer extends Node {

    private static final String SPLITTER = "##";
    private static final String STATSPLITER = "%%";

    private Question next;
    int destinationID;
    String answerText;
    HashMap<String, Pair<Character, Integer>> statsToBeChanged;
    int ownerID;
    int id;

    /**
     * Constructor used by Maker.
     * @param id Answers ID
     * @param _ownerID ID of question that owns this answer
     */
    Answer(int id, int _ownerID){
        answerText = "Put Your Answer Text Here.";
        ownerID = _ownerID;
        this.id = id;
        next = null;
        destinationID = -1;
        statsToBeChanged = new HashMap<String,Pair<Character, Integer>>();

    }

    /**
     * Constructor with parameter.
     * @param input type is string.
     * It's parse to string.After initialize answerText and nextQuestionID.
     */
    Answer(String input){
        String[] tokens = input.split(SPLITTER );
        answerText = tokens[0];
        destinationID = Integer.parseInt(tokens[1]);
        if(tokens.length != 2){ //has preRequisite
            String prereqSplit = tokens[2];
            String[] pre = prereqSplit.split(STATSPLITER);

            String statName = pre[2];
            Integer value = Integer.parseInt(pre[1]);
            Character symbol = pre[0].charAt(0);
            Pair<Character,Integer> p = new Pair<Character,Integer>(symbol,value);
            statsToBeChanged = new HashMap<String, Pair<Character,Integer>>();
            statsToBeChanged.put(statName,p);
        }else{
            statsToBeChanged = new HashMap<>();
        }
    }

    /**
     * Updates answers fields with given parameters.
     * @param _text new text for answer.
     * @param targetQuestion new target (next) Question for answer
     * @param _preReq new preRequisites for answer
     */
    public void UpdateAllFields(String _text, Question targetQuestion,HashMap<String,Pair<Character,Integer>> _preReq ){
        setAnswerText(_text);
        setNext(targetQuestion);
        setDestinationID(targetQuestion.getId());
        setStatsToBeChanged(_preReq);
    }

    /**
     * If this answer object selected by user in a game.
     * This method will take user to next question.
     * @return next question address.
     */
    public Question GetNextQuestion(){
        return next;
    }

    /**
     * This method will use for set next quest after the this answer.
     */
    public void setNextQuestion(Question nextQuestion){
        next = nextQuestion;
    }

    /**
     * This method will use for answer have a next question.
     * If there is no next question, it's mean game is ended.
     * @return boolean. İf next variable == null return  false.
     * Otherwise return true.
     */
    public boolean hasNextQuestion(){
        if(destinationID == -1){
            return false;
        }
        return true;
    }


    //Getter - Setters
    public Question getNext() {
        return next;
    }

    public void setNext(Question next) {
        this.next = next;
    }

    public int getDestinationID() {
        return destinationID;
    }

    public void setDestinationID(int destinationID) {
        this.destinationID = destinationID;
    }

    public String getAnswerText() {
        return answerText;
    }

    public void setAnswerText(String answerText) {
        this.answerText = answerText;
    }

    public HashMap<String, Pair<Character, Integer>> getStatsToBeChanged() {
        return statsToBeChanged;
    }

    public void setStatsToBeChanged(HashMap<String, Pair<Character, Integer>> statsToBeChanged) {
        this.statsToBeChanged = statsToBeChanged;
    }

    public int getOwnerID() {
        return ownerID;
    }

    public void setOwnerID(int ownerID) {
        this.ownerID = ownerID;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String saveFormat(){
        String save = "";
        save = answerText + SPLITTER + destinationID + SPLITTER;
        if(statsToBeChanged.isEmpty()){
            save += SPLITTER;
        }else{
            Set<String> keyV = statsToBeChanged.keySet();
            for(String outp : keyV){
                String statName = outp;
                Character symbol = (statsToBeChanged.get(statName)).getKey();
                Integer value = (statsToBeChanged.get(statName)).getValue();
                save += symbol + STATSPLITER + value + STATSPLITER + statName + STATSPLITER;
            }
        }

        save += SPLITTER;

        return save;
    }

    /**
     * Override toString method.
     * @return answerText string variable.
     */
    @Override
    public String toString() {
        return " " + answerText + "\n->" + destinationID ;
    }
}