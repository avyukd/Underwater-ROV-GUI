import java.awt.Color;
import java.awt.Graphics;
import java.lang.*;
import java.lang.Math;
public class TiltSymbol {
	
	private Color myColor;
	private int myXwidth;
	private double x1, x2, y1, y2;
	private int tilt;
	
	public TiltSymbol(int myX, int t){
		myColor = Color.RED;
		
		myXwidth = myX;
		// myXwidth is the diameter
		
      tilt  = t;
	   setCoordinates();
   }
	public double getX1(){
		return x1;	
	}
	public double getY1(){
		return y1;
	}
  	public double getX2(){
		return x2;	
	}
	public double getY2(){
		return y2;
	}
	public int getXWidth(){
		return myXwidth;
	}
	public void setXWidth( int x){
		myXwidth  = x;
	}
   
   public int getTilt(){
      return tilt;
   }
   public void setTilt(int t){
      tilt =t;
      setCoordinates();
      // redraw after every set (use set Coordinates)
   }
	public void draw(Graphics g){
		g.setColor(myColor);
      g.drawOval(myXwidth/2-25,myXwidth/2-25,50,50);
		g.drawLine((int)getX1(), (int)getY1(), (int)getX2(), (int)getY2());
	}
	
	public void setCoordinates(){
     double hyp = myXwidth/2;
     
     if(Math.floor(tilt) ==0 || Math.floor(tilt) ==180){
      x1 = myXwidth;
      y1 = hyp;
      x2 = 0;
      y2 = hyp;
     }else if(Math.floor(tilt) == 90 || Math.floor(tilt) == 270){
      x1 = hyp;
      y1= 0;
      x2 = hyp;
      y2 = myXwidth;
     }else{
      x1= hyp+(hyp*Math.cos(tilt));
      y1 = hyp-(hyp*Math.sin(tilt));
      x2 = hyp-(hyp*Math.cos(tilt));
      y2 = hyp+(hyp*Math.sin(tilt));
     }
   }

}