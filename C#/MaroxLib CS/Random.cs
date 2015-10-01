using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Marox
{
    namespace Tools
    {
        public static class Random
        {
            private static System.Random rnd = new System.Random();
            public static int GetRandomNumber(int range_from, int range_to)
            {
                return Marox.Tools.Random.rnd.Next(range_from, range_to + 1);
            }
            public static double GetRandomNumber(double range_from, double range_to)
            {
                return Marox.Tools.Random.rnd.NextDouble() * (range_to - range_from) + range_from;
            }
        }
    }
}
