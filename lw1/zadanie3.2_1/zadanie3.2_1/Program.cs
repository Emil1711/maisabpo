using System;

class Program
{
    static void Main(string[] args)
    {
        int a = Convert.ToInt32("101101101", 2); // 365
        int b = Convert.ToInt32("10111101010", 2); // 1514
        int M = Convert.ToInt32("10001000000100001", 2); // 69665

        Console.WriteLine("a + b mod M = " + ((a ^ b) % M) + " = " + Convert.ToString((a ^ b) % M, 2));
        Console.WriteLine("a - b mod M = " + ((a ^ b) % M) + " = " + Convert.ToString((a ^ b) % M, 2));
        Console.WriteLine("a * b mod M = " + Multiply(a, b, M) + " = " + Convert.ToString(Multiply(a, b, M), 2));
        Console.WriteLine("2^(-1) mod M = " + ModInverse(2, M) + " = " + Convert.ToString(ModInverse(2, M), 2));
    }

    static int Multiply(int a, int b, int m)
    {
        int res = 0;
        while (b > 0)
        {
            if ((b & 1) != 0)
            {
                res ^= a;
                if (res >= m) res ^= m;
            }
            a <<= 1;
            if (a >= m) a ^= m;
            b >>= 1;
        }
        return res;
    }

    static int ModInverse(int a, int m)
    {
        a %= m;
        for (int x = 1; x < m; x++)
            if (Multiply(a, x, m) == 1)
                return x;
        return 1;
    }
}