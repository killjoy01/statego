package StrategoJava;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.Image;

import javax.swing.JFrame;
import javax.swing.JPanel;


public class Framework extends JPanel implements MouseListener
{
	private GameBoard board;
	private Font f = new Font("Courier New", Font.BOLD|Font.ITALIC, 20);
	private Image layout, piecepictures[];
	public static int MENU = 0, INIT = 1, PROGRAM = 2, SCOUT = 3, CREDITS_SCENE = 4, GAME_OVER = 5, QUIT = 6;
	private GamePiece thepieces[];
	
	public Framework()
	{
		addMouseListener(this);
		board = null;
		layout = null;
		piecepictures = null;
		thepieces = null;
		board = new GameBoard();
		layout = Toolkit.getDefaultToolkit().
				createImage("test3.png");
	}
	
	public void paintComponent(Graphics g) 
	{
		super.paintComponent(g);
		g.setFont(f);
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				
				g.drawImage(layout, (int)(i * layout.getWidth(null)), (int)(j * layout.getHeight(null)), null);
			}
		}
	}
	
	public static void main(String[] args) 
	{
		JFrame jf = new JFrame("My Frame");
		jf.setSize(800, 672);
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jf.add(new Framework());
		jf.setVisible(true);
	}

	public void mousePressed(MouseEvent e) {
	}
	@Override
	public void mouseClicked(MouseEvent e) {
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
}
