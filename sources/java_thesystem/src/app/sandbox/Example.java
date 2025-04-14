package src.app.sandbox;

import src.app.events.Event;
import src.app.layers.Layer;

public class Example extends Layer {
	public void onEvent(Event event) {
		System.out.println(event);
	}
}
