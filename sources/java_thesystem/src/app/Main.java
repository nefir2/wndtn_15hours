package src.app;

import java.awt.Color;

import src.app.core.Window;
import src.app.sandbox.Example;

public class Main {
	public static void main(String[] args) {
		Window window = new Window("Window", 960, 640, Color.BLACK);
		window.addLayer(new Example("Layer1", Color.BLUE));
		window.addLayer(new Example("Layer2", Color.RED));
		window.addLayer(new Example("Layer3", Color.DARK_GRAY));
	}
}