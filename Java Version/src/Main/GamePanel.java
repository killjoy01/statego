package Main;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.awt.event.*;

import javax.swing.JPanel;

import GameState.GameStateManager;

public class GamePanel extends JPanel implements Runnable, KeyListener{
	//  INFO:  Dimensions
	public static final int HEIGHT = 240;
	public static final int WIDTH = 320;
	public static final int SCALE = 2;
	
	// INFO:  Graphics 
	private BufferedImage title;
	private Graphics2D graphics;
	private boolean running;
	
	//  INFO:  GameStateManager
	private GameStateManager gameStateManager;
	
	//  INFO:  Game Thread
	private Thread thread;
	
	/////////////////////////////////////////////////////////////////////////
	//  TODO:  Should difficulty be here?
	private int difficulty;
	
	public GamePanel(){
		//  TODO:  Is this necessary?  
		super();
		difficulty = 0;
		setPreferredSize(new Dimension(WIDTH * SCALE, HEIGHT * SCALE));
		setFocusable(true);
		requestFocus();
	}
	
	public void addNotify(){
		super.addNotify();
		if(thread == null){
			thread = new Thread(this);
			addKeyListener(this);
			thread.start();
		}
	}
	
	private void init(){
		title = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
		graphics = (Graphics2D) title.getGraphics();
		running = true;
		gameStateManager = new GameStateManager();
	}
	
	public void run(){
		init();
		
		while(running){
			update();
			draw();
			drawToScreen();
		}
	}
	
	private void update(){
		gameStateManager.update();
	}
	
	private void draw(){
		gameStateManager.draw(graphics);
	}
	private void drawToScreen(){
		Graphics graphicsTwo = getGraphics();
		graphicsTwo.drawImage(title, 0, 0, WIDTH * SCALE, HEIGHT * SCALE, null);
		graphicsTwo.dispose();
	}
	
	public void keyTyped(KeyEvent key){
		
	}
	
	public void keyPressed(KeyEvent key){
		gameStateManager.keyPressed(key.getKeyCode());
	}
	
	public void keyReleased(KeyEvent key){
		gameStateManager.keyReleased(key.getKeyCode());
	}
	
}