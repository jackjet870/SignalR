﻿using System.Threading.Tasks;

namespace SignalR.Hubs
{
    public abstract class Hub : IHub
    {
        public IClientAgent Agent { get; set; }

        /// <summary>
        /// A dynamic object that represents all clients connected to this hub (not hub instance).
        /// </summary>
        public dynamic Clients
        {
            get
            {
                return Agent;
            }
        }

        /// <summary>
        /// A dynamic object that represents the calling client.
        /// </summary>
        public dynamic Caller { get; set; }

        /// <summary>
        /// Provides information about the calling client.
        /// </summary>
        public HubContext Context { get; set; }

        /// <summary>
        /// The group manager for this hub instance.
        /// </summary>
        public IGroupManager Groups { get; set; }
    }
}