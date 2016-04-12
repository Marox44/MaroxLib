using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Marox
{
    namespace ExtensionMethods
    {
        public static partial class ExtensionMethod
        {
            public static void Swap<T>(this IList<T> list, int firstIndex, int secondIndex)
            {
                System.Diagnostics.Contracts.Contract.Requires(list != null);
                System.Diagnostics.Contracts.Contract.Requires(firstIndex >= 0 && firstIndex < list.Count);
                System.Diagnostics.Contracts.Contract.Requires(secondIndex >= 0 && secondIndex < list.Count);
                if (firstIndex == secondIndex)
                {
                    return;
                }
                T temp = list[firstIndex];
                list[firstIndex] = list[secondIndex];
                list[secondIndex] = temp;
            }
        }
    }
}
