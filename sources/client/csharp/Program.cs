namespace Servers_Client
{
	class Program
	{
		private static void Main() {
			using Client client = new Client();
			client.Connect();
		}
	}
}