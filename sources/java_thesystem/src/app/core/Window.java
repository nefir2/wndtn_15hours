package src.app.core;

import java.util.List;
import java.util.ArrayList;

import java.awt.Color;
import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.image.BufferStrategy;
import java.awt.event.MouseEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseMotionListener;

import javax.swing.JFrame;

import src.app.layers.Layer;
import src.app.events.Event;
import src.app.events.types.MouseMotionEvent;
import src.app.events.types.MousePressedEvent;
import src.app.events.types.MouseReleasedEvent;

public class Window extends Canvas {
	private BufferStrategy bs;
	private Graphics g;
	private JFrame frame;
	private Color color;
	private List<Layer> layers = new ArrayList<Layer>();

	public Window(String name, int width, int height, Color color) {
		this.color = color;
		setPreferredSize(new Dimension(width, height));
		init(name);

		addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				MousePressedEvent event = new MousePressedEvent(e.getButton(), e.getX(), e.getY());
				onEvent(event);
			}

			public void mouseReleased(MouseEvent e) {
				MouseReleasedEvent event = new MouseReleasedEvent(e.getButton(), getX(), getY());
				onEvent(event);
			}
		});
		
		addMouseMotionListener(new MouseMotionListener() {
			//@Override
			public void mouseMoved(MouseEvent e) {
				MouseMotionEvent event = new MouseMotionEvent(e.getX(), e.getY(), false);
				onEvent(event);
			}

			//@Override
			public void mouseDragged(MouseEvent e) {
				MouseMotionEvent event = new MouseMotionEvent(e.getX(), e.getY(), true);
				onEvent(event);
			}
		});

		render();
	}

	private void init(String name) {
		frame = new JFrame(name);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(this);
		frame.pack();
		frame.setLocationRelativeTo(null); //null = center of screen
		frame.setResizable(true);
		frame.setVisible(true);
	}

	private void render() {
		if (bs == null) createBufferStrategy(3);
		bs = getBufferStrategy();

		g = bs.getDrawGraphics();
		g.setColor(color);
		g.fillRect(0, 0, getWidth(), getHeight());
		onRender(g);
		g.dispose();
		bs.show();

		try {
			Thread.sleep(3);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		EventQueue.invokeLater(() -> render());
	}

	private void onRender(Graphics g) {
		for (int i = 0; i < layers.size(); i++) layers.get(i).onRender(g);
	}

	private void onEvent(Event event) {
		for (int i = layers.size() - 1; i >= 0 ; i--) layers.get(i).onEvent(event);
	}

	public void addLayer(Layer layer) {
		layers.add(layer);
	}
}