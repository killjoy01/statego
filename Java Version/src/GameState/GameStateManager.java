package GameState;

import java.util.ArrayList;

public class GameStateManager {
	private ArrayList<GameState> gameStates;
	private int state, menuState;
	
	/////////////////////////////////////////////////////////////////////////////////
	//  INFO:  For drawing menu, sub-menus, and a game end state so people can replay,
	//         or quit in the middle to start a new game.
	/////////////////////////////////////////////////////////////////////////////////
	//  TODO:  How many states are needed here?  Main menu can have a way to display sub menus
	public static final int MENU_MAIN = 0;
	public static final int MENU_OPTIONS = 1;
	public static final int MENU_CREDITS = 2;
	public static final int GAME_RUN = 3;
	public static final int GAME_END = 4;
	
	public GameStateManager(){
		gameStates = new ArrayList<GameState>();
		state = 0;
		menuState = 0;
		gameStates.add(new MenuState(this));
	}
	
	public void setMenuState(int s){
		menuState = s;
	}
	
	public int getMenuState(){
		return menuState;
	}
	
	public void setState(int s){
		state = s;
		gameStates.get(state).init();
	}
	
	public int getState(){
		return state;
	}
	
	public void update(){
		gameStates.get(state).update();
	}
	
	public void draw(java.awt.Graphics2D g){
		gameStates.get(state).draw(g);
		
	}
	
	public void keyPressed(int k){
		gameStates.get(state).keyPressed(k);
	}
	
	public void keyReleased(int k){
		gameStates.get(state).keyReleased(k);
	}

}
