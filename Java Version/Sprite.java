package StrategoJava;

public class Sprite {

	//Texture texture;
	protected Vector2D position;

	protected float scalex;
	protected float scaley;
	protected float rotation;
	protected Rect rect;
	
	public Sprite()
	{
		position = new Vector2D();
		scalex = 0;
		scaley = 0;
		rotation = 0;
	}
	
	public void init(/*Texture texture*/Vector2D a_v, int a_s_x, int a_s_y, int a_r/*, RECT recta */)
	{
		position = a_v;
		scalex = a_s_x;
		scaley = a_s_y;
		rotation = a_r;
	}
	
	//public void getTexture
	//public void setTexture
	public void setPosition(Vector2D a_v) {position = a_v;}
	public Vector2D getPosition() {return a_v;}
	public void setScaleX(float a_s_x) {scalex = a_s_x;}
	public void setScaleY(float a_s_y) {scaley = a_s_y;}
	public void setRotation(float a_r) {rotation = a_r;}
	public float getScaleX() {return scalex;}
	public float getScaleY() {return scaley;}
	public float getRotation() {return rotation;}
	public void setRect(Rect r) {rect = r;}
	public Rect getRect() {return rect;}
};
