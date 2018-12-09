package sample;


import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.util.Pair;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.URL;
import java.util.HashMap;
import java.util.ResourceBundle;

/**
 * This class is used by Application class to create a new story.
 * With this class you can add new questions, answers to your story and save your story for others to play.
 **/
public class Maker extends User implements Initializable {

    //Class Variables
    /**
     * HashMap of Question objects. Stores all created questions excluding deleted ones.
     */
    private HashMap<Integer, Question> questions;
    /**
     * HashMap of Answer objects. Stores all created answers excluding deleted ones.
     */
    private HashMap<Integer, Answer> answers;
    /**
     * Character Stats for the game. Max 3 stats allowed.
     */
    private CStats stats;
    /**
     * Selected Question via GUI.
     */
    private Question selectedQuestion;
    /**
     * Selected Answer Object via GUI
     */
    private Answer selectedAnswer;
    /**
     * Stores created games name.
     */
    private String gameName = "42";
    /**
     * Counts all created Questions for creating ID.
     */
    private int createdQuestionNum;
    /**
     * Counts all created Answers for creating ID.
     */
    private int createdAnswerNum;

    //FXML Variables

    //Panes
    /**
     * Panel for question list
     */
    @FXML AnchorPane questionListPanel;
    /**
     * Panel for answer list
     */
    @FXML AnchorPane answerListPanel;
    /**
     * Panel for Selected Question
     */
    @FXML AnchorPane selectedQuestionPanel;
    /**
     * Panel for Selected Answer
     */
    @FXML AnchorPane selectedAnswerPanel;

    //Lists
    /**
     * Question List of questions HashMap
     */
    @FXML ListView<Question> questionsListView;
    /**
     * Answer List of answers HashMap
     */
    @FXML ListView<Answer> answersListView;

    //Selected Question Parts
    /**
     * ID of SelectedQuestion via GUI
     */
    @FXML Label fxmlSelectedQuestionID;
    /**
     * Text of SelectedQuestion via GUI
     */
    @FXML TextArea fxmlSelectedQuestionText;
    /**
     * SelectedQuestions Number Of Answers. Max 4 Answers allowed
     */
    @FXML TextField fxmlSelectedQuestionAnswerNum;
    /**
     * Choice box of Character Stat Names for Selected Question via GUI
     */
    @FXML ChoiceBox fxmlSelectedQuestionSideEffectBox;
    /**
     * Choice box of CharacterStat Modifiers for Selected Question via GUI
     */
    @FXML ChoiceBox fxmlSelectedQuestionSideEffectModifier;
    /**
     * Text Field for Charactar Stat side Effect Value
     */
    @FXML TextField fxmlSelectedQuestionSideEffectValue;


    //Selected Answer Parts
    /**
     * ID of Selected Answer via GUI
     */
    @FXML Label fxmlSelectedAnswerID;
    /**
     * Text of Selected Answer via GUI
     */
    @FXML TextArea fxmlSelectedAnswerText;
    /**
     * Target Question ID of Selected Answer via GUI
     */
    @FXML TextField fxmlSelectedAnswerTargetQuestionID;
    /**
     * Choice Box of Character Stat Names for Selected Answer via GUI
     */
    @FXML ChoiceBox fxmlSelectedAnswerPreReqBox;
    /**
     * Choice Box of Character Stat Modifier for Selected Answer via GUI
     */
    @FXML ChoiceBox fxmlSelectedAnswerPreReqModifier;
    /**
     * TextField for Character Stat prerequisite value
     */
    @FXML TextField fxmlSelectedAnswerPreReqValue;


    //CSTATS
    /**
     * Name of first Character Stat Name
     */
    @FXML TextField fxmlStatName1;
    /**
     * Name of second Character Stat Name
     */
    @FXML TextField fxmlStatName2;
    /**
     * Name of third Character Stat Name
     */
    @FXML TextField fxmlStatName3;
    /**
     * Default Value of First Character Stat
     */
    @FXML TextField fxmlStatDefault1;
    /**
     * Default Value of Second Character Stat
     */
    @FXML TextField fxmlStatDefault2;
    /**
     * Default Value of Third Character Stat
     */
    @FXML TextField fxmlStatDefault3;

