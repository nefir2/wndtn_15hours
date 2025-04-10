using System.Text;
using System.Net.Sockets;
using System;
using System.Drawing;
using System.Reflection;

namespace Servers_Client
{
	class Client : IDisposable {
		private const int SIZE = 1024;
		private byte[] buffer;
		private readonly int port;
		private readonly string address;
		private readonly Socket socket;
		public Client(int port = 8888, string address = "127.0.0.1") {
			socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.IP);
			this.port = port;
			this.address = address;
			buffer = new byte[SIZE];
		}
		public void Connect() {
			socket.ConnectAsync(address, port);

			for (;;) {
				Send();
				Receive();
				Process();
			}
		}
		~Client() {
			this.Dispose();
		}

		public void Send() {
			Console.Out.Write("write a message: ");
			string message = Console.In.ReadLine()!;
			buffer = new byte[SIZE];
			int it = 0;
			foreach (byte b in Encoding.ASCII.GetBytes(message)) buffer[it++] = b;
			socket.Send(buffer);
		}

		public void Receive() {
			buffer = new byte[SIZE];
			socket.Receive(buffer);
		}

		public void Process() {
			Console.Out.WriteLine($"Received from server: {Encoding.UTF8.GetString(buffer)}");
		}

		public void Dispose()
		{
			socket.Disconnect(false);
			socket.Dispose();
		}
	}
	class Program
	{
		private static void Main() {
			using Client client = new Client();
			client.Connect();
		}
	}
}