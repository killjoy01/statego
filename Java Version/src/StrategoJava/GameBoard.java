package StrategoJava;

import java.awt.Graphics;

public class GameBoard {
	private Player player[];
	int active;
	
	public GameBoard()
	{
		player = new Player[2];
		for (int i = 0; i < 2; ++i)
		{
			player[i] = new Player();
		}
		active = 0;
	}
	
	public Player getPlayer(int i) {return player[i];}
	public void setPlayer(int i, Player p) {player[i] = p;}
	public void setActive(int a) {active = a;}
	public int getActive() {return active;}
	
	public void displayNewPosition(GamePiece p)
	{
		int i = 0;
		int left = p.getPosition().getX() - 64, right = p.getPosition().getX() + 64, up = p.getPosition().getY() - 64, down = p.getPosition().getY() + 64;
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
				Framework.movepositions[i].setX(leftCheck.getX());
				Framework.movepositions[i].setY(leftCheck.getY());
				i++;
				flagleft = false;
			}
			else if (left <= -1)
			{
				flagleft = false;
			}
			else
			{
				Framework.movepositions[i].setX(leftCheck.getX());
				Framework.movepositions[i].setY(leftCheck.getY());
				i++;
				left -= 64;
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
				Framework.movepositions[i].setX(rightCheck.getX());
				Framework.movepositions[i].setY(rightCheck.getY());
				i++;
				flagright = false;
			}
			else if (right >= 640)
			{
				flagright = false;
			}
			else
			{
				Framework.movepositions[i].setX(rightCheck.getX());
				Framework.movepositions[i].setY(rightCheck.getY());
				i++;
				right += 64;
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
				Framework.movepositions[i].setX(upCheck.getX());
				Framework.movepositions[i].setY(upCheck.getY());
				i++;
				flagup = false;
			}
			else if (up <= -1)
			{
				flagup = false;
			}
			else
			{
				Framework.movepositions[i].setX(upCheck.getX());
				Framework.movepositions[i].setY(upCheck.getY());
				i++;
				up -= 64;
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
				Framework.movepositions[i].setX(downCheck.getX());
				Framework.movepositions[i].setY(downCheck.getY());
				i++;
				flagdown = false;
			}
			else if (down >= 640)
			{
				flagdown = false;
			}
			else
			{
				Framework.movepositions[i].setX(downCheck.getX());
				Framework.movepositions[i].setY(downCheck.getY());
				i++;
				down += 64;
			}
		}
	}
	
	public boolean checkForCollision(Vector2D p)
	{
		System.out.println(p.getX());
		System.out.println(p.getY());
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
			GamePiece g = null;;
			for (int i = 0; i < 40; i++)
			{
				if (((player[0].getGamePiece(i).getPosition().getX() / 64) == (p.getX() / 64)) && 
				    ((player[0].getGamePiece(i).getPosition().getY() / 64) == (p.getY() / 64)) && 
				    (player[0].getGamePiece(i).getActive()))
				{
					g = player[0].getGamePiece(i);
				}
			}
			if (g == null)
			{
				return false;
			}
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
			System.out.println("Here!");
			GamePiece g = null;
			for (int i = 0; i < 40; i++)
			{
				if (((player[1].getGamePiece(i).getPosition().getX() / 64) == (p.getX() / 64)) && 
					((player[1].getGamePiece(i).getPosition().getY() / 64) == (p.getY() / 64)) && 
					(player[1].getGamePiece(i).getActive()))
				{
					g = player[1].getGamePiece(i);
				}
			}
			if (g == null)
			{
				return false;
			}
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
				System.out.println("Entered Collision");
				GamePiece g = new GamePiece();
				for (int i = 0; i < 40; ++i)
				{
					if ((((player[1].getGamePiece(i).getPosition().getX() / 64) == (p.getX() / 64)) &&
						 ((player[1].getGamePiece(i).getPosition().getY() / 64) == (p.getY() / 64)))
						&& (player[1].getGamePiece(i).getActive()))
					{
						System.out.println("Got Piece");
						g = player[1].getGamePiece(i);
					}
				}
				System.out.println("Resolving Collision");
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
					System.out.println("Take Piece!");
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
				if (((p.getX() / 64) < 0.0f) || ((p.getX() / 64) > 9.0f) || ((p.getY() / 64) < 0.0f) || ((p.getY() / 64) > 9.0f))
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
					if (((player[0].getGamePiece(i).getPosition().getX() / 64) == (p.getX() / 64) &&
						 ((player[0].getGamePiece(i).getPosition().getY() / 64) == (p.getY() / 64)))
							&& (player[0].getGamePiece(i).getActive()))
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
					System.out.println("Take Piece!");
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
				if (((p.getX() / 64) < 0.0f) || ((p.getX() / 64) > 9.0f) || ((p.getY() / 64) < 0.0f) || ((p.getY() / 64) > 9.0f))
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

