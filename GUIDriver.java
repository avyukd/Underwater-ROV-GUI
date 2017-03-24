	import javax.swing.JFrame;
public class GUIDriver {
 		public static void main(String[] args){
			JFrame frame = new JFrame("Arm Panel test");
			frame.setSize(400, 400);
			frame.setLocation(100,50);
			frame.setContentPane(new TiltPanel());
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setVisible(true);
		}
	}


