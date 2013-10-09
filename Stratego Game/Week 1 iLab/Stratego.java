package StrategoJava;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Stratego extends JPanel {
	public static int SCREEN_WIDTH = 800;
	public static int SCREEN_HEIGHT = 672;
	
	public static void main(String[] args) 
	{
		JFrame jf = new JFrame("My Frame");
		jf.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jf.add(new Framework());
		jf.setVisible(true);
	}
}
