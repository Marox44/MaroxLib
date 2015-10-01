using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Marox
{
    public abstract class THREAD
    {
        public void threadStart(bool isBackground = true, string threadName = null)
        {
            if (!this.isThreadRunning)
            {
                this.isThreadRunning = true;

                try
                {
                    this.h_thread = new System.Threading.Thread(() => this.run());
                    if (isBackground)
                    {
                        this.h_thread.IsBackground = true;
                    }
                    if (threadName != null)
                    {
                        this.h_thread.Name = threadName;
                    }

                    this.h_thread.Start();
                }
                catch (Exception ex)
                {
                    Alert.Warning(ex.Message);
                }
            }
        }
        public void threadStop()
        {
            this.isThreadRunning = false;
        }
        abstract protected void run();


        public System.Threading.Thread h_thread = new Thread(new ThreadStart(() => { }));
        public bool isThreadRunning { get; set; }


        //** STATIC **//

        public static Thread CreateThreadFromFunction(Action func, string name = "", bool background = true, bool autostart = false)
        {
            Thread t = new Thread(new ThreadStart(func));
            if (background)
            {
                t.IsBackground = true;
            }
            if (autostart)
            {
                t.Start();
            }
            if(!String.IsNullOrEmpty(name))
            {
                t.Name = name;
            }

            return t;
        }
    }
}
