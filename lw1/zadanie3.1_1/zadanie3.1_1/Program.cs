using System;
using System.Numerics;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            // Проверяем, что аргументов достаточно
            if (args.Length < 4)
            {
                Console.WriteLine("Недостаточно аргументов");
                return;
            }

            // Получаем операцию, число1, число2 и модуль из аргументов
            string operation = args[0];
            BigInteger number1 = BigInteger.Parse(args[1]);
            BigInteger number2 = BigInteger.Parse(args[2]);
            BigInteger modulus = BigInteger.Parse(args[3]);

            // Объявляем переменную для результата
            BigInteger result = 0;

            // Выполняем операцию в зависимости от ее названия
            switch (operation)
            {
                case "add":
                    result = (number1 + number2) % modulus;
                    break;
                case "sub":
                    result = (number1 - number2) % modulus;
                    break;
                case "mul":
                    result = (number1 * number2) % modulus;
                    break;
                case "pow":
                    result = BigInteger.ModPow(number1, number2, modulus);
                    break;
                case "inv":
                    result = ModInverse(number1, modulus);
                    break;
                case "div":
                    result = (number1 * ModInverse(number2, modulus)) % modulus;
                    break;
                default:
                    Console.WriteLine("Неверная операция");
                    return;
            }

            // Выводим результат в десятичном виде
            Console.WriteLine($"Результат: {result}");
        }

        // Метод для нахождения обратного элемента по модулю с помощью расширенного алгоритма Евклида
        static BigInteger ModInverse(BigInteger a, BigInteger m)
        {
            // Проверяем, что модуль положителен
            if (m <= 0)
            {
                throw new ArgumentException("Модуль должен быть положительным");
            }

            // Проверяем, что a и m взаимно простые
            if (BigInteger.GreatestCommonDivisor(a, m) != 1)
            {
                throw new ArgumentException("Числа должны быть взаимно простыми");
            }

            // Инициализируем переменные для коэффициентов Безу и остатков
            BigInteger x0 = 1; // Коэффициент при a
            BigInteger x1 = 0; // Коэффициент при m
            BigInteger r0 = a; // Остаток от деления a на m
            BigInteger r1 = m; // Остаток от деления m на r0

            // Пока остаток не равен нулю, повторяем шаги алгоритма
            while (r1 != 0)
            {
                // Находим частное и остаток от деления r0 на r1
                BigInteger q = r0 / r1; // Частное
                BigInteger r = r0 % r1; // Остаток

                // Обновляем значения переменных
                r0 = r1; // Предыдущий остаток становится текущим
                r1 = r;  // Текущий остаток становится следующим

                BigInteger x = x0 - q * x1; // Находим новый коэффициент при a
                x0 = x1; // Предыдущий коэффициент становится текущим
                x1 = x;  // Текущий коэффициент становится следующим
            }

            // Возвращаем коэффициент при a по модулю m
            return (x0 % m + m) % m;
        }
    }
}
