using System;
using System.Numerics;

namespace BigIntegerExample
{
    class Program
    {
        static void Main(string[] args)
        {
            BigInteger a = BigInteger.Parse("123456789012345678901234567890");
            BigInteger b = BigInteger.Parse("987654321098765432109876543210");

            Console.WriteLine("a = " + a);
            Console.WriteLine("b = " + b);

            BigInteger c = a + b;
            Console.WriteLine("a + b = " + c);

            BigInteger d = a * b;
            Console.WriteLine("a * b = " + d);

            BigInteger e = a % 1000;
            Console.WriteLine("a % 1000 = " + e);
        }
    }
}
