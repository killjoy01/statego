package StrategoJava;

public class Rect {
	private Vector2D min, max;
	
	public Rect() {min = new Vector2D(); max = new Vector2D();}
	public Rect(Vector2D a_min, Vector2D a_max) {min = a_min; max = a_max;}
	public boolean isWithin (Rect r)
	{
		return ((min.getX() >= r.min.getX()) && (min.getY() >= r.min.getY()) && (r.max.getX() <= r.max.getX()) && (r.max.getY() <= r.max.getY()));
	}

}
