import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;

public class LightsPanel extends JPanel{
   private JButton s1, s2;
   public LightsPanel(){
      s1 = new JButton("Off");
		s2 = new JButton("Off");
      setLayout(new FlowLayout());
		JPanel subpanel = new JPanel();
		subpanel.setLayout(new GridLayout(2,2,5,5));
      JLabel m = new JLabel("Lights: ");
      Font f = new Font("Calibri", Font.BOLD, 18);
      m.setFont((f));
      m.setForeground(Color.RED);
      add(m);
      subpanel.add(new JLabel("Blue Lights"));
      subpanel.add(s1);
      subpanel.add(new JLabel("Normal Lights"));
      subpanel.add(s2);
      s1.addActionListener(new Listener(1));
      s2.addActionListener(new Listener(2));
      add(subpanel);

    


}
   public class Listener implements ActionListener {
      int i;
      public Listener(int ii){
         i = ii;
      }
      
		@Override
		public void actionPerformed(ActionEvent arg0) {
        //write to arduino
        if(i==1){
         if(s1.getText().equals("On")){
            s1.setText("Off");
         }else{
            s1.setText("On");
         }
        }else{
         if(s2.getText().equals("On")){
            s2.setText("Off");
         }else{
            s2.setText("On");
         }
        }   
      }
	}
}

