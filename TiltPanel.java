import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.awt.Component.*;
import java.io.*;
import java.util.Scanner;

public class TiltPanel extends JPanel{
   private static final Color BACKGROUND = Color.BLUE;
	private static final int x = 400;
	private static final int y = 400;
	private BufferedImage myImage;
	private Graphics g;
	private TiltSymbol ts;
   int tilt;
   int current = 10;
   Timer t;
   public TiltPanel(){
         tilt = 0;
         myImage = new BufferedImage(x,y,BufferedImage.TYPE_INT_RGB);
   	   g = myImage.getGraphics();		
   		
   		g.setColor(BACKGROUND);
   		g.fillRect(0, 0, x, y);
   		ts = new TiltSymbol(x,tilt);
         ts.draw(g);
         t = new Timer(500, new Listener());
         t.start();
     
         
   	}
      
      public void paintComponent(Graphics g)
      {
        g.drawImage(myImage, 0, 0, x, y, null);
       }
       
      public class Listener implements ActionListener {

		   @Override
		   public void actionPerformed(ActionEvent arg0) {
            g.setColor(BACKGROUND);
      	       g.fillRect(0,0,x,y);
             ts.setTilt(current);
             ts.draw(g);
             repaint();
             
         }
      }
   
   
}