    //Game Name
    /**
     * Game Name Text Field for GUI
     */
    @FXML TextField fxmlGameName;

    /**
     * Used on printing information about maker process to GUI.
     */
    @FXML Label fxmlInformationBox;

    /**
     * No Param Constructor. Creates a starting point for maker.
     */
    public Maker() {
        questions = new HashMap<Integer, Question>();
        answers = new HashMap<Integer, Answer>();
        stats = new CStats();
        selectedAnswer = null;
        selectedQuestion = null;
        createdAnswerNum = 0;
        createdQuestionNum = 0;
    }

    // Question Part

    /**
     * Updates selectedQuestion with FXML parameters. Giving NONE for sideEffect name, removes sideEffect from Question.
     * @throws IDNotAllowed thrown when illegal ID is given to a question.
     * @caution fxmlSelectedQuestionAnswerNum must be smaller than 5
     */
    public void UpdateQuestion() throws IDNotAllowed {
        if (selectedQuestion != null) {
            Integer newNumOfAnswers = Integer.parseInt(fxmlSelectedQuestionAnswerNum.getText());
            if (newNumOfAnswers > 4) newNumOfAnswers = 4;
            selectedQuestion.setText(fxmlSelectedQuestionText.getText());
            while (selectedQuestion.Answers.size() > newNumOfAnswers) {
                RemoveLastAnswer();
            }
            while (selectedQuestion.Answers.size() != newNumOfAnswers) {
                CreateNewAnswer();
            }

            //SideEffect section
            if(!fxmlSelectedQuestionSideEffectBox.getValue().toString().equals("None")) {
                HashMap<String,Pair<Character,Integer>> newSide = new HashMap<String, Pair<Character,Integer>>();
                Pair<Character,Integer> newPair = new Pair<Character,Integer>(fxmlSelectedQuestionSideEffectModifier.getValue().toString().charAt(0), Integer.parseInt(fxmlSelectedQuestionSideEffectValue.getText().toString()) );
                newSide.put(fxmlSelectedQuestionSideEffectBox.getValue().toString(),newPair);
                selectedQuestion.setPreRequisite(newSide);
            }else{
                fxmlSelectedQuestionSideEffectValue.setText("");
                fxmlSelectedQuestionSideEffectModifier.setValue("None");
                fxmlSelectedQuestionSideEffectBox.setValue("None");
                selectedQuestion.preRequisite = new HashMap<>();
            }

            questionsListView.refresh();
            answersListView.refresh();
            selectedQuestionPanel.requestLayout();
            selectedAnswerPanel.requestLayout();

            fxmlInformationBox.setText("Question " + selectedQuestion.getId() + "successfully updated.");

        }
    }

    /**
     * Creates a new Question with default text, no sideEffect and 0 answers.
     * @throws IDNotAllowed thrown when illegal ID is passed to a question.
     */
    public void CreateNewQuestion() throws IDNotAllowed {
        int id = ++createdQuestionNum;
        Question newQ = new Question(id);
        questions.put(newQ.getId(), newQ);
        newQ.Answers.clear();
        questionsListView.getItems().add(newQ);

        fxmlInformationBox.setText("Question " + id + " successfully created.");
    }

    /**
     * Updates selectedQuestion on a Question Click from Question List
     */
    public void QuestionListButtonPushed() {
        Question selectedQuestion = questionsListView.getSelectionModel().getSelectedItem();
        SelectQuestion(selectedQuestion);
    }

    /**
     * Updates selectedAnswer on a Answer Click from Answer List
     */
    public void AnswerListButtonPressed() {
        Answer selectedAnswer = answersListView.getSelectionModel().getSelectedItem();
        SelectAnswer(selectedAnswer);
    }


    /**
     * Method for GUI usage. Updates selectedQuestion panel according to the mouse click on a Question from Question List.
     * @param selected Question that has been clicked on
     */
    public void SelectQuestion(Question selected){
        if (selected != null) {
            selectedQuestion = selected;
            Integer noA = selectedQuestion.Answers.size();

            fxmlSelectedQuestionAnswerNum.setText(noA.toString());
            fxmlSelectedQuestionText.setText(selectedQuestion.getQuestionText());
            noA = selectedQuestion.getId();
            fxmlSelectedQuestionID.setText(noA.toString());

            //SideEffect section
            if(!selectedQuestion.preRequisite.isEmpty()) {

                String key = "";
                if(selectedQuestion.preRequisite.get(fxmlStatName1.getText()) != null){
                    key = fxmlStatName1.getText();
                }else if(selectedQuestion.preRequisite.get(fxmlStatName2.getText()) != null){
                    key = fxmlStatName2.getText();
                }else{
                    key = fxmlStatName3.getText();
                }

                fxmlSelectedQuestionSideEffectBox.setValue(key);
                Pair<Character, Integer> qPair = selectedQuestion.getPreRequisite().get(key);
                fxmlSelectedQuestionSideEffectModifier.setValue(qPair.getKey().toString());
                fxmlSelectedQuestionSideEffectValue.setText(qPair.getValue().toString());
            }else{
                fxmlSelectedQuestionSideEffectValue.setText("");
                fxmlSelectedQuestionSideEffectModifier.setValue("None");
                fxmlSelectedQuestionSideEffectBox.setValue("None");
            }

            selectedAnswer = null;

            answersListView.getItems().clear();
            for (Answer ans : selectedQuestion.Answers) {
                answersListView.getItems().add(ans);
            }
            answersListView.refresh();

        }
    }

    /**
     * Deletes selected question. Makes selectedQuestion null and removes selectedQuestion from QuestionList
     */
    public void DeleteQuestion() {
        if (selectedQuestion != null) {
            RemoveAllAnswers();
            Integer id = selectedQuestion.getId();
            questionsListView.getItems().remove(selectedQuestion);
            questions.remove(selectedQuestion.getId());
            //TODO check for answers goin for that question ?
            selectedQuestion = null;

            fxmlInformationBox.setText("Question " + id + "successfully deleted.");

        }

        //SelectedQuestion Update for null
        fxmlSelectedQuestionID.setText("-1");
        fxmlSelectedQuestionText.setText("Select A Question To Edit");
        fxmlSelectedQuestionAnswerNum.setText("0");

    }


    //Answer Part

    /**
     * Updates selectedAnswer with FXML parameters. Giving NONE for prerequisite name, removes prerequisite from selectedAnswer.
     */
    public void UpdateAnswer() {
        if (selectedAnswer != null) {
            Integer targetQuestionID = Integer.parseInt(fxmlSelectedAnswerTargetQuestionID.getText());
            selectedAnswer.setAnswerText(fxmlSelectedAnswerText.getText());
            selectedAnswer.setDestinationID(targetQuestionID);


            //prerequisite section
            if(!fxmlSelectedAnswerPreReqBox.getValue().toString().equals("None")) {
                HashMap<String,Pair<Character,Integer>> newSide = new HashMap<String, Pair<Character,Integer>>();
                Pair<Character,Integer> newPair = new Pair<Character,Integer>(fxmlSelectedAnswerPreReqModifier.getValue().toString().charAt(0), Integer.parseInt(fxmlSelectedAnswerPreReqValue.getText().toString()) );
                newSide.put(fxmlSelectedAnswerPreReqBox.getValue().toString(),newPair);
                selectedAnswer.setStatsToBeChanged(newSide);
            }else{
                fxmlSelectedAnswerPreReqValue.setText("");
                fxmlSelectedAnswerPreReqModifier.setValue("None");
                fxmlSelectedAnswerPreReqBox.setValue("None");
                selectedAnswer.statsToBeChanged = new HashMap<>();
            }

            fxmlInformationBox.setText("Question " + selectedQuestion.getId() + " Answer ID:" + selectedAnswer.getId() + "successfully updated.");

        }
        questionsListView.refresh();
        answersListView.refresh();
        selectedQuestionPanel.requestLayout();
        selectedAnswerPanel.requestLayout();
    }


    /**
     * Creates new answer with default text, special ID, no prerequisite, and no destination.
     * For a given Quesiton, can not create more than 4 answer
     */
    public void CreateNewAnswer() {
        if (selectedQuestion != null && selectedQuestion.Answers.size() != 4) {
            int id = ++createdAnswerNum;
            Answer newA = new Answer(id, selectedQuestion.getId());
            answers.put(newA.getId(), newA);
            selectedQuestion.AddAnswer(newA);
            answersListView.getItems().add(newA);
            fxmlSelectedQuestionAnswerNum.setText(Integer.toString(selectedQuestion.Answers.size()));
        }
        answersListView.refresh();
        questionsListView.refresh();
    }

