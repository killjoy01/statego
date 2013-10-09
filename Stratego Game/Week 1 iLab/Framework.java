package StrategoJava;

import java.awt.*;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.Image;

import javax.swing.JFrame;
import javax.swing.JPanel;



public class Framework extends JPanel implements MouseListener, Runnable
{
	private GameBoard board;
	private Font f = new Font("Courier New", Font.BOLD|Font.ITALIC, 20);
	private Image layout;
	public final int MENU = 0, INIT = 1, PROGRAM = 2, SCOUT = 3, CREDITS_SCENE = 4, GAME_OVER = 5, QUIT = 6;
	public int state;
	private GamePiece thepieces[];
	private Image redpieces[];
	private Image bluepieces[];
	public boolean isRunning = true;
	private Thread thread;
	private boolean running = true;
	private static Vector2D initPosition;
	private static int setPiece;
	private static int pieceType;
	public Framework()
	{
		setFocusable(true);
		requestFocus();
		addMouseListener(this);
		layout = null;
		thepieces = null;
		board = new GameBoard();
		redpieces = new Image[13];
		bluepieces = new Image[13];
	}
	
	public void init()
	{
		layout = Toolkit.getDefaultToolkit().createImage("test3.png");
		redpieces[0] = Toolkit.getDefaultToolkit().createImage("redblank.jpg");
		redpieces[1] = Toolkit.getDefaultToolkit().createImage("redmarshal.jpg");
		redpieces[2] = Toolkit.getDefaultToolkit().createImage("redgeneral.jpg");
		redpieces[3] = Toolkit.getDefaultToolkit().createImage("redcolonel.jpg");
		redpieces[4] = Toolkit.getDefaultToolkit().createImage("redmajor.jpg");
		redpieces[5] = Toolkit.getDefaultToolkit().createImage("redcaptain.jpg");
		redpieces[6] = Toolkit.getDefaultToolkit().createImage("redlieutenant.jpg");
		redpieces[7] = Toolkit.getDefaultToolkit().createImage("redsergeant.jpg");
		redpieces[8] = Toolkit.getDefaultToolkit().createImage("redminer.jpg");
		redpieces[9] = Toolkit.getDefaultToolkit().createImage("redscout.jpg");
		redpieces[10] = Toolkit.getDefaultToolkit().createImage("redspy.jpg");
		redpieces[11] = Toolkit.getDefaultToolkit().createImage("redbomb.jpg");
		redpieces[12] = Toolkit.getDefaultToolkit().createImage("redflag.jpg");
		bluepieces[0] = Toolkit.getDefaultToolkit().createImage("blueblank.jpg");
		bluepieces[1] = Toolkit.getDefaultToolkit().createImage("bluebomb.jpg");
		bluepieces[2] = Toolkit.getDefaultToolkit().createImage("bluecaptain.jpg");
		bluepieces[3] = Toolkit.getDefaultToolkit().createImage("bluecolonel.jpg");
		bluepieces[4] = Toolkit.getDefaultToolkit().createImage("blueflag.jpg");
		bluepieces[5] = Toolkit.getDefaultToolkit().createImage("bluegeneral.jpg");
		bluepieces[6] = Toolkit.getDefaultToolkit().createImage("bluelieutenant.jpg");
		bluepieces[7] = Toolkit.getDefaultToolkit().createImage("bluemajor.jpg");
		bluepieces[8] = Toolkit.getDefaultToolkit().createImage("bluemarshal.jpg");
		bluepieces[9] = Toolkit.getDefaultToolkit().createImage("blueminer.jpg");
		bluepieces[10] = Toolkit.getDefaultToolkit().createImage("bluescout.jpg");
		bluepieces[11] = Toolkit.getDefaultToolkit().createImage("bluesergeant.jpg");
		bluepieces[12] = Toolkit.getDefaultToolkit().createImage("bluespy.jpg");
		initPosition = new Vector2D(0, Stratego.SCREEN_HEIGHT - redpieces[0].getHeight(null));
		state = INIT;
	}
	
