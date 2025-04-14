package src.app.events.types;

import src.app.events.Event;

public class MousePressedEvent extends MouseButtonEvent {
	public MousePressedEvent(int keyCode, int x, int y) {
		super(Event.Type.MOUSE_PRESSED, keyCode, x, y);
	}
}
