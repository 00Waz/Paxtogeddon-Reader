using System;
using System.Net;

namespace Companion
{
    internal class PaxtogeddonReader : WebClient
    {
        private int Timeout = 30000;

        public PaxtogeddonReader(int timeout)
        {
            Timeout = timeout;
        }

        protected override WebRequest GetWebRequest(Uri uri)
        {
            WebRequest request = base.GetWebRequest(uri);
            request.Timeout = Timeout;
            return request;
        }
    }
}
