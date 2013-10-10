package StrategoJava;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.Image;

import javax.swing.JFrame;
import javax.swing.JPanel;



public class Framework extends JPanel implements MouseListener, KeyListener, Runnable
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
		addKeyListener(this);
		layout = null;
		thepieces = null;
		board = new GameBoard();
		redpieces = new Image[13];
		bluepieces = new Image[13];
		setPiece = 0;
		initPosition = new Vector2D(0, (Stratego.SCREEN_HEIGHT - 64));
	}
	
	public void init()
	{
		layout = Toolkit.getDefaultToolkit().createImage("test3.png");
		redpieces[0] = Toolkit.getDefaultToolkit().createImage("redblank.png");
		redpieces[1] = Toolkit.getDefaultToolkit().createImage("redmarshal.png");
		redpieces[2] = Toolkit.getDefaultToolkit().createImage("redgeneral.png");
		redpieces[3] = Toolkit.getDefaultToolkit().createImage("redcolonel.png");
		redpieces[4] = Toolkit.getDefaultToolkit().createImage("redmajor.png");
		redpieces[5] = Toolkit.getDefaultToolkit().createImage("redcaptain.png");
		redpieces[6] = Toolkit.getDefaultToolkit().createImage("redlieutenant.png");
		redpieces[7] = Toolkit.getDefaultToolkit().createImage("redsergeant.png");
		redpieces[8] = Toolkit.getDefaultToolkit().createImage("redminer.png");
		redpieces[9] = Toolkit.getDefaultToolkit().createImage("redscout.png");
		redpieces[10] = Toolkit.getDefaultToolkit().createImage("redspy.png");
		redpieces[11] = Toolkit.getDefaultToolkit().createImage("redbomb.png");
		redpieces[12] = Toolkit.getDefaultToolkit().createImage("redflag.png");
		bluepieces[0] = Toolkit.getDefaultToolkit().createImage("blueblank.jpg");
		bluepieces[1] = Toolkit.getDefaultToolkit().createImage("bluemarshal.png"); 
		bluepieces[2] = Toolkit.getDefaultToolkit().createImage("bluegeneral.png");
		bluepieces[3] = Toolkit.getDefaultToolkit().createImage("bluecolonel.png");
		bluepieces[4] = Toolkit.getDefaultToolkit().createImage("bluemajor.png");
		bluepieces[5] = Toolkit.getDefaultToolkit().createImage("bluecaptain.png");
		bluepieces[6] = Toolkit.getDefaultToolkit().createImage("bluelieutenant.png");
		bluepieces[7] = Toolkit.getDefaultToolkit().createImage("bluesergeant.png");
		bluepieces[8] = Toolkit.getDefaultToolkit().createImage("blueminer.png");
		bluepieces[9] = Toolkit.getDefaultToolkit().createImage("bluescout.png");
		bluepieces[10] = Toolkit.getDefaultToolkit().createImage("bluespy.png");
		bluepieces[11] = Toolkit.getDefaultToolkit().createImage("bluebomb.png");
		bluepieces[12] = Toolkit.getDefaultToolkit().createImage("blueflag.png");
		makeGamePieces();
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
		//try
		{
			for (int i = 0; i < 40; ++i)
			{
				if (board.getActive() == 0)
				{		
					if (board.getPlayer(0).getGamePiece(i).getActive())
					{
						g.drawImage(board.getPlayer(0).getGamePiece(i).getTexture(),
									(int)(board.getPlayer(0).getGamePiece(i).getPosition().getX()),
									(int)(board.getPlayer(0).getGamePiece(i).getPosition().getY()), null);
					}

					if (board.getPlayer(1).getGamePiece(i).getActive())
					{
						g.drawImage(bluepieces[0],
									(int)(board.getPlayer(1).getGamePiece(i).getPosition().getX()),
									      (int)(board.getPlayer(1).getGamePiece(i).getPosition().getY()), null);
					}
				}
				else
				{
					if (board.getPlayer(1).getGamePiece(i).getActive())
					{
						g.drawImage(board.getPlayer(1).getGamePiece(i).getTexture(),
						           (int)(board.getPlayer(1).getGamePiece(i).getPosition().getX()), 
								   (int)(board.getPlayer(1).getGamePiece(i).getPosition().getY()), null);
  			      	}
					if (board.getPlayer(0).getGamePiece(i).getActive())
					{
						g.drawImage(redpieces[0],
								   (int)(board.getPlayer(0).getGamePiece(i).getPosition().getX()),
								   (int)(board.getPlayer(0).getGamePiece(i).getPosition().getY()), null);
					}
				}
			}
			if (state == INIT)
			{
				if (board.getActive() == 0)	
				{
					System.out.println(initPosition.getX());
					System.out.println(initPosition.getY());
					g.drawImage(thepieces[setPiece].getTexture(), initPosition.getX(),
								initPosition.getY(), null);
				}
				else
				{
					g.drawImage(thepieces[setPiece].getTexture(), (int)initPosition.getX(),
							initPosition.getY(), null);
				}
			}
		}
		//catch (Exception e){System.out.println(e.getMessage());}
		
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
	
	 /** Handle the key typed event from the text field. */
    public void keyTyped(KeyEvent e) {
        
    }
     
    /** Handle the key pressed event from the text field. */
    public void keyPressed(KeyEvent e) {
        
    }
     
    /** Handle the key released event from the text field. */
    public void keyReleased(KeyEvent e) {
    
    	System.out.println(KeyEvent.getKeyText(e.getKeyCode()));
    	if (state == INIT)
    	{
    		if (board.getActive() == 0)
    		{
    			if (e.getKeyCode() == KeyEvent.VK_ENTER)
    			{
    				thepieces[setPiece].setPosition(initPosition);
    				if (!board.getPlayer(0).checkForCollision(initPosition))
    				{
    					board.getPlayer(0).setGamePiece(setPiece, thepieces[setPiece]);
    					board.getPlayer(0).getGamePiece(setPiece).setActive(true);
    					setPiece++;
    					if (setPiece > 39)
    					{
    						board.setActive(1);
    						initPosition.setX(0);
    						initPosition.setY(0);
    						return;
    					}
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_RIGHT)
    			{
    				if (initPosition.getX() < (9 * redpieces[0].getWidth(null)))
    				{
    					initPosition.setX(initPosition.getX() + redpieces[0].getWidth(null));
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_LEFT)
    			{
    				if (initPosition.getX() > 0)
    				{
    					initPosition.setX(initPosition.getX() - redpieces[0].getWidth(null));
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_UP)
    			{
    				if (initPosition.getY() > (Stratego.SCREEN_HEIGHT - (4 * redpieces[0].getWidth(null))))
    				{
    					initPosition.setY(initPosition.getY() - redpieces[0].getWidth(null));
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_DOWN)
    			{
    				if (initPosition.getY() < (Stratego.SCREEN_HEIGHT - redpieces[0].getWidth(null)))
    				{
    					initPosition.setY(initPosition.getY() + redpieces[0].getWidth(null));
    				}
    			}
    		}
    		if (board.getActive() == 1)
    		{
    			if (e.getKeyCode() == KeyEvent.VK_ENTER)
    			{
    				thepieces[setPiece].setPosition(initPosition);
    				if (!board.getPlayer(1).checkForCollision(initPosition))
    				{
    					board.getPlayer(1).setGamePiece(setPiece % 40, thepieces[setPiece]);
    					board.getPlayer(1).getGamePiece(setPiece % 40).setActive(true);
    					setPiece++;
    					if (setPiece > 79)
    					{
    						board.setActive(0);
    						state = PROGRAM;
    					}
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_RIGHT)
    			{
    				if (initPosition.getX() < (9 * bluepieces[0].getWidth(null)))
    				{
    					initPosition.setX(initPosition.getX() + redpieces[0].getWidth(null));
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_LEFT)
    			{
    				if (initPosition.getX() > 0)
    				{
    					initPosition.setX(initPosition.getX() - bluepieces[0].getWidth(null));
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_UP)
    			{
    				if (initPosition.getY() > 0)
    				{
    					initPosition.setY(initPosition.getY() - bluepieces[0].getWidth(null));
    				}
    			}
    			if (e.getKeyCode() == KeyEvent.VK_DOWN)
    			{
    				if (initPosition.getY() < (4 * bluepieces[0].getWidth(null)))
    				{
    					initPosition.setY(initPosition.getY() + redpieces[0].getWidth(null));
    				}
    			}
    		}
    	}
    }
    
	private boolean gameUpdate()
	{
		if (state == INIT)
		{

		}
		return false;
	}
	private void gameRender()
	{
		repaint();
	}
	
	private void makeGamePieces()
	{
		thepieces = new GamePiece[80];
		thepieces[0] = new GamePiece();
		thepieces[0].setTexture(redpieces[1]);
		thepieces[0].setRank(9);
		thepieces[0].setShowRank(false);
		thepieces[1] = new GamePiece();
		thepieces[1].setTexture(redpieces[2]);
		thepieces[1].setRank(8);
		thepieces[1].setShowRank(false);
		for (int i = 2; i <= 3; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[3]);
			thepieces[i].setRank(7);
			thepieces[i].setShowRank(false);
		}
		for (int i = 4; i <= 6; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[4]);
			thepieces[i].setRank(6);
			thepieces[i].setShowRank(false);
		}
		for (int i = 7; i <= 10; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[5]);
			thepieces[i].setRank(5);
			thepieces[i].setShowRank(false);
		}
		for (int i = 11; i <= 14; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[6]);
			thepieces[i].setRank(4);
			thepieces[i].setShowRank(false);
		}
		for (int i = 15; i <= 18; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[7]);
			thepieces[i].setRank(3);
			thepieces[i].setShowRank(false);
		}
		for (int i = 19; i <= 23; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[8]);
			thepieces[i].setRank(2);
			thepieces[i].setShowRank(false);
		}
		for (int i = 24; i <= 31; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[9]);
			thepieces[i].setRank(1);
			thepieces[i].setShowRank(false);
		}
		thepieces[32] = new GamePiece();
		thepieces[32].setTexture(redpieces[10]);
		thepieces[32].setRank(0);
		thepieces[32].setShowRank(false);
		for (int i = 33; i <= 38; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(redpieces[11]);
			thepieces[i].setRank(10);
			thepieces[i].setShowRank(false);
		}
		thepieces[39] = new GamePiece();
		thepieces[39].setTexture(redpieces[12]);
		thepieces[39].setRank(-1);
		thepieces[39].setShowRank(false);
		thepieces[40] = new GamePiece();
		thepieces[40].setTexture(bluepieces[1]);
		thepieces[40].setRank(9);
		thepieces[40].setShowRank(false);
		thepieces[41] = new GamePiece();
		thepieces[41].setTexture(bluepieces[2]);
		thepieces[41].setRank(8);
		thepieces[41].setShowRank(false);
		for (int i = 42; i <= 43; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[3]);
			thepieces[i].setRank(7);
			thepieces[i].setShowRank(false);
		}
		for (int i = 44; i <= 46; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[4]);
			thepieces[i].setRank(6);
			thepieces[i].setShowRank(false);
		}
		for (int i = 47; i <= 50; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[5]);
			thepieces[i].setRank(5);
			thepieces[i].setShowRank(false);
		}
		for (int i = 51; i <= 54; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[6]);
			thepieces[i].setRank(4);
			thepieces[i].setShowRank(false);
		}
		for (int i = 55; i <= 58; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[7]);
			thepieces[i].setRank(3);
			thepieces[i].setShowRank(false);
		}
		for (int i = 59; i <= 63; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[8]);
			thepieces[i].setRank(2);
			thepieces[i].setShowRank(false);
		}
		for (int i = 64; i <= 71; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[9]);
			thepieces[i].setRank(1);
			thepieces[i].setShowRank(false);
		}
		thepieces[72] = new GamePiece();
		thepieces[72].setTexture(bluepieces[10]);
		thepieces[72].setRank(0);
		thepieces[72].setShowRank(false);
		for (int i = 73; i <= 78; ++i)
		{
			thepieces[i] = new GamePiece();
			thepieces[i].setTexture(bluepieces[11]);
			thepieces[i].setRank(10);
			thepieces[i].setShowRank(false);
		}
		thepieces[79] = new GamePiece();
		thepieces[79].setTexture(bluepieces[12]);
		thepieces[79].setRank(-1);
		thepieces[79].setShowRank(false);
	}
}
