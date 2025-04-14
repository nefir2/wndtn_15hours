package src.app.events;

public class Event {
	public enum Type {
		MOUSE_MOVED,
		MOUSE_PRESSED,
		MOUSE_RELEASED
	}

	private Type type;
	public boolean handled;
	
	protected Event(Type type) {
		this.type = type;
		handled = false;
	}

	public Type getType() {
		return type;
	}
}
