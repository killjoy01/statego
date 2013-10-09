package StrategoJava;

import java.awt.Image;

public class GamePiece extends Sprite {
	private int playercode;
	private int rank;
	private String name;
	private boolean selection;
	private boolean isActive;
	private boolean showRank;
	
	public GamePiece()
	{
		super();
		playercode = 0;
		rank = 0;
		name = "";
		selection = false;
		isActive = false;
		showRank = false;
	}
	
	void init (Image i, int r)
	{
		super.init(i, new Vector2D(-1, -1), 0.0f, 0.0f, 0.0f);
		rank = 'r';
		switch(r)
		{
		case -1:
			name = "FLAG";
			break;
		case 0:
			name = "SPY";
			break;
		case 1:
			name = "SCOUT";
			break;
		case 2:
			name = "MINER";
			break;
		case 3:
			name = "SERGEANT";
			break;
		case 4:
			name = "LIEUTENANT";
			break;
		case 5:
			name = "CAPTAIN";
			break;
		case 6:
			name = "MAJOR";
			break;
		case 7:
			name = "COLONEL";
			break;
		case 8:
			name = "GENERAL";
			break;
		case 9:
			name = "MARSHAL";
			break;
		case 10:
			name = "BOMB";
			break;
		default:
			name = "FLAG";
			break;
		}
	}
	
	public void setRank(int r) 
	{
		rank = r;
		switch(r)
		{
		case -1:
			name = "FLAG";
			break;
		case 0:
			name = "SPY";
			break;
		case 1:
			name = "SCOUT";
			break;
		case 2:
			name = "MINER";
			break;
		case 3:
			name = "SERGEANT";
			break;
		case 4:
			name = "LIEUTENANT";
			break;
		case 5:
			name = "CAPTAIN";
			break;
		case 6:
			name = "MAJOR";
			break;
		case 7:
			name = "COLONEL";
			break;
		case 8:
			name = "GENERAL";
			break;
		case 9:
			name = "MARSHAL";
			break;
		case 10:
			name = "BOMB";
			break;
		default:
			name = "FLAG";
			break;
		}
	}
	public int getRank() {return rank;}
	public String getName() {return name;}
	public void setSelection(boolean s) {selection = s;}
	public boolean getSelection() {return selection;}
	public void setActive(boolean a) {isActive = a;}
	public boolean getActive() {return isActive;}
	public void setShowRank(boolean s) {showRank = s;}
	public boolean getShowRank() {return showRank;}
	
	public boolean checkForCollision(Vector2D p)
	{
		if (position == p)
		{
			if (isActive)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
};
