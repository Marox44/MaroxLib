using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Marox.ExtensionMethods;
using System.Collections.Generic;

namespace UNIT_TESTS_CS
{
    class Dog
    {
        public Dog()
        {
            this.ID = Marox.Tools.Random.GetRandomNumber(1, int.MaxValue - 1);
        }
        public string Name { get; set; }
        public int Age { get; set; }
        public int ID { get; set; }
        public List<Dog> Children { get; set; }
    }

    [TestClass]
    public class ExtensionMethods_UnitTest
    {
        [TestMethod]
        public void DeepCopying_1()
        {
            Dog dog_1 = new Dog()
            {
                Name = "Azor",
                Age = 12,
                Children = new List<Dog>() 
                {
                    new Dog()
                    {
                        Name = "Burek",
                        Age = 15
                    }
                }
            };

            Dog dog_2 = dog_1;

            Assert.IsTrue(dog_1.Equals(dog_2), "1");
            Assert.IsTrue(object.Equals(dog_1, dog_2), "2");
            Assert.IsTrue(object.ReferenceEquals(dog_1, dog_2), "3");


            Dog dog_3 = dog_1.Copy();

            Assert.IsFalse(dog_1.Equals(dog_3), "4");
            Assert.IsFalse(object.Equals(dog_1, dog_3), "5");
            Assert.IsFalse(object.ReferenceEquals(dog_1, dog_3), "6");
        }
    }
}
