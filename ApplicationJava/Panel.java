import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class Panel extends JPanel{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	Frame frm;
	Image image;
	int x;
	int y;
	int i = 0;
	Image map;
	Image tuture;
	Image tutureDroite;
	Image tutureGauche;
	int node = 1;
	
	public Panel(Frame frame) {
		frm = frame;
		
		try {
            this.map = ImageIO.read(this.getClass().getResourceAsStream("map.png"));
            this.tuture = ImageIO.read(this.getClass().getResourceAsStream("tuture.png"));
            this.tutureDroite = ImageIO.read(this.getClass().getResourceAsStream("tuture - Copie.png"));
            this.tutureGauche = ImageIO.read(this.getClass().getResourceAsStream("tuture - Copie - Copie.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
	}
	
	public void paint(Graphics g) {
		
			super.paint(g);
			g.clearRect(0, 0, this.getWidth(), this.getHeight());
			g.drawImage(map, 5, 0, frm);
			g.drawLine(620, 0, 620, 450);
			g.drawLine(620,40,820,40);
			g.setFont(new Font("Calibri", Font.PLAIN, 20));
			g.drawString("Tuture en direct", 630, 30);
			g.drawString("Vitesse moyenne :", 630, 80);
			g.drawString(" 0.315m/s", 630, 120);
		
				displayNode(g);
	}
	
	public void displayNode(Graphics g) {
		switch (node) {
		case 1:	
			image = tuture; //1
			x = 80;
			y = 50;
			node++;
			break;
		case 2:
			image = tuture; //2
			x = 170;
			y = 50;
			node++;
			break;
		case 3:
			image = tuture;//3
			x = 350;
			y = 50;
			node++;
			break;
		case 4:
			image = tuture; //4
			x = 432;
			y = 50;
			if(i == 0) {
				node++;
				i++;
			} else {
				node = 14;
			}
			break;
		case 5:
			image = tuture; //5
			x = 480;
			y = 50;
			node++;
			break;
		case 6:
			image = tutureDroite; //6	
			x = 500;
			y = 210;
			node++;
			break;
		case 7:
			image = tuture; //7
			x = 480;
			y = 300;
			node++;
			break;
		case 8:
			image = tuture;//8
			x = 165;
			y = 300;
			node++;
			break;
		case 9:
			image = tuture;//9
			x = 85;
			y = 300;
			node++;
			break;
		case 10:
			image = tutureGauche;//10
			x = 63;
			y = 210;
			node++;
			break;
		case 11:
			image = tutureGauche;//11
			x = 63;
			y = 130;
			node++;
			break;
		case 12:
			image = tuture;//12
			x = 170;
			y = 115;
			node++;
			break;
		case 13:
			image = tuture;//13
			x = 350;
			y = 115;
			node = 3;
			break;
		case 14:
			image = tuture;//14
			x = 430;
			y = 200;
			node++;
			break;
		case 15:
			image = tuture;//15
			x = 430;
			y = 245;
			node++;
			break;
		case 16:
			image = tuture;//16
			x = 170;
			y = 245;
			break;
		default:
			break;
		}
		g.drawImage(image, x, y, frm);
		this.repaint();
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
