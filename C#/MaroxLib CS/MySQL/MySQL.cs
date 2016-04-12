using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Net;
using System.Text;
using System.Windows.Forms;

namespace Marox
{
    public static class MySQL
    {
        private static MySqlConnection m_conn = new MySqlConnection();

        public static MySqlConnection MySqlConnectionHandle
        {
            get
            {
                return m_conn;
            }
        }
        public static System.Data.ConnectionState State
        {
            get
            {
                return m_conn.State;
            }
        }
        public static bool IsOpen
        {
            get
            {
                return (m_conn.State == System.Data.ConnectionState.Open);
            }
        }
        public static bool IsConnectionSet
        {
            get
            {
                return (m_conn.ConnectionString != String.Empty);
            }
        }


        public static void SetConnection(string ip, string username, string password)
        {
            m_conn.ConnectionString = String.Format("Server={0};Username={1};Password={2};", ip, username, password);
        }
        public static void SetConnection(string ip, string username, string password, string databaseName)
        {
            m_conn.ConnectionString = String.Format("Server={0};Username={1};Password={2};Database={3};", ip, username, password, databaseName);
        }
        public static void SetConnection(string ip, UInt16 port, string username, string password)
        {
            m_conn.ConnectionString = String.Format("Server={0};Port={1};Username={2};Password={3};", ip, port, username, password);
        }
        public static void SetConnection(string ip, UInt16 port, string username, string password, string databaseName)
        {
            m_conn.ConnectionString = String.Format("Server={0};Port={1};Username={2};Password={3};Database={4};", ip, port, username, password, databaseName);
        }
        public static void SetConnectionWithCharset(string ip, string username, string password, string charset)
        {
            m_conn.ConnectionString = String.Format("Server={0};Username={1};Password={2};Charset={3};", ip, username, password, charset);
        }
        public static void SetConnectionWithCharset(string ip, string username, string password, string charset, string databaseName)
        {
            m_conn.ConnectionString = String.Format("Server={0};Username={1};Password={2};Charset={3};Database={4};", ip, username, password, charset, databaseName);
        }
        public static void SetConnectionWithCharset(string ip, UInt16 port, string username, string password, string charset)
        {
            m_conn.ConnectionString = String.Format("Server={0};Port={1};Username={2};Password={3};Charset={4};", ip, port, username, password, charset);
        }
        public static void SetConnectionWithCharset(string ip, UInt16 port, string username, string password, string charset, string databaseName)
        {
            m_conn.ConnectionString = String.Format("Server={0};Port={1};Username={2};Password={3};Charset={4};Database={5};", ip, port, username, password, charset, databaseName);
        }

        public static void SetDatabase(string dbName)
        {
            try
            {
                m_conn.Open();
                m_conn.ChangeDatabase(dbName);
                m_conn.Close();
            }
            catch (Exception)
            {
                throw;
            }
        }

        public static bool TestConnection()
        {
            try
            {
                m_conn.Open();

                if (m_conn.State != System.Data.ConnectionState.Open)
                {
                    return false;
                }

                m_conn.Close();
            }
            catch (MySqlException ex)
            {
                throw;
            }

            return true;
        }

        public static DataSet ExecuteQuery(string query)
        {
            if (!IsConnectionSet)
            {
                throw (new InvalidOperationException("MySQL connection is not set. Use MySQL.SetConnection befor executing oprations"));
            }

            try
            {
                MySqlCommand cmd = new MySqlCommand(query, m_conn);
                MySqlDataAdapter dataAdapter = new MySqlDataAdapter(query, m_conn);

                DataSet ds = new DataSet();
                dataAdapter.Fill(ds);

                m_conn.Close();

                return ds;
            }
            catch (MySqlException ex)
            {
                throw;
            }





        }



    }
}


//todo: prepared statements