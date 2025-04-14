package src.app.sandbox;

import java.awt.Color;
import java.awt.Point;
import java.awt.Graphics;
import java.awt.Rectangle;

import java.util.Random;

import src.app.layers.Layer;
import src.app.events.Event;
import src.app.events.Dispatcher;
import src.app.events.types.MouseMotionEvent;
import src.app.events.types.MousePressedEvent;
import src.app.events.types.MouseReleasedEvent;

public class Example extends Layer {
	private String name;
	private Color color;
	private Rectangle rect;
	private int prevX, prevY;
	private boolean dragging;

	private static final Random random = new Random();

	public Example(String name, Color color) {
		this.name = name;
		this.color = color;
		dragging = false;

		rect = new Rectangle(
			random.nextInt(100) + 150,
			random.nextInt(100) + 250,
			random.nextInt(100) + random.nextInt(120),
			random.nextInt(100) + random.nextInt(240)
		);
		System.out.println("rect \"" + name + "\" generated on positions: x" + rect.x + " y" + rect.y + ". with sizes: w" + rect.width + " h" + rect.height + ".");
	}
	
	public void onEvent(Event event) {
		Dispatcher dispatcher = new Dispatcher(event);

		if (event.getType().equals(Event.Type.MOUSE_PRESSED)) dispatcher.dispatch(event.getType(), (Event e) -> onPressed((MousePressedEvent)event));
		if (event.getType().equals(Event.Type.MOUSE_RELEASED)) dispatcher.dispatch(event.getType(), (Event e) -> onReleased((MouseReleasedEvent)event));
		if (event.getType().equals(Event.Type.MOUSE_MOVED)) dispatcher.dispatch(event.getType(), (Event e) -> onMoved((MouseMotionEvent)event));

		// // у него написано вот так, и почему-то работает правильно. я не понял почему...
		// dispatcher.dispatch(Event.Type.MOUSE_PRESSED, (Event e) -> onPressed((MousePressedEvent)event));
		// dispatcher.dispatch(Event.Type.MOUSE_RELEASED, (Event e) -> onPressed((MousePressedEvent)event));
		// dispatcher.dispatch(Event.Type.MOUSE_MOVED, (Event e) -> onPressed((MousePressedEvent)event));
	}

	public void onRender(Graphics g) {
		g.setColor(color);
		g.fillRect(rect.x, rect.y, rect.width, rect.height);

		g.setColor(Color.WHITE);
		g.drawString(name, rect.x + 15, rect.y + 35);
	}

	private boolean onPressed(MousePressedEvent event) {
		System.out.println("mouse pressed: " + event.getKeyCode());
		if (rect.contains(new Point(event.getX(), event.getY()))) dragging = true;
		return dragging;
	}

	private boolean onReleased(MouseReleasedEvent event) {
		System.out.println("mouse released: " + event.getKeyCode());
		return dragging = false;
	}

	private boolean onMoved(MouseMotionEvent event) {
		//System.out.println("mouse moved: x" + event.getX() + " y" + event.getY() + ". isdragged: " + event.getDragged());
		if (dragging) {
			rect.x += event.getX() - prevX;
			rect.y += event.getY() - prevY;
		}
		prevX = event.getX();
		prevY = event.getY();
		return dragging;
	}
}
