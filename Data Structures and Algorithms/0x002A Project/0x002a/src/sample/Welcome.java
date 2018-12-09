package sample;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class Welcome implements Initializable
{
    @FXML
    private AnchorPane back_ground;
    public static String filename = "";


    @FXML
    private VBox welcome;
    @FXML
    private BorderPane to_visible;
    @FXML
    private javafx.scene.control.ListView<String> game_list;

    private static final String pickedGame= "./saved/";

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        /**
         * String take.
         */
        welcome.setVisible(true);
        to_visible.setVisible(false);
        File folder = new File(pickedGame);
        File[] listOfFiles = folder.listFiles();
        if (listOfFiles != null)
        {
            for (File temp : listOfFiles)
                if (temp.isFile())
                    game_list.getItems().add(temp.getName());
        }
        else
            System.err.println("No such directory");
    }

    public void switch_visible()
    {
        welcome.setVisible(to_visible.isVisible());
        to_visible.setVisible(!welcome.isVisible());
    }

    public void File_selected() throws IOException {
        filename = game_list.getSelectionModel().getSelectedItem();
        AnchorPane pane = FXMLLoader.load(getClass().getResource("player.fxml"));
        back_ground.getChildren().setAll(pane);

    }

    public void maker_clicked() throws IOException
    {
        AnchorPane pane = FXMLLoader.load(getClass().getResource("maker.fxml"));
        back_ground.getChildren().setAll(pane);
    }
}
