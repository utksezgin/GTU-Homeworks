package sample;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;



public class Maker_Frame extends JPanel {
    private static final int N_ROWS = 20;
    private static final String[] header = {"Questions", "1. A", "2. A", "3. A", "4. A"};
    private DefaultTableModel dtm = new DefaultTableModel(null, header) {

        @Override
        public Class<?> getColumnClass(int col) {
            return getValueAt(0, col).getClass();
        }
    };
    private JTable table = new JTable(dtm);
    private JScrollPane scrollPane = new JScrollPane(table);
    private JScrollBar vScroll = scrollPane.getVerticalScrollBar();
    private int row;
    private boolean isAutoScroll;

    public Maker_Frame() {
        top_create();
        this.add(bottom_c(), BorderLayout.SOUTH);
    }

    private JPanel bottom_c()
    {
        JPanel panel = new JPanel(new GridLayout(2, 1));
        JButton [] bottom_l = new JButton[2];
        ActionListener k = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if (actionEvent.getActionCommand().equals("0"))
                    addRow();
                else
                    System.out.println("save");
            }
        };
        bottom_l[0] = new JButton("Add Question");
        bottom_l[1] = new JButton("Save");
        for(int i = 0; i < 2; ++i)
        {
            bottom_l[i].setActionCommand("" + i);
            bottom_l[i].addActionListener(k);
            panel.add(bottom_l[i]);
        }
        return panel;
    }


    private void top_create()
    {
        this.setLayout(new BorderLayout());
        Dimension d = new Dimension(320, N_ROWS * table.getRowHeight());
        table.addMouseListener(new MouseAdapter() {

            @Override
            public void mouseClicked(MouseEvent mouseEvent) {
                int row = table.rowAtPoint(mouseEvent.getPoint());
                int col = table.columnAtPoint(mouseEvent.getPoint());
                if(col == 0)
                    System.out.println(table.getValueAt(row,col).toString());
                else
                    JOptionPane.showMessageDialog(null, table.getValueAt(row,col).toString());
            }});
        table.setPreferredScrollableViewportSize(d);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        vScroll.addAdjustmentListener(new AdjustmentListener() {

            @Override
            public void adjustmentValueChanged(AdjustmentEvent e) {
                isAutoScroll = !e.getValueIsAdjusting();
            }
        });
        this.add(scrollPane, BorderLayout.CENTER);
    }


    private void addRow() {
        char c = (char) ('A' + row++ % 26);
        dtm.addRow(new Object[]{
                Character.valueOf(c),
                String.valueOf(c) + String.valueOf(row),
                Integer.valueOf(row),
                Integer.valueOf(row),
                Boolean.valueOf(isAutoScroll),
        });
    }
}