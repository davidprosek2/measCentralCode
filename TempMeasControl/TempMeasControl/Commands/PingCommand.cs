using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TempMeasControl.Commands
{
    internal class PingCommand : ICommand
    {
        private readonly MessageProcessor meassageProcessor;

        public PingCommand(MessageProcessor meassageProcessor)
        {
            this.meassageProcessor = meassageProcessor;
        }

        public void Execute()
        {
            meassageProcessor.Ping();   
        }
    }
}
