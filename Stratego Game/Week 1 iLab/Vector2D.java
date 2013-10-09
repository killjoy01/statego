package StrategoJava;

public class Vector2D {
	private int x, y;

	public Vector2D(){x = 0; y = 0;}
	public Vector2D(int a_x, int a_y){x = a_x; y = a_y;}
	public void setX(int a_x){x = a_x;}
	public void setY(int a_y){y = a_y;}
	public int getX(){return x;}
	public int getY(){return y;}
};
