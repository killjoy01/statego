package StrategoJava;

import java.awt.Graphics;
import java.awt.Image;

public class Sprite {

	//Texture texture;
	protected Image texture;
	protected Vector2D position;

	protected float scalex;
	protected float scaley;
	protected float rotation;
	protected Rect rect;
	
	public Sprite()
	{
		texture = null;
		position = new Vector2D();
		position.setX(-1);
		position.setY(-1);
		scalex = 0;
		scaley = 0;
		rotation = 0;
	}
	
	public void init(Image i, Vector2D a_v, float a_s_x, float a_s_y, float a_r/*, RECT recta */)
	{
		texture = i;
		position = a_v;
		scalex = a_s_x;
		scaley = a_s_y;
		rotation = a_r;
	}
	
	public void setTexture(Image i) {texture = i;}
	public Image getTexture() {return texture;}
	public void setPosition(Vector2D a_v) {position = new Vector2D(a_v.getX(), a_v.getY());}
	public Vector2D getPosition() {return position;}
	public void setScaleX(float a_s_x) {scalex = a_s_x;}
	public void setScaleY(float a_s_y) {scaley = a_s_y;}
	public void setRotation(float a_r) {rotation = a_r;}
	public float getScaleX() {return scalex;}
	public float getScaleY() {return scaley;}
	public float getRotation() {return rotation;}
	public void setRect(Rect r) {rect = r;}
	public Rect getRect() {return rect;}
	
	public void draw(Graphics g)
	{
		g.drawImage(texture, position.getX(), position.getY(), null);
	}
};