	public void addNotify()
	{
		super.addNotify();
		if (thread == null)
		{
			thread = new Thread(this);
			thread.start();
		}
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
		try
		{
			for (int i = 0; i < 40; ++i)
			{
				if (board.getActive() == 0)
				{
					if (board.getPlayer(0).getGamePiece(i).getActive())
					{
						g.drawImage(board.getPlayer(0).getGamePiece(i).getTexture(),
									(int)(board.getPlayer(0).getGamePiece(i).getPosition().getX() + 
										  board.getPlayer(0).getGamePiece(i).getTexture().getWidth(null)),
									(int)(board.getPlayer(0).getGamePiece(i).getPosition().getY() +
										  board.getPlayer(0).getGamePiece(i).getTexture().getHeight(null)), null);
					}

					if (board.getPlayer(1).getGamePiece(i).getActive())
					{
						g.drawImage(bluepieces[0],
									(int)(board.getPlayer(1).getGamePiece(i).getPosition().getX() + 
									      bluepieces[0].getWidth(null)),
									      (int)(board.getPlayer(1).getGamePiece(i).getPosition().getY() +
									      bluepieces[0].getHeight(null)), null);
					}
				}
				else
				{
					if (board.getPlayer(1).getGamePiece(i).getActive())
					{
						g.drawImage(board.getPlayer(1).getGamePiece(i).getTexture(),
						           (int)(board.getPlayer(1).getGamePiece(i).getPosition().getX() + 
						                 board.getPlayer(1).getGamePiece(i).getTexture().getWidth(null)),
								   (int)(board.getPlayer(1).getGamePiece(i).getPosition().getY() +
								         board.getPlayer(1).getGamePiece(i).getTexture().getHeight(null)), null);
  			      	}
					if (board.getPlayer(0).getGamePiece(i).getActive())
					{
						g.drawImage(redpieces[0],
								   (int)(board.getPlayer(0).getGamePiece(i).getPosition().getX() + 
										 redpieces[0].getWidth(null)),
								   (int)(board.getPlayer(0).getGamePiece(i).getPosition().getY() +
										 redpieces[0].getHeight(null)), null);
					}
				}
			}
			if (board.getActive() == 0)
			{
				g.drawImage(redpieces[pieceType + 1], (int)initPosition.getX(),
							initPosition.getY(), null);
			}
			else
			{
				g.drawImage(bluepieces[pieceType / 13 + 1], (int)initPosition.getX(),
						initPosition.getY(), null);
			}
		}
		catch (Exception e){System.out.println(e.getMessage());}
		
	}
	
	public void run()
	{
		init();
		while (running)
		{
			gameUpdate();
			gameRender();
		}
	}
	public void mousePressed(MouseEvent e) 
	{
		if (state == INIT)
		{
			if (e.getButton() == MouseEvent.BUTTON1)
			{
			}
		}
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
	
	private boolean gameUpdate()
	{

		if (state == INIT)
		{
			if (board.getActive() == 0)
			{
				if (setPiece == 0)
				{
					pieceType = 0;
				}
				else if (setPiece == 1)
				{
					pieceType = 1;
				}
				else if ((setPiece >= 2) && (setPiece <= 3))
				{
					pieceType = 2;
				}
				else if ((setPiece >= 4) && (setPiece <= 6))
				{
					pieceType = 3;
				}
				else if ((setPiece >= 7) && (setPiece <= 10))
				{
					pieceType = 4;
				}
				else if ((setPiece >= 11) && (setPiece <= 14))
				{
					pieceType = 5;
				}
				else if ((setPiece >= 15) && (setPiece <= 18))
				{
					pieceType = 6;
				}
				else if ((setPiece >= 19) && (setPiece <= 23))
				{
					pieceType = 7;
				}
				else if ((setPiece >= 24) && (setPiece <= 31))
				{
					pieceType = 8;
				}
				else if (setPiece == 32)
				{
					pieceType = 9;
				}
				else if ((setPiece >= 23) && (setPiece <= 38))
				{
					pieceType = 10;
				}
				else if (setPiece == 39)
				{
					pieceType = 11;
				}
				else if (setPiece == 40)
				{
					board.setActive(1);
					setPiece = 0;
					pieceType = 12;
					initPosition = new Vector2D(0, 0);
					//state = BLANK_BOARD;
					return false;
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}
	private void gameRender()
	{
		repaint();
	}
	
	
}
