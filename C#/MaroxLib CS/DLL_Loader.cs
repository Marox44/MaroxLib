using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

/* - wczytaj dll z pliku
 *   - jeśli nie ma pliku
 *   - jeśli zły plik
 * - wywołaj statyczną metodę: 
 *   - bez parametrów 
 *   - z parametrami
 *   - void
 *   - return type
 * - obiekt:
 *   - utwórz instancję
 *   - konstruktor bez parametrów
 *   - konstruktor z parametrami
 *   - wywołaj metodę obiektu
 *     - bez parametrów
 *     - z parametrami
 *   GetExportedTypes()
 *   GetConstructors()
 *   GetMethod() -> Invoke
 * 
 * AssemblyInfo:
 *  - werjsa DLL'a
 *  - daty utworzenia itd ?
 * 
 */

namespace Marox
{
    namespace DLL
    {
        public sealed class DLL
        {
            public DLL(Assembly assembly)
            {
                this.Assembly = assembly;
                this.ExportedTypes = this.Assembly.GetExportedTypes().ToList<Type>();
            }

            public object InvokeStaticMethod(string methodAddressFull, Type[] parameterTypes, object[] parameters)
            {
                //todo: method/namespace not found
                //todo: co jeśli źle napisany adres

                try
                {
                    string methodType = methodAddressFull.Substring(0, methodAddressFull.LastIndexOf('.'));
                    if (methodType == null)
                    {
                        return null;
                    }

                    string methodName = methodAddressFull.Split('.').Last();
                    if (methodName == null)
                    {
                        return null;
                    }

                    var type = this.Assembly.GetType(methodType);
                    if (type == null)
                    {
                        return null;
                    }

                    var method = parameterTypes == null ? type.GetMethod(methodName) : type.GetMethod(methodName, parameterTypes);
                    if (method == null)
                    {
                        return null;
                    }

                    var result = method.Invoke(null, parameters);
                    if (result == null)
                    {
                        string returnStr = "Method returned void";
                        return returnStr;
                    }

                    return result;
                }
                catch (Exception ex)
                {
                    return null;
                }

            }
            
            public T InvokeStaticMethod<T>(string methodAddressFull, Type[] parameterTypes, object[] parameters) where T: class
            {
                //todo: method/namespace not found
                //todo: co jeśli źle napisany adres

                try
                {
                    string methodType = methodAddressFull.Substring(0, methodAddressFull.LastIndexOf('.'));
                    if (methodType == null)
                    {
                        return null;
                    }

                    string methodName = methodAddressFull.Split('.').Last();
                    if (methodName == null)
                    {
                        return null;
                    }

                    var type = this.Assembly.GetType(methodType);
                    if (type == null)
                    {
                        return null;
                    }

                    var method = parameterTypes == null ? type.GetMethod(methodName) : type.GetMethod(methodName, parameterTypes);
                    if (method == null)
                    {
                        return null;
                    }

                    var result = method.Invoke(null, parameters);
                    if (result == null)
                    {
                        //string returnStr = "Method returned void";
                        return default(T);
                    }

                    return result as T;
                }
                catch (Exception ex)
                {
                    return null;
                }

            }

            public dynamic CreateTypeInstance(string typeFull, params object[] constructorArgs)
            {
                try
                {
                    var type = this.Assembly.GetType(typeFull);
                    if (type == null)
                    {
                        return null;
                    }

                    dynamic instance = Activator.CreateInstance(type, constructorArgs);

                    return instance;
                }
                catch (Exception ex)
                {
                    return null;
                }
            }

            public object InvokeInstanceMethod(object instance, string methodName, Type[] parameterTypes, object[] parameters)
            {
                try
                {
                    Type type = instance.GetType();
                    if (type == null)
                    {
                        return null;
                    }

                    var method = parameterTypes == null ? type.GetMethod(methodName) : type.GetMethod(methodName, parameterTypes);
                    if (method == null)
                    {
                        return null;
                    }

                    var result = method.Invoke(instance, parameters);
                    if (result == null)
                    {
                        string returnStr = "Method returned void";
                        return returnStr;
                    }

                    return result;
                }
                catch (Exception ex)
                {
                    return null;
                }
            }

            public T InvokeInstanceMethod<T>(object instance, string methodName, Type[] parameterTypes, object[] parameters) where T: class
            {
                try
                {
                    Type type = instance.GetType();
                    if (type == null)
                    {
                        return null;
                    }

                    var method = parameterTypes == null ? type.GetMethod(methodName) : type.GetMethod(methodName, parameterTypes);
                    if (method == null)
                    {
                        return null;
                    }

                    var result = method.Invoke(instance, parameters);
                    if (result == null)
                    {
                        //string returnStr = "Method returned void";
                        return default(T);
                    }

                    return result as T;
                }
                catch (Exception ex)
                {
                    return null;
                }
            }


            //
            public List<Type> ExportedTypes { get; }
            public Assembly Assembly { get; }
        }
    }
}
