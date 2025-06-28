using System.Threading.Tasks;

namespace Companion
{
    internal sealed class ESP32Connect
    {
        internal async static Task<string> Get(string ipAddress, string route, int timeout)
        {
            string response = string.Empty;

            await Task.Run(() =>
            {
                try
                {
                    using (PaxtogeddonReader paxtogeddonReader = new PaxtogeddonReader(timeout))
                    {
                        response = paxtogeddonReader.DownloadString($"http://{ipAddress}{route}");
                    }
                }
                catch
                {
                    response = string.Empty;
                }
            });

            return response;
        }
    }
}
