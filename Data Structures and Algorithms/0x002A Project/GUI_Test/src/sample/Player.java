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
 *
 */
public class Player extends User implements Initializable{

    private Story theStory;
    public static String pickedGameFile= "./saved";
    Stack<Question> questions;



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

    public Player() throws IOException, IDNotAllowed {
        try {
            theStory=new Story("42.txt"/*pickedGameFile + Welcome.filename*/);
            questions=new Stack<>();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (IDNotAllowed ıdNotAllowed) {
            ıdNotAllowed.printStackTrace();
        }
    }


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

    public void Answered1(){
        PassToNextQuestion(1);
    }
    public void Answered2(){
        PassToNextQuestion(2);
    }
    public void Answered3(){
        PassToNextQuestion(3);
    }
    public void Answered4(){
        PassToNextQuestion(4);
    }


    public void PassToNextQuestion(int answerNum){
        fxmlPastQuestionList.getItems().add(theStory.getCurrQuestion());
        questions.push(theStory.getCurrQuestion());
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
    }

    public void undoQuestion(){
        fxmlPastQuestionList.getItems().remove(theStory.undo());

        if(questions.empty())
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


    public void finish(){
        fxmlPlayPane.setVisible(false);
        fxmlFinishPane.setVisible(true);
        fxmlFinishLabel.setText(theStory.getCurrQuestion().getQuestionText() + "\n" + theStory.getGameChar().toString());
    }
}