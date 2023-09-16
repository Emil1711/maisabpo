using System;

class Program
{
    static void Main()
    {
        int a = 321;
        int b = 654;
        int M = 155;

        Console.WriteLine("(a+b) mod M = " + ((a + b) % M));
        Console.WriteLine("(a-b) mod M = " + ((a - b + M) % M));
        Console.WriteLine("(a*b) mod M = " + ((a * b) % M));
        Console.WriteLine("(a^b) mod M = " + Power(a, b, M));

        int invA = ModInverse(a, M);
        if (invA == -1)
            Console.WriteLine("a^(-1) mod M = нет решения");
        else
            Console.WriteLine("a^(-1) mod M = " + invA);

        int invB = ModInverse(b, M);
        if (invB == -1)
            Console.WriteLine("b^(-1) mod M = нет решения");
        else
            Console.WriteLine("b^(-1) mod M = " + invB);

        if (invA != -1)
            Console.WriteLine("(b/a) mod M = " + ((b * invA) % M));
        else
            Console.WriteLine("(b/a) mod M = нет решения");

        if (invB != -1)
            Console.WriteLine("(a/b) mod M = " + ((a * invB) % M));
        else
            Console.WriteLine("(a/b) mod M = нет решения");
    }

    static int Power(int a, int b, int m)
    {
        int result = 1;
        while (b > 0)
        {
            if (b % 2 == 1)
                result = (result * a) % m;
            a = (a * a) % m;
            b /= 2;
        }
        return result;
    }

    static int ModInverse(int a, int m)
    {
        for (int x = 1; x < m; x++)
            if (((a % m) * (x % m)) % m == 1)
                return x;
        return -1;
    }
}
