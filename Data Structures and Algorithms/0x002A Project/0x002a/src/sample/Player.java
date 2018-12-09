package sample;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

import java.io.IOException;
import java.net.URL;
import java.util.*;

/**
 * This class is for making possible to play a game that created by 0x002A engine.
 * Implements Initializable interface for create a GUI.
 */
public class Player extends User implements Initializable{
    /**
     * Story will created by a save data choice from Welcome screen.
     */
    private Story theStory;
    /**
     * Save directory location.
     */
    public static String pickedGameFile= "saved/";

    @FXML AnchorPane fxmlQuestionAnswer;

    @FXML Label fxmlQuestionText;

    @FXML Button fxmlUndoButton;

    @FXML Button fxmlAnswer1;
    @FXML Button fxmlAnswer2;
    @FXML Button fxmlAnswer3;
    @FXML Button fxmlAnswer4;
    @FXML ListView<Question> fxmlPastQuestionList;
    @FXML SplitPane fxmlPlayPane;
    @FXML Pane fxmlFinishPane;
    @FXML Label fxmlFinishLabel;
    @FXML VBox fxmlVBox;
    @FXML AnchorPane fxmlGeneralPane;


    /**
     * Constructor, creates a new Story by filename choice from welcome screen.
     * @throws IOException if there is no such file
     * @throws IDNotAllowed if question can' t be created
     */
    public Player() throws IOException, IDNotAllowed {
        try {
            theStory=new Story(pickedGameFile + Welcome.filename);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (IDNotAllowed ıdNotAllowed) {
            ıdNotAllowed.printStackTrace();
        }
    }


    /**
     * Creates a new frame for playing game in GUI.
     */
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        fxmlFinishPane.setVisible(false);
        fxmlUndoButton.setVisible(false);
        if(theStory.isEnd())
            finish();
        else {
            fxmlQuestionText.setText(theStory.getFirstQuestion().getQuestionText());
            ArrayList<Answer> firstAnswers = theStory.legalAnswers();
            if (firstAnswers.size() >= 1) {
                fxmlAnswer1.setText(firstAnswers.get(0).getAnswerText());
                fxmlAnswer1.setVisible(true);
            } else
                fxmlAnswer1.setVisible(false);

            if (firstAnswers.size() >= 2) {
                fxmlAnswer2.setText(firstAnswers.get(1).getAnswerText());
                fxmlAnswer2.setVisible(true);
            } else
                fxmlAnswer2.setVisible(false);

            if (firstAnswers.size() >= 3) {
                fxmlAnswer3.setText(firstAnswers.get(2).getAnswerText());
                fxmlAnswer3.setVisible(true);
            } else
                fxmlAnswer3.setVisible(false);

            if (firstAnswers.size() == 4) {
                fxmlAnswer4.setText(firstAnswers.get(3).getAnswerText());
                fxmlAnswer4.setVisible(true);
            } else
                fxmlAnswer4.setVisible(false);
        }
    }

    /**
     * Choose the 1st answer
     */
    public void Answered1(){
        PassToNextQuestion(1);
    }

    /**
     * Choose the 2nd answer
     */
    public void Answered2(){
        PassToNextQuestion(2);
    }

    /**
     * Choose the 3th answer.
     */
    public void Answered3(){
        PassToNextQuestion(3);
    }

    /**
     * Choose the 4th answer.
     */
    public void Answered4(){
        PassToNextQuestion(4);
    }


    /**
     * Take the selected answer and update the story by the answer.
     * @param answerNum selected answer number.
     */
    public void PassToNextQuestion(int answerNum){
        fxmlPastQuestionList.getItems().add(theStory.getCurrQuestion());
        theStory.toNextQuestion(answerNum);
        if(theStory.isEnd())
            finish();
        else{
            fxmlQuestionText.setText(theStory.getCurrQuestion().getQuestionText());
            ArrayList<Answer> firstAnswers=theStory.legalAnswers();
            if (firstAnswers.size() >= 1) {
                fxmlAnswer1.setText(firstAnswers.get(0).getAnswerText());
                fxmlAnswer1.setVisible(true);
            } else
                fxmlAnswer1.setVisible(false);

            if (firstAnswers.size() >= 2) {
                fxmlAnswer2.setText(firstAnswers.get(1).getAnswerText());
                fxmlAnswer2.setVisible(true);
            } else
                fxmlAnswer2.setVisible(false);

            if (firstAnswers.size() >= 3) {
                fxmlAnswer3.setText(firstAnswers.get(2).getAnswerText());
                fxmlAnswer3.setVisible(true);
            } else
                fxmlAnswer3.setVisible(false);

            if (firstAnswers.size() == 4) {
                fxmlAnswer4.setText(firstAnswers.get(3).getAnswerText());
                fxmlAnswer4.setVisible(true);
            } else
                fxmlAnswer4.setVisible(false);
        }
        fxmlUndoButton.setVisible(true);
    }

    /**
     * Return the last question and restore the story.
     */
    public void undoQuestion(){
        fxmlPastQuestionList.getItems().remove(theStory.undo());

        if(theStory.isUndoStackEmpty())
            fxmlUndoButton.setVisible(false);

        ArrayList<Answer> firstAnswers=theStory.legalAnswers();
        if (firstAnswers.size() >= 1) {
            fxmlAnswer1.setText(firstAnswers.get(0).getAnswerText());
            fxmlAnswer1.setVisible(true);
        } else
            fxmlAnswer1.setVisible(false);

        if (firstAnswers.size() >= 2) {
            fxmlAnswer2.setText(firstAnswers.get(1).getAnswerText());
            fxmlAnswer2.setVisible(true);
        } else
            fxmlAnswer2.setVisible(false);

        if (firstAnswers.size() >= 3) {
            fxmlAnswer3.setText(firstAnswers.get(2).getAnswerText());
            fxmlAnswer3.setVisible(true);
        } else
            fxmlAnswer3.setVisible(false);

        if (firstAnswers.size() == 4) {
            fxmlAnswer4.setText(firstAnswers.get(3).getAnswerText());
            fxmlAnswer4.setVisible(true);
        } else
            fxmlAnswer4.setVisible(false);
    }


    /**
     * End the story and show last question without answers.
     */
    public void finish(){
        fxmlPlayPane.setVisible(false);
        fxmlFinishPane.setVisible(true);
        fxmlFinishLabel.setText(theStory.getCurrQuestion().getQuestionText() + "\n" + theStory.getGameChar().toString());
    }
}