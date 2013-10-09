package StrategoJava;

import java.awt.Graphics;

public class GameBoard {
	private Player player[];
	int active;
	
	public GameBoard()
	{
		player = new Player[2];
		active = 0;
	}
	
	public Player getPlayer(int i) {return player[i];}
	public void setPlayer(int i, Player p) {player[i] = p;}
	public void setActive(int a) {active = a;}
	public int getActive() {return active;}
	
	public void displayNewPosition(GamePiece p, Vector2D spacesfound[])
	{
		for (int j = 0; j < 20; j++)
		{
			spacesfound[j] = new Vector2D(-1, -1);
		}
		int i = 0;
		int left = p.getPosition().getX() - 1, right = p.getPosition().getX() + 1, up = p.getPosition().getY() - 1, down = p.getPosition().getY() + 1;
		boolean flagleft = true, flagright = true, flagup = true, flagdown = true;
		while (flagleft)
		{
			Vector2D leftCheck = new Vector2D(left, p.getPosition().getY());
			if (checkForCollision2(leftCheck))
			{
				flagleft = false;
			}
			else if (checkForCollision(leftCheck))
			{
				spacesfound[i] = leftCheck;
				i++;
				flagleft = false;
			}
			else if (left == -1.0f)
			{
				flagleft = false;
			}
			else
			{
				spacesfound[i] = leftCheck;
				i++;
				left--;
			}
		}
		while (flagright)
		{
			Vector2D rightCheck = new Vector2D(right, p.getPosition().getY());
			if (checkForCollision2(rightCheck))
			{
				flagright = false;
			}
			else if (checkForCollision(rightCheck))
			{
				spacesfound[i] = rightCheck;
				i++;
				flagright = false;
			}
			else if (right > 9.0f)
			{
				flagright = false;
			}
			else
			{
				spacesfound[i] = rightCheck;
				i++;
				right++;
			}
		}
		while (flagup)
		{
			Vector2D upCheck = new Vector2D(p.getPosition().getX(), up);
			if (checkForCollision2(upCheck))
			{
				flagup = false;
			}
			else if (checkForCollision(upCheck))
			{
				spacesfound[i] = upCheck;
				i++;
				flagup = false;
			}
			else if (up < 0.0f)
			{
				flagup = false;
			}
			else
			{
				spacesfound[i] = upCheck;
				i++;
				up = up--;
			}
		}
		while (flagdown)
		{
			Vector2D downCheck = new Vector2D(p.getPosition().getX(), down);
			if (checkForCollision2(downCheck))
			{
				flagdown = false;
			}
			else if (checkForCollision(downCheck))
			{
				spacesfound[i] = downCheck;
				i++;
				flagdown = false;
			}
			else if (down > 9.0f)
			{
				flagdown = false;
			}
			else
			{
				spacesfound[i] = downCheck;
				i++;
				down++;
			}
		}
	}
	
	public boolean checkForCollision(Vector2D p)
	{
		for (int i = 0; i < 40; i++)
		{
			if (active == 0)
			{
				if (player[1].getGamePiece(i).checkForCollision(p))
				{
					return true;
				}
			}
			else if (active == 1)
			{
				if (player[0].getGamePiece(i).checkForCollision(p))
				{
					return true;
				}
			}
		}
		return false;
	}
	
	public boolean checkForCollision2(Vector2D p)
	{
		for (int i = 0; i < 40; i++)
		{
			if (player[active].getGamePiece(i).checkForCollision(p))
			{
				return true;
			}
		}
		return false;
	}
	
