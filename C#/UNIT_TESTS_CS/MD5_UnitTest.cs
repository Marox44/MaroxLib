using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;

namespace UNIT_TESTS_CS
{
    [TestClass]
    public class MD5_UnitTest
    {
        [TestMethod]
        public void CheckFileHash()
        {
            string correct = "C711C220A309482ABB45CACA0BC5182B";

            //file
            string path = "sampleTextFile.txt";

            //check md5
            var md5_1 = Marox.MD5.HashFile(path);

            Assert.AreEqual<string>(correct, md5_1, "Incorrect file hash!");
        }

        [TestMethod]
        public void CheckStringHash()
        {
            //pattern [pingwin]
            var stringToHash = "pingwin";
            var correct = "62f6ca0dfc3626c7b68bed075d17d75f";

            var result = Marox.MD5.HashString(stringToHash);

            Assert.AreEqual(correct, result, ignoreCase: true);
        }
    }
}
