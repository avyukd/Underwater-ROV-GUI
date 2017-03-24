import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;

public class ShortcutWindow extends JPanel{
	private JButton shutdown, reorient, bringToSurface;
   public ShortcutWindow(){
      // add shortcuts as needed
		setLayout(new FlowLayout(FlowLayout.CENTER,5,5));
      JLabel m = new JLabel("Shortcuts: ");
      Font f = new Font("Calibri", Font.BOLD, 18);
      m.setFont(f);
      m.setForeground(Color.red);
      add(m);
      shutdown = new JButton("Shut Down");
      shutdown.setForeground(Color.red);
		reorient = new JButton("Reorient Robot");
      reorient.setForeground(Color.red);
		bringToSurface = new JButton("Surface Robot");
      bringToSurface.setForeground(Color.red);
      
      shutdown.addActionListener(new Shutdown());
      reorient.addActionListener(new Reorient());
      bringToSurface.addActionListener(new Surface());
      add(shutdown);
      add(reorient);
      add(bringToSurface);		
	}
	
   public class Shutdown implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent arg0) {
          // write to arduino serial monitor
          if(shutdown.getText().equals("Shut Down")){
            shutdown.setText("Confirm shut down?");
          }else if(shutdown.getText().equals("Confirm shut down?")){
            shutdown.setText("Shutting down");
            //write to arduino
            shutdown.setEnabled(false);
            
          }
      }
	}
   
   public class Reorient implements ActionListener {
     public void actionPerformed(ActionEvent arg0) {
          // write to arduino serial monitor
          reorient.setEnabled(false);
          try{
            System.out.println("worked");
            Thread.sleep(5000);
         } catch(InterruptedException ex) {
            System.err.println("Not working");
            Thread.currentThread().interrupt();
         } // how long does reorientation take MAX
          
          reorient.setEnabled(true); 
   
     }
	}
   
   
   
   public class Surface implements ActionListener {
     public void actionPerformed(ActionEvent arg0) {
       // write to arduino serial monitor
        bringToSurface.setEnabled(false);
          try{
            System.out.println("worked");
            Thread.sleep(5000);
         } catch(InterruptedException ex) {
            System.err.println("Not working");
            Thread.currentThread().interrupt();
         } // how long does reorientation take MAX
          
         bringToSurface.setEnabled(true); 
   

     }
	}

}
