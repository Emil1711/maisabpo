using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        Console.Write("Введите количество простых чисел, которые вы хотите вывести: ");
        int N = Convert.ToInt32(Console.ReadLine());
        List<int> primes = FirstNPrimes(N);
        Console.WriteLine(String.Join(", ", primes));

        Console.Write("Введите число для проверки на простоту: ");
        int num = Convert.ToInt32(Console.ReadLine());
        Console.WriteLine(IsPrime(num) ? "Простое" : "Составное");
    }

    static List<int> FirstNPrimes(int N)
    {
        List<int> primes = new List<int>();
        if (N > 0)
            primes.Add(1);

        int num = 2;
        while (primes.Count < N)
        {
            if (IsPrime(num))
                primes.Add(num);
            num++;
        }
        return primes;
    }

    static bool IsPrime(int num)
    {
        if (num <= 1)
            return false;

        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
                return false;
        }

        return true;
    }
}
