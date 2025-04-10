import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.io.IOException;
import java.util.Scanner;

public class Client {
	private static final short SIZE = 1024;
	private int port;
	private String ipaddress;
	private InetAddress serversAddress;
	private DatagramSocket socket;
	private Thread t2;
	private String message;
	private Scanner scanner;

	public Client(int port, String ipaddress) {
		this.port = port;
		this.ipaddress = ipaddress;
		serversAddress = null;
		this.scanner = new Scanner(System.in);
	}

	private void init() {
		t2 = new Thread(() -> receive());
		try {
			socket = new DatagramSocket();
			serversAddress = InetAddress.getByName(ipaddress);
			socket.connect(serversAddress, port);
		} catch (Exception e) {
			e.printStackTrace();
		}
		t2.start();
	}

	public void connect() {
		init();
		for (;;) {
			System.out.print("Enter a message: ");
			message = scanner.nextLine();
			send(message.getBytes());
		}
	}

	private void receive() {
		try {
			byte[] data = new byte[SIZE];
			DatagramPacket packet = new DatagramPacket(data, data.length);
			socket.receive(packet);
			process(packet.getData());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void send(byte[] data) {
		try {
			DatagramPacket packet = new DatagramPacket(data, data.length);
			socket.send(packet);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void process(byte[] data) {
		System.out.println("packet from: " + port + ":" + ipaddress);
		System.out.println("data: " + new String(data));
	}

	public static void main(String[] args) {
		Client client = new Client(8888, "localhost");
		client.connect();
	}
}