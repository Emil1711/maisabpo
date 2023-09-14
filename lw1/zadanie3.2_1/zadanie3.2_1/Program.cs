using System;
using System.Numerics;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            // Параметры поля
            int n = 4; // Порядок полинома
            BigInteger M = new BigInteger(0b10011); // Неприводимый полином M(x) = x^4 + x + 1

            // Ввод полиномов
            Console.Write("Введите первый полином: ");
            BigInteger poly1 = BigInteger.Parse(Console.ReadLine());

            Console.Write("Введите второй полином: ");
            BigInteger poly2 = BigInteger.Parse(Console.ReadLine());

            Console.WriteLine();

            // Выполнение операций
            BigInteger sum = Addition(poly1, poly2, M);
            BigInteger diff = Subtraction(poly1, poly2, M);
            BigInteger product = Multiplication(poly1, poly2, M);
            BigInteger power = Power(poly1, n, M);
            BigInteger inverse = Inverse(poly1, M);
            BigInteger quotient = Division(poly1, poly2, M);

            // Вывод результатов
            Console.WriteLine("Сумма: " + sum.ToString("X"));
            Console.WriteLine("Разность: " + diff.ToString("X"));
            Console.WriteLine("Произведение: " + product.ToString("X"));
            Console.WriteLine("Возведение в степень: " + power.ToString("X"));
            Console.WriteLine("Обратный элемент: " + inverse.ToString("X"));
            Console.WriteLine("Частное: " + quotient.ToString("X"));

            Console.ReadLine();
        }

        // Сложение
        static BigInteger Addition(BigInteger poly1, BigInteger poly2, BigInteger M)
        {
            return poly1 ^ poly2;
        }

        // Вычитание
        static BigInteger Subtraction(BigInteger poly1, BigInteger poly2, BigInteger M)
        {
            return poly1 ^ poly2;
        }

        // Умножение
        static BigInteger Multiplication(BigInteger poly1, BigInteger poly2, BigInteger M)
        {
            BigInteger result = new BigInteger(0);
            while (poly2 != 0)
            {
                if ((poly2 & 1) == 1)
                    result ^= poly1;
                poly1 <<= 1;
                if ((poly1 & (1 << 4)) != 0)
                    poly1 ^= M;
                poly2 >>= 1;
            }
            return result;
        }

        // Возведение в степень
        static BigInteger Power(BigInteger poly, int power, BigInteger M)
        {
            BigInteger result = new BigInteger(1);
            while (power != 0)
            {
                if ((power & 1) == 1)
                    result = Multiplication(result, poly, M);
                poly = Multiplication(poly, poly, M);
                power >>= 1;
            }
            return result;
        }

        // Поиск обратного элемента
        static BigInteger Inverse(BigInteger poly, BigInteger M)
        {
            return Power(poly, (int)M - 2, M);
        }

        // Деление
        static BigInteger Division(BigInteger poly1, BigInteger poly2, BigInteger M)
        {
            if (poly2 == 0)
                throw new DivideByZeroException("Деление на ноль невозможно.");
            return Multiplication(poly1, Inverse(poly2, M), M);
        }
    }
}
