using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Marox
{
    namespace Serialization
    {
        [Serializable]
        public abstract class SERIALIZABLE
        {
            public byte[] Serialize()
            {
                try
                {
                    IFormatter formatter = new BinaryFormatter();
                    using (var ms = new MemoryStream())
                    {
                        formatter.Serialize(ms, this as dynamic);
                        return ms.ToArray();
                    }
                }
                catch (Exception)
                {
                    return null;
                }

            }

            public static dynamic Deserialize(byte[] bytes)
            {
                try
                {
                    using (var memStream = new MemoryStream())
                    {
                        var binForm = new BinaryFormatter();
                        memStream.Write(bytes, 0, bytes.Length);
                        memStream.Seek(0, SeekOrigin.Begin);
                        var obj = binForm.Deserialize(memStream);

                        return obj as dynamic;
                    }
                }
                catch (Exception)
                {
                    return null;
                }
            }
        }

        public sealed class Serializer
        {
            //todo: sprawdzić!!
            //todo: exceptions!
            public static Object DeserializeObject(byte[] arrBytes)
            {
                try
                {
                    using (var memStream = new MemoryStream())
                    {
                        var binForm = new BinaryFormatter();
                        memStream.Write(arrBytes, 0, arrBytes.Length);
                        memStream.Seek(0, SeekOrigin.Begin);
                        var obj = binForm.Deserialize(memStream);
                        return obj;
                    }
                }
                catch (Exception)
                {
                    return null;
                }
            }

            public static byte[] SerializeObject(Object obj)
            {
                try
                {
                    BinaryFormatter bf = new BinaryFormatter();
                    using (var ms = new MemoryStream())
                    {
                        bf.Serialize(ms, obj);
                        return ms.ToArray();
                    }
                }
                catch (Exception)
                {
                    return null;
                }
            }

            public static bool SerializeObjectToFile<T>(string fileName, T obj)
            {
                try
                {
                    IFormatter formatter = new BinaryFormatter();
                    Stream stream = new FileStream(fileName, FileMode.Create, FileAccess.Write, FileShare.None);
                    formatter.Serialize(stream, obj);
                    stream.Close();
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }
            }

            public static T DeserializeObjectFromFile<T>(string fileName) where T: class
            {
                T obj = default(T);
                try
                {
                    if (!File.Exists(fileName))
                    {
                        return obj;
                    }

                    IFormatter formatter = new BinaryFormatter();
                    Stream stream = new FileStream(fileName, FileMode.Open, FileAccess.Read, FileShare.Read);
                    obj = formatter.Deserialize(stream) as T;
                    stream.Close();

                    if (obj == null)
                    {
                        return obj;
                    }
                }
                catch (Exception)
                {
                    return null;
                }

                return obj;
            }

        }
    }
}