    /**
     * Method for GUI usage. Updates selectedAnswer panel according to the mouse click on a Answer from Answer List.
     * @param selected Answer that has been clicked on
     */
    public void SelectAnswer(Answer selected) {
        if (selected != null) {
            selectedAnswer = selected;
            Integer numID = selectedAnswer.getId();
            fxmlSelectedAnswerID.setText(numID.toString());
            fxmlSelectedAnswerText.setText(selectedAnswer.getAnswerText());
            numID = selectedAnswer.getDestinationID();
            fxmlSelectedAnswerTargetQuestionID.setText(numID.toString());

            //prerequisite section
            if(!selectedAnswer.statsToBeChanged.isEmpty()) {
                String key = "";
                if(selectedAnswer.statsToBeChanged.get(fxmlStatName1.getText()) != null){
                    key = fxmlStatName1.getText();
                }else if(selectedAnswer.statsToBeChanged.get(fxmlStatName2.getText()) != null){
                    key = fxmlStatName2.getText();
                }else{
                    key = fxmlStatName3.getText();
                }
                fxmlSelectedAnswerPreReqBox.setValue(key);
                Pair<Character, Integer> qPair = selectedAnswer.getStatsToBeChanged().get(key);
                fxmlSelectedAnswerPreReqModifier.setValue(qPair.getKey().toString());
                fxmlSelectedAnswerPreReqValue.setText(qPair.getValue().toString());
            }else{
                fxmlSelectedAnswerPreReqValue.setText("");
                fxmlSelectedAnswerPreReqModifier.setValue("None");
                fxmlSelectedAnswerPreReqBox.setValue("None");
            }

        }
    }


    /**
     * Deletes selected asnwer. Makes selectedAnswer null and removes selectedAnswer from Answer List
     * @post selectedAnswer becomes null
     */
    public void DeleteAnswer() {
        if(selectedAnswer != null){
            selectedQuestion.Answers.remove(selectedAnswer);
            Integer id = selectedAnswer.getId();
            answers.remove(selectedAnswer.id);
            answersListView.getItems().remove(selectedAnswer);
            answersListView.refresh();
            selectedAnswer = null;

            fxmlInformationBox.setText("Question " + selectedQuestion.getId() + " Answer ID: " + id + " successfully deleted.");

        }

    }

    /**
     * Removes lastAnswer from the selectedQuestion. Updates AnswerList accordingly
     * @return removed answer
     */
    private Answer RemoveLastAnswer() {
        answersListView.getItems().remove(selectedQuestion.Answers.size()-1);
        return selectedQuestion.Answers.remove(selectedQuestion.Answers.size() - 1);
    }

    /**
     * Removes all answers from the selectedQuestion. Clears Answer List for SelectedQuestion.
     */
    private void RemoveAllAnswers() {
        while (selectedQuestion.Answers.size() != 0) {
            RemoveLastAnswer();
        }
        selectedAnswer = null;
    }


    //CStats

    /**
     * Updates CStats for Game Character. Giving nothing for Character Stat name removes that stat from the game.
     */
    public void UpdateCStats() {
        fxmlSelectedQuestionSideEffectBox.getItems().clear();
        fxmlSelectedAnswerPreReqBox.getItems().clear();

        if(!fxmlStatName1.getText().isEmpty()){
            stats.addParam(fxmlStatName1.getText(),Integer.parseInt(fxmlStatDefault1.getText()) );
            fxmlSelectedQuestionSideEffectBox.getItems().add(fxmlStatName1.getText());
            fxmlSelectedAnswerPreReqBox.getItems().add(fxmlStatName1.getText());

        }
        if(!fxmlStatName2.getText().isEmpty()){
            stats.addParam(fxmlStatName2.getText(),Integer.parseInt(fxmlStatDefault2.getText()) );
            fxmlSelectedAnswerPreReqBox.getItems().add(fxmlStatName2.getText());
            fxmlSelectedQuestionSideEffectBox.getItems().add(fxmlStatName2.getText());

        }
        if(!fxmlStatName3.getText().isEmpty()){
            stats.addParam(fxmlStatName3.getText(),Integer.parseInt(fxmlStatDefault3.getText()) );
            fxmlSelectedQuestionSideEffectBox.getItems().add(fxmlStatName3.getText());
            fxmlSelectedAnswerPreReqBox.getItems().add(fxmlStatName3.getText());
        }

        //TODO: Change all Question and Answer cstats for removed Stat.

        fxmlSelectedAnswerPreReqBox.setValue("None");
        fxmlSelectedQuestionSideEffectBox.setValue("None");
        fxmlSelectedQuestionSideEffectBox.getItems().add( "None");
        fxmlSelectedAnswerPreReqBox.getItems().add( "None");

        fxmlInformationBox.setText("Character Stats successfully updated.");

    }

