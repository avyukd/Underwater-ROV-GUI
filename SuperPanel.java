import javax.swing.*;
import java.awt.*;

public class SuperPanel extends JPanel{
	private MotorPanel m;
	private OrientationPanel o;
	private ArmPanel a;
	private CollectorPanel c;
	private LightsPanel l;
	
	public SuperPanel(){
		m = new MotorPanel();
		//o = new OrientationPanel();
		a = new ArmPanel();
		c =  new CollectorPanel();
		l = new LightsPanel();
		
		setLayout(new FlowLayout(FlowLayout.LEFT, 15,15));
		
		add(m);
		//add(o);
		add(a);
		add(c);
		add(l);
      add(new ShortcutWindow());
		setForeground(Color.GRAY);
		
	}
	
	
}
