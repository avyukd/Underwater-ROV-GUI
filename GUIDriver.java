	import javax.swing.JFrame;
public class GUIDriver {
 		public static void main(String[] args){
			JFrame frame = new JFrame("Motor Panel Test");
			frame.setSize(400, 150);
			frame.setLocation(100,50);
			frame.setContentPane(new LightsPanel());
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setVisible(true);
		}
	}


