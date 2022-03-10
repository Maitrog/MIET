using lab2_csharp;
using System;
using System.IO;
using Xunit;
using Xunit.Abstractions;

namespace UnitTest.Tests
{
    public class UnitTest
    {

        [Fact]
        public void IfAllInputArgumentsZero_ThenWriteFive()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n0\n0\n0\n0\n0";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("5", stringWriter.ToString());
        }

        [Fact]
        public void Test2()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "5\n3\n4\n3\n6\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("2 -3 7", stringWriter.ToString());
        }

        [Fact]
        public void IfABCEZeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n0\n0\n3\n0\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 3", stringWriter.ToString());
        }

        [Fact]
        public void IfACDFZeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n3\n0\n0\n9\n0";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 3", stringWriter.ToString());
        }

        [Fact]
        public void IfACZeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n3\n0\n3\n9\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 3", stringWriter.ToString());
        }

        [Fact]
        public void IfABDEZeroAndSystemHasSolution_ThenWriteThreeAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n0\n3\n0\n0\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 3", stringWriter.ToString());
        }

        [Fact]
        public void IfBCDFZeroAndSystemHasSolution_ThenWriteThreeAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "3\n0\n0\n0\n9\n0";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 3", stringWriter.ToString());
        }

        [Fact]
        public void IfBDZeroAndSystemHasSolution_ThenWriteThreeAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "3\n0\n3\n0\n9\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 3", stringWriter.ToString());
        }

        [Fact]
        public void IfABEZeroAndSystemHasSolution_ThenWriteOneAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n0\n3\n3\n0\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("1 -1 3", stringWriter.ToString());
        }

        [Fact]
        public void IfCDFZeroAndSystemHasSolution_ThenWriteOneAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "3\n3\n0\n0\n9\n0";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("1 -1 3", stringWriter.ToString());
        }

        [Fact]
        public void IfCoefficientsAreProportional_ThenWriteOneAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "1\n1\n3\n3\n3\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("1 -1 3", stringWriter.ToString());
        }

        [Fact]
        public void IfSystemHaveNotSolution_ThenWriteZero()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "1\n1\n3\n3\n33\n9";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("0", stringWriter.ToString());
        }

        [Fact]
        public void IfABCEeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n0\n0\n5\n0\n5";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 1", stringWriter.ToString());
        }

        [Fact]
        public void IfACDFeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n5\n0\n0\n5\n0";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 1", stringWriter.ToString());
        }

        [Fact]
        public void IfABDEeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "0\n0\n5\n0\n0\n5";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 1", stringWriter.ToString());
        }

        [Fact]
        public void IfBCDFeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            var stringWriter = new StringWriter();
            Console.SetOut(stringWriter);

            string result = "5\n0\n0\n0\n5\n0";
            var stringReader = new StringReader(result);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 1", stringWriter.ToString());
        }
    }
}