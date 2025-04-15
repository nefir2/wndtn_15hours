using System;
using System.Text;
using System.Linq;
using System.Net.Sockets;

namespace Servers_Client {
	class Client : IDisposable {
		private const int SIZE = 1024;
		private byte[] buffer;
		private int bufferSize;
		private readonly int port;
		private readonly string address;
		private readonly Socket socket;
		public Client(int port = 8888, string address = "127.0.0.1") {
			socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.IP);
			this.port = port;
			this.address = address;
			buffer = new byte[SIZE];
			Console.InputEncoding = Encoding.UTF8;
		}
		~Client() {
			this.Dispose();
		}
		
		public void Connect() {
			socket.ConnectAsync(address, port);

			for (;;) {
				Send();
				Console.Out.WriteLine("count of sent bytes: " + bufferSize);
				Receive();
				Process();
			}
		}

		public void Send() {
			Console.Out.Write("write a message: ");
			Console.InputEncoding = Encoding.UTF8;
			string message = Console.In.ReadLine()!; //rus signs not working idk why
			if (message.Length > SIZE) {
				Console.Out.WriteLine("message too long.");
				return;
			}
			else if (message.Length == 0) {
				Console.Out.WriteLine("message too short.");
				return;
			}
			buffer = new byte[message.Length];
			int it = 0;
			Console.Out.WriteLine("message for send: " + message);
			foreach (byte b in Encoding.UTF8.GetBytes(message.ToArray())) buffer[it++] = b;
			bufferSize = socket.Send(buffer.Take(it).ToArray(), 0, it, SocketFlags.None);
		}

		public void Receive() {
			buffer = new byte[SIZE];
			bufferSize = socket.Receive(buffer);
		}

		public void Process() {
			Console.Out.WriteLine($"Received from server {{{address}:{port}}}: {Encoding.UTF8.GetString(buffer)}");
		}

		public void Dispose()
		{
			socket.Disconnect(false);
			socket.Dispose();
		}
	}
}