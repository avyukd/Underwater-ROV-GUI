import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;
public class CollectorPanel extends JPanel{
   private JButton use;
   private JButton s; // on or off
   Timer t;
   public CollectorPanel(){
      use = new JButton("Use Collector");
      setLayout(new FlowLayout());
      JLabel m = new JLabel("Agar Collector: ");
      Font f = new Font("Calibri", Font.BOLD, 18);
      m.setFont((f));
      m.setForeground(Color.RED);
      add(m);
      add(use);      
      s=new JButton("On"); //cut power supply to
      add(s);
      use.addActionListener(new Listener());
      s.addActionListener(new Switch());   
  }
   public class Switch implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent arg0) {
         //write to Arduino
         if(s.getText().equals("On")){
            s.setText("Off");
         }else{
            s.setText("On");
         }
         // write state to arduino to cut off supply because only being used once
      }
	}

   public class Listener implements ActionListener{
      @Override
		public void actionPerformed(ActionEvent arg0) {
         // loading means in use, blue means has been used 
         use.setForeground(Color.blue);
         use.setEnabled(false);
           try{
            System.out.println("worked");
            Thread.sleep(5000);
           } catch(InterruptedException ex) {
            System.err.println("Not working");
            Thread.currentThread().interrupt();
           } // how long does the collector take
           use.setText("Use Collector");
           use.setEnabled(true); 
         
         }
      }
   }


