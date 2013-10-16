package GameState;

import java.awt.*;
import java.awt.event.KeyEvent;

import TileMap.Background;
import StrategoJava.Framework;
import StrategoJava.Stratego;

public class MenuState extends GameState {
	
	private Background backGround;
	
	private int currentChoice = 0;
	private String[] options = {"Play Game", "Options", "Credits", "Quit"};
	private String[] optionsMenu = {"Easy", "Normal", "Hard"};
	////////////////////////////////////////////////////////////////////////
	//  INFO:  String array for "easy" printing of credits.
	private String[] credits = {"*AI Programming/Project Lead - Phil Marinucci", "*AI Lead: John Harrison","*Tech Lead - James Sorge", 
								"*Menus / Artwork - Justin Lockridge"};
	
	private Color titleColor;
	private Font titleFont, font;
	
	public MenuState(GameStateManager gsm){
		this.gameStateManager = gsm;
		try{
			backGround = new Background("/AT_Title.png", 1);
			titleColor = new Color(128,0,0);
			titleFont = new Font("Century Gothic", Font.PLAIN, 28);
			font = new Font("Arial", Font.PLAIN, 12);
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	
	public void init(){};
	public void update(){
		backGround.update();
	};
	public void draw(Graphics2D g){
		///////////////////////////////////////////////////////////////////////////////
		//  INFO:  Draws Background, Game title, then menu
		switch(gameStateManager.getMenuState()){
		case 0: //  MAIN_MENU State
		{
		//}
		/////////////////////////////////////////////////////////////////////////////
		//  TODO:  Add an actual background image for Title Screen
		//backGround.draw(g);
			g.setColor(Color.BLACK);
			g.fillRect(0,0, 320, 240);
		g.setColor(titleColor);
		g.setFont(titleFont);
		g.drawString("GSP420 Stratego", 50, 50);
		
		g.setFont(font);
		for(int i = 0; i < options.length; ++i){
			if(i == currentChoice){
				g.setColor(Color.BLUE);
				}
			else{ 
				g.setColor(Color.RED);
			}
			g.drawString(options[i], 130, 180 + i * 15);
		}
		break;
		}
		case 1: // INFO:  MENU_OPTIONS State
		{
			g.setColor(Color.BLACK);
			g.fillRect(0,0, 320, 240);
			g.setColor(Color.ORANGE);
			g.setFont(titleFont);
			g.drawString("Options", 10, 30);
			g.setFont(font);
			g.drawString("Difficulty:  ", 20, 50);
			for(int i = 0; i < optionsMenu.length; ++i){
				if(currentChoice < 0)
					currentChoice = 3;
				if(currentChoice > 2)
					currentChoice = 0;
				if(i == currentChoice){
					g.setColor(Color.BLUE);
					}
				else{ 
					g.setColor(Color.RED);
				}
			
			g.drawString(optionsMenu[i], 30, 70 + i * 15);
			}
			g.setColor(Color.RED);
			g.drawString("Press Enter to return to the Main Menu.", 50, 200);
			break;
		
		}
		case 2: //  INFO:  MENU_CREDITS State
		{
			//backGround.draw(g);
			g.setColor(Color.BLACK);
			g.fillRect(0,0, 320, 240);
			g.setColor(Color.ORANGE);
			g.setFont(titleFont);
			g.drawString("GSP420 Group Project", 10, 30);
			g.setColor(Color.GREEN);
			g.setFont(font);
			for(int i = 0; i < credits.length; ++i){
				g.drawString(credits[i], 30, 50 + i * 15);
			}
			g.drawString("Press Enter to return to the Main Menu.", 50, 200);
			break;
		}
		};
	};
	///////////////////////////////////////////////////////////////////////////////////
	//  INFO:  Function to handle key presses on the main menu / title screen
	private void menuSelection(){
		///////////////////////////////////////////////////////////////////////////
		//  INFO:  Runs the Main Screen Controls
		if(gameStateManager.getMenuState() == 0){
		switch(currentChoice){
		case 0:  //  TODO:  Starts the game, needs implementing
			Stratego.main(null);
			//f.run();
			break;
		case 1:  //  TODO:  Display options / difficulty, needs implementing
			gameStateManager.setMenuState(1);
			currentChoice = 0;
			break;
		case 2:  //  TODO:  Display Credits, needs implementing
			gameStateManager.setMenuState(2);
			currentChoice = 0;
			break;
		case 3:  
			System.exit(0);
			break;
		};
		}
		else{
		///////////////////////////////////////////////////////////////////////////
		//  INFO:  Returns from the Sub-Menus
			gameStateManager.setMenuState(0);
		}
	}
	public void keyPressed(int k){
		switch(k){
		case KeyEvent.VK_ENTER:{
			menuSelection();
			break;
		}
		case KeyEvent.VK_UP:{
			currentChoice--;
			if(currentChoice == -1){
				currentChoice = options.length - 1;
			}
			break;
		}
		case KeyEvent.VK_DOWN:{
			currentChoice++;
			if(currentChoice == 4){
				currentChoice = 0;
			}
			break;
		}
		}
	};
	public void keyReleased(int k){};

}
