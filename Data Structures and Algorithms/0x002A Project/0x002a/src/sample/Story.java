package sample;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Stack;


public class Story {


    private BinarySearchTree<Question> QuestionSearchTree = null;//For binary search tree
    private Question firstQuestion = null;//For flow of story
    private CStats GameChar = null;
    private CStats GameCharCurr = null;
    private Question currQuestion = null;
    private PriortyQueueQuestion printArray = new PriortyQueueQuestion();
    private Stack<Question> undoQues;
    private int QuestionCount = 0;
    public Story(String fileName) throws IOException, IDNotAllowed {
        QuestionSearchTree = new BinarySearchTree<>();
        initializeStory(fileName);
        currQuestion=firstQuestion;
        undoQues=new Stack<>();
    }
    /**
     * Verilen dosyadan hikayeyi okur ve yapılandırır
     *
     * @param fileName Hikayeyi icinde tutan dosyanın ismi
     * */
    public void initializeStory(String fileName) throws IOException, IDNotAllowed {

        FileReader readStory = new FileReader(fileName);
        String bufferString;
        boolean firstFlag = true;
        boolean cstatFlag = true;
        StringBuilder parsedString = new StringBuilder();

        BufferedReader readerStory = new BufferedReader(readStory);

        while((bufferString = readerStory.readLine()) != null){
            if(cstatFlag){
                GameChar = new CStats(bufferString);
                cstatFlag = false;
            }
            else{
                Question localCurrQuestion = new Question(bufferString);
                if(!firstFlag)
                {
                    QuestionSearchTree.add(localCurrQuestion);
                    ++QuestionCount;
                }
                else{
                    ++QuestionCount;
                    QuestionSearchTree.add(localCurrQuestion);
                    firstQuestion = localCurrQuestion;
                    firstFlag=false;
                }

            }


        }
        connector();



        return;
    }
    /**
     * Dosyadan okunan soruları birbirine baglar
     *
     *
     * */
    private void connector() throws IDNotAllowed {
        for(int i = 0;i<QuestionCount;i++){
            Question searchThis = new Question(i);
            Question temp = null;
            temp = QuestionSearchTree.search(searchThis);
            if(temp!=null){
                if(temp.GetAnswers() != null)
                    for(int j=0;j<temp.GetAnswers().size();j++){
                        searchThis = new Question(temp.GetAnswers().get(j).destinationID);
                        Question temp2 = QuestionSearchTree.search(searchThis);
                        if(temp2!=null){
                            temp.GetAnswers().get(j).setNextQuestion(temp2);
                        }
                    }
            }
        }
        Question searchThis = new Question(4);

    }
    /**
     * @return Suanki sorunun bir son olup olmadigini dondurur
     *
     * */
    public boolean isEnd(){
        if(currQuestion!=null)
            return currQuestion.isEnd();
        return true;
    }
    /**
     *
     * Suanki sorunun metnini terminale bastirir
     *
     * */
    public void showQuestion(){

        currQuestion.showQuestion();

    }


    /**
     *
     * Suanki sorunun metnini ve cevap metinlerini terminale bastirir
     *
     * */
    public void showQuestionAndAnswer(){
        currQuestion.showQuestionAndAnswer();
    }




    /**
     * Verilen cevap parametresine gore suanki soruyu gunceller
     *
     * @param parameter Gidilmek istenen soruyu tutan cevap
     * */
    public void toNextQuestion(int parameter){
        undoQues.push(currQuestion);
        currQuestion=currQuestion.GetAnswers().get(parameter-1).GetNextQuestion();
        GameCharCurr = GameChar;
        if(!currQuestion.getPreRequisite().isEmpty()){
            GameChar.updateAllStats(currQuestion.getPreRequisite());
        }
    }
    /**
     *
     *
     *Karakter ozelliklerinin gidebildigi cevaplari bir ArrayList<Answer></> halinde dondurur
     *
     *@return Gidilebilecek cevaplar
     * */
    public ArrayList<Answer> legalAnswers(){
        ArrayList<Answer> result = new ArrayList<>();
        for (int i=0;i<currQuestion.GetAnswers().size();i++){
            if(!currQuestion.GetAnswers().get(i).getStatsToBeChanged().isEmpty()){
                if(GameChar.canAccess(currQuestion.GetAnswers().get(i).getStatsToBeChanged()))
                    result.add(currQuestion.GetAnswers().get(i));
                else;

            }
            else{
                result.add(currQuestion.GetAnswers().get(i));
            }
        }
        return result;
    }
    /**
     *
     *Bir onceki hamleye doner
     *
     *
     * */
    public Question undo(){
        currQuestion=undoQues.pop();
        GameChar = GameCharCurr;
        return currQuestion;
    }
    /**
     * @return Suanki soruyu dondurur
     *
     * */
    public Question getCurrQuestion() {
        return currQuestion;
    }
    /**
     * @return ilk soruyu dondurur
     *
     * */
    public Question getFirstQuestion() {
        return firstQuestion;
    }

    /**
     *
     * Ikılı arama agacindan istenen id ye ait soruyu dondurur
     *
     * */
    public Question getByID(int ıd) throws IDNotAllowed {
        Question searchQuestion = new Question(ıd);
        return QuestionSearchTree.search(searchQuestion);
    }

    /**
     *
     * Oncelige gore bastirmak icin oncelikli listeyi doldurur
     *
     * */
    private void initializePrint(){
        ArrayList<Question> Queue=new ArrayList<>();
        int i=1;
        Question current = null;
        if(firstQuestion!=null){
            Queue.add(firstQuestion);
            printArray.add(firstQuestion,i);
            i++;
            while(Queue.size()!=0){
                current = Queue.get(0);
                current.setVisited(true);
                if(current.GetAnswers()!=null){
                    for (int j=0;j<current.GetAnswers().size();j++){
                        if(!current.isVisited()) {
                            printArray.add(current.GetAnswers().get(j).GetNextQuestion(), i);
                            Queue.add(current.GetAnswers().get(j).GetNextQuestion());
                        }
                    }
                }
                i++;
                Queue.remove(0);
            }
        }
    }
    /**
     *
     * @return Karakteri dondurur
     *
     * */
    public CStats getGameChar() {
        return GameChar;
    }


    /**
     *
     * Geri alinabilecek hamle olup olmadigina bakar
     *
     * */
    public boolean isUndoStackEmpty(){
        return undoQues.isEmpty();
    }
}