    /**
     * Returns the stat name for given index
     *
     * @param i index for stat name
     * @return Required stat name
     */
    public String getStatName(int i) {
        return (String) stats.getStats().toArray()[i];
    }

    /**
     * Returns Current number of used questions. That means all created questions minus deleted questions
     * @return current number of used questions.
     */
    public int currentNumOfQuestions() {
        return questions.size();
    }

    /**
     * Returns current number of used answers.
     * @return Current number of used answers.
     */
    public int currentNumOfAnswers() {
        return answers.size();
    }

    /**
     * Any question that doesn't have an answer is an ending. This method returns number of Questions that doesn't have any answer.
     * @return number of different endings.
     */
    public int numOfDifferentEndings() {
        int endings = 0;
        for (int i = 0; i < createdQuestionNum; ++i) {
            if (questions.containsKey(i)) {
                if (questions.get(i).Answers.size() == 0) {
                    ++endings;
                }
            }
        }
        return endings;
    }

    /**
     * Sets game name according to FXML variable fxmlGameName
     */
    public void SetGameName() {
        gameName = fxmlGameName.getText();

        fxmlInformationBox.setText("Game Name Successfully changed to " + gameName);

    }

    /**
     * Returns Game Name As A String
     * @return Game Name As A String
     */
    public String GetGameName() {
        return gameName;
    }

    @Override
    /**
     * Initializes unchangeable variables for CharacterStat modifiers. Sets default game name "42"
     * Clears all Character Stat Names.
     */
    public void initialize(URL url, ResourceBundle rb) {

        fxmlSelectedQuestionSideEffectModifier.getItems().clear();
        fxmlSelectedQuestionSideEffectModifier.getItems().addAll("+","-","*","=", "None");

        fxmlSelectedAnswerPreReqModifier.getItems().clear();
        fxmlSelectedAnswerPreReqModifier.getItems().addAll("<","=",">","None");

        fxmlSelectedQuestionSideEffectBox.getItems().clear();
        fxmlSelectedQuestionSideEffectBox.getItems().add("None");

        fxmlSelectedAnswerPreReqBox.getItems().clear();
        fxmlSelectedAnswerPreReqBox.getItems().add("None");

        fxmlGameName.setText("42");
    }


    /**
    * Saves the created story in a file to share with players.
    */
    public void save() throws IOException {

        File saveFile = new File("./saved/"+ gameName + ".txt");
        File theDir = new File("saved");

        boolean created = true;

        if(!theDir.exists()){
            try{
                theDir.mkdir();
            }
            catch(SecurityException e){
                fxmlInformationBox.setText("Failed to Create savedDirectory. Save action is failed. Contact the creators");
                created = false;
            }
        }
        if(created){
            saveFile.delete();
            saveFile.createNewFile();

            FileWriter fileWriter = new FileWriter(saveFile);

            //Cstat saving.
            fileWriter.append(stats.toSave() + "\n");
            fileWriter.flush();

            //Quesiton & Answer saving
            Object[] questionIDS =  questions.keySet().toArray();
            for (Object i : questionIDS) {
                fileWriter.append(questions.get(questionIDS[(Integer)i-1]).saveFormat());
                fileWriter.append("\n");
                fileWriter.flush();
            }
            fileWriter.flush();

            fxmlInformationBox.setText(gameName + " successfully saved");
        }

    }
}