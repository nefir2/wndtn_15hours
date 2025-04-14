package src.app.events.types;

import src.app.events.Event;

public class MouseReleasedEvent extends MouseButtonEvent {
	public MouseReleasedEvent(int keyCode, int x, int y) {
		super(Event.Type.MOUSE_RELEASED, keyCode, x, y);
	}
}
