package StrategoJava;

public class Player {
	private GamePiece pieces[];
	private int displayColor;
	
	public Player()
	{
		pieces = new GamePiece[40];
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
}
