import javax.swing.JFrame;

public class Frame extends JFrame{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	Panel pnl = new Panel(this);

	public Frame() {
		super();
		
		setTitle("Acar - Tuture");
        setSize(820,450);
        setLocationRelativeTo(null); 
        setResizable(false); 
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        setContentPane(pnl);
        setVisible(true);
	}
}
