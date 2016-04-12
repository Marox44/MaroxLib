using System;
using System.Net;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Data;
using System.Xml;

namespace UNIT_TESTS_CS
{
    [TestClass]
    public class MySQL_UnitTest
    {
        [TestMethod]
        public void CheckConnection_1()
        {
            Marox.MySQL.SetConnection("ensembldb.ensembl.org", "anonymous", "");

            bool result = false;
            try
            {
                result = Marox.MySQL.TestConnection();
            }
            catch (Exception ex)
            {
                Assert.Fail(ex.Message);
            }

            Assert.IsTrue(result, "MySQL test connection no. 1 failed!");
        }

        [TestMethod]
        public void CheckConnection_2()
        {
            Marox.MySQL.SetConnection("martdb.ensembl.org", 5316, "anonymous", "");

            bool result = false;
            try
            {
                result = Marox.MySQL.TestConnection();
            }
            catch (Exception ex)
            {
                Assert.Fail(ex.Message);
            }

            Assert.IsTrue(result, "MySQL test connection no. 2 failed!");
        }

        [TestMethod]
        public void ExecuteSampleSQLQuery_1()
        {
            Marox.MySQL.SetConnection("useastdb.ensembl.org", "anonymous", "");
            Marox.MySQL.SetDatabase("bos_taurus_core_83_31");

            var isConnectionSuccess = Marox.MySQL.TestConnection();
            Assert.IsTrue(isConnectionSuccess, "TestConnection failed!");

            try
            {
                var data = Marox.MySQL.ExecuteQuery("SELECT * FROM bos_taurus_core_83_31.coord_system;");

                Assert.IsTrue((data.Tables.Count > 0), "Selecting data from DB to DataSet failed");
            }
            catch (Exception ex)
            {
                Assert.Fail(ex.Message);
            }
        }

        [TestMethod]
        public void ExecuteSampleProcedure()
        {
            Marox.MySQL.SetConnection("server.marox44.pl", "cacti", "cacti");
            Marox.MySQL.SetDatabase("cacti");
            //test_select_1



            
        }


        

    }
}

//todo: test bez połączenia
//todo: select bez połączenia
//todo: select bez wybrania bazy
//todo: wybrana zła baza
