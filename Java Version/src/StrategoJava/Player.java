package StrategoJava;

import java.awt.Graphics;

public class Player {
	private GamePiece pieces[];
	private int displayColor;
	
	public Player()
	{
		pieces = new GamePiece[40];
		for (int i = 0; i < 40; ++i)
		{
			pieces[i] = new GamePiece();
		}
		displayColor = 0;
	}
	
	void init (int c)
	{
		if (c == 1)
		{
			displayColor = 0;
		}
		else
		{
			displayColor = 1;
		}
	}
	
	public void setGamePiece (int i, GamePiece g)
	{
		pieces[i] = g;
	}
	
	public GamePiece getGamePiece(int i)
	{
		return pieces[i];
	}
	
	public void setColor (int c)
	{
		displayColor = c;
	}
	
	public int getColor ()
	{
		return displayColor;
	}
	
	public void draw(Graphics g)
	{
		for (int i = 0; i < 40; ++i)
		{
			pieces[i].draw(g);
		}
	}
	
	public boolean checkForCollision(Vector2D p)
	{
		for (int i = 0; i < 40; ++i)
		{
			if ((pieces[i].getPosition().getX() == p.getX()) && (pieces[i].getPosition().getY() == p.getY()))
			{
				return true;
			}
		}
		return false;
	}
}
