using lab2_csharp;
using System;
using System.IO;
using Xunit;
using Xunit.Abstractions;

namespace UnitTest.Tests
{
    public class UnitTest
    {
        private readonly StringWriter _stringWriter;
        public UnitTest()
        {
            _stringWriter = new StringWriter();
            Console.SetOut(_stringWriter);
        }

        [Fact]
        public void IfAllInputArgumentsZero_ThenWriteFive()
        {
            // Arrange
            string input = "0\n0\n0\n0\n0\n0";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("5", _stringWriter.ToString());
        }

        [Fact]
        public void IfSystemHasSingleSolution_ThenWriteTwoAndResult()
        {
            // Arrange
            string input = "5\n3\n4\n3\n6\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("2 -3 7", _stringWriter.ToString());
        }

        [Fact]
        public void IfABCEZeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            string input = "0\n0\n0\n3\n0\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfACDFZeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            string input = "0\n3\n0\n0\n9\n0";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfACZeroAndSystemHasSolution_ThenWriteFourAndRezult()
        {
            // Arrange
            string input = "0\n3\n0\n3\n9\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfABDEZeroAndSystemHasSolution_ThenWriteThreeAndRezult()
        {
            // Arrange
            string input = "0\n0\n3\n0\n0\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfBCDFZeroAndSystemHasSolution_ThenWriteThreeAndRezult()
        {
            // Arrange
            string input = "3\n0\n0\n0\n9\n0";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfBDZeroAndSystemHasSolution_ThenWriteThreeAndRezult()
        {
            // Arrange
            string input = "3\n0\n3\n0\n9\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfABEZeroAndSystemHasSolution_ThenWriteOneAndRezult()
        {
            // Arrange
            string input = "0\n0\n3\n3\n0\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("1 -1 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfCDFZeroAndSystemHasSolution_ThenWriteOneAndRezult()
        {
            // Arrange
            string input = "3\n3\n0\n0\n9\n0";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("1 -1 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfCoefficientsAreProportional_ThenWriteOneAndRezult()
        {
            // Arrange
            string input = "1\n1\n3\n3\n3\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("1 -1 3", _stringWriter.ToString());
        }

        [Fact]
        public void IfSystemHasNotSolution_ThenWriteZero()
        {
            // Arrange
            string input = "1\n1\n3\n3\n33\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("0", _stringWriter.ToString());
        }

        [Fact]
        public void IfACZeroAndSystemHasNotSolution_ThenWriteZero()
        {
            // Arrange
            string input = "0\n1\n0\n3\n33\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("0", _stringWriter.ToString());
        }

        [Fact]
        public void IfBDZeroAndSystemHasNotSolution_ThenWriteZero()
        {
            // Arrange
            string input = "1\n0\n3\n0\n33\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("0", _stringWriter.ToString());
        }

        [Fact]
        public void IfABCDZeroAndSystemHasNotSolution_ThenWriteZero()
        {
            // Arrange
            string input = "0\n0\n0\n0\n33\n9";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("0", _stringWriter.ToString());
        }

        [Fact]
        public void IfACEFZeroAndSystemHasNotSolution_ThenWriteFourAndResult()
        {
            // Arrange
            string input = "0\n3\n0\n3\n0\n0";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("4 0", _stringWriter.ToString());
        }

        [Fact]
        public void IfBDEFZeroAndSystemHasNotSolution_ThenWriteFourAndResult()
        {
            // Arrange
            string input = "3\n0\n3\n0\n0\n0";
            var stringReader = new StringReader(input);
            Console.SetIn(stringReader);

            // Act
            Program.Main(Array.Empty<string>());

            // Assert
            Assert.Equal("3 0", _stringWriter.ToString());
        }
    }
}