import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Scanner;

public class ArmPanel extends JPanel{
	private JButton rotate, open, close, up, down; 
   private JLabel howOpen, level; 
   private int hO, l;
   public ArmPanel(){
      hO = 0;
      l = 0;
		setLayout(new FlowLayout());
      
      JLabel mr = new JLabel("Arm: "); //center vertically
      //mr.setVerticalAlignment(JLabel.CENTER);
      Font f = new Font("Calibri", Font.BOLD, 18);
      mr.setFont(f);
      mr.setForeground(Color.red);
      add(mr, SwingConstants.CENTER);
      
      JPanel sub = new JPanel();
      sub.setLayout(new GridLayout(5,5,3,1));
      JPanel r = new JPanel();
      r.setLayout(new GridLayout(1,2));
      r.add(new JLabel("Rotate: ", SwingConstants.CENTER));
      rotate = new JButton("Rotate Arm 360 Degrees");
      r.add(rotate);
      sub.add(r);
      
      JPanel oc = new JPanel();
      oc.setLayout(new GridLayout(1,3));
      howOpen = new JLabel(hO+"% open", SwingConstants.CENTER);    
		open = new JButton("Open Arm 10%");
      close = new JButton("Close Arm 10%");
		oc.add(howOpen);
      JPanel m = new JPanel();
      m.setLayout(new GridLayout(2,1));
      m.add(open);
      m.add(close);
      oc.add(m);
      sub.add(oc);
      
      JPanel lev = new JPanel();
      lev.setLayout(new GridLayout(1,3));
      level = new JLabel(l+" degrees", SwingConstants.CENTER);    
		up = new JButton("Move Arm Up 10 degrees");
      down = new JButton("Move Arm Down 10 degrees");
		lev.add(level);
      JPanel t = new JPanel();
      t.setLayout(new GridLayout(2,1));
      t.add(up);
      t.add(down);
      lev.add(t);
      sub.add(lev);	
      
      add(sub);
      
      rotate.addActionListener(new Rotate());
      
      open.addActionListener(new Listener("open"));
      close.addActionListener(new Listener("close"));
      up.addActionListener(new Listener("up"));
      down.addActionListener(new Listener("down"));

   }
	 public class Rotate implements ActionListener{
    @Override
    public void actionPerformed(ActionEvent arg0) {
            //write to arduino
            // how much extent of rotation needed
         
      }

    }
    
    public class Listener implements ActionListener{
      String s;
      public Listener(String ss){
         s = ss;
      }
      @Override
      public void actionPerformed(ActionEvent arg0){
         if(s.equals("open")){
            hO+=10;
            if(hO>100){
               hO = 100;
            }
            howOpen.setText(""+hO+"% open");
         }
        if(s.equals("close")){
            hO-=10;
               if(hO<0){
                  hO = 0;
               }
               howOpen.setText(""+hO+"% open");
         }
         if(s.equals("up")){
            l+=10;
            if(l>90){
               l = 90;
            }
            level.setText(""+l+" degrees");
         }
        if(s.equals("down")){
            l-=10;
               if(l<-90){
                  l = -90;
               }
               level.setText(""+l+" degrees");
         }
         
      }
    }
   
}