	public boolean makeSelection(Vector2D p)
	{
		for (int i = 0; i < 40; i++)
		{
			player[0].getGamePiece(i).setSelection(false);
			player[1].getGamePiece(i).setSelection(false);
		}
		if (active == 0)
		{
			GamePiece g = new GamePiece();
			for (int i = 0; i < 40; i++)
			{
				if ((player[0].getGamePiece(i).getPosition() == p) && (player[0].getGamePiece(i).getActive()))
				{
					g = player[0].getGamePiece(i);
				}
			}
			/*if (g == NULL)
			{
				return false;
			}*/
			if ((g.getRank() == 10) || (g.getRank() == -1))
			{
				return false;
			}
			else
			{
				g.setSelection(true);
				return true;
			}
		}
		else if (active == 1)
		{
			GamePiece g = new GamePiece();
			for (int i = 0; i < 40; i++)
			{
				if ((player[1].getGamePiece(i).getPosition() == p) && (player[0].getGamePiece(i).getActive()))
				{
					g = player[1].getGamePiece(i);
				}
			}
			/*if (g == NULL)
			{
				return false;
			}*/
			if ((g.getRank() == 10) || (g.getRank() == -1))
			{
				return false;
			}
			else
			{
				g.setSelection(true);
				return true;
			}
		}
		return false;
	}

	public boolean move(GamePiece y, Vector2D p)
	{
		//moves one position
		if (active == 0)
		{
			if (checkForCollision(p))
			{
				GamePiece g = new GamePiece();
				for (int i = 0; i < 40; i++)
				{
					if ((player[1].getGamePiece(i).getPosition() == p) && (player[1].getGamePiece(i).getActive()))
					{
						g = player[1].getGamePiece(i);
					}
				}
				if ((y.getRank() == 0) && (g.getRank() == 9))  //spy removing the marshal
				{
					g.setActive(false);
					y.setPosition(p);
					y.setShowRank(true);
					return true;
				}
				else if ((y.getRank() == 2) && (g.getRank() == 10)) //miner removing the bomb
				{
					g.setActive(false);
					y.setPosition(p);
					y.setShowRank(true);
					return true;
				}
				else if (y.getRank() == g.getRank())  //if the ranks are a tie
				{
					g.setActive(false);
					y.setActive(false);
					return true;
				}
				else if (y.getRank() > g.getRank())  // your rank is greater than their rank
				{
					g.setActive(false);
					y.setPosition(p);
					y.setShowRank(true);
					return true;
				}
				else //you are lower rank than the opponent
				{
					y.setActive(false);
					g.setShowRank(true);
					return true;
				}
			}
			else //move to that position
			{
				if ((p.getX() < 0.0f) || (p.getX() > 9.0f) || (p.getY() < 0.0f) || (p.getY() > 9.0f))
				{
					return false;
				}
				else
				{
					for (int i = 0; i < 40; i++)
					{
						if ((p == player[0].getGamePiece(i).getPosition()) && (player[0].getGamePiece(i).getActive()))
						{
							return false;
						}
					}
					y.setPosition(p);
					return true;
				}
			}
		}
		else if (active == 1)
		{
			if (checkForCollision(p))
			{
				GamePiece g = new GamePiece();
				for (int i = 0; i < 40; i++)
				{
					if ((player[0].getGamePiece(i).getPosition() == p) && (player[0].getGamePiece(i).getActive()))
					{
						g = player[0].getGamePiece(i);
					}
				}
				if ((y.getRank() == 0) && (g.getRank() == 9))
				{
					g.setActive(false);
					y.setPosition(p);
					y.setShowRank(true);
				}
				else if ((y.getRank() == 2) && (g.getRank() == 10))
				{
					g.setActive(false);
					y.setPosition(p);
					y.setShowRank(true);
				}
				else if (y.getRank() == g.getRank())
				{
					g.setActive(false);
					y.setActive(false);
					return true;
				}
				else if (y.getRank() > g.getRank())
				{
					g.setActive(false);
					y.setPosition(p);
					y.setShowRank(true);
				}
				else
				{
					y.setActive(false);
					g.setShowRank(true);
				}
			}
			else
			{
				if ((p.getX() < 0.0f) || (p.getX() > 9.0f) || (p.getY() < 0.0f) || (p.getY() > 9.0f))
				{
					return false;
				}
				else
				{
					for (int i = 0; i < 40; i++)
					{
						if ((p == player[1].getGamePiece(i).getPosition()) && (player[1].getGamePiece(i).getActive()))
						{
							return false;
						}
					}
					y.setPosition(p);
					return true;
				}
			}
		}
		return true;
	}
	
	public void draw(Graphics g)
	{
		for (int i = 0; i < 2; i++)
		{
			player[i].draw(g);
		}
	}

}

