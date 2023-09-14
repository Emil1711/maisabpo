using System;

class SieveOfEratosthenes
{
    // Метод для вывода N первых простых чисел
    static void PrintPrimes(int N)
    {
        // Создаем массив для хранения информации о числах
        bool[] isPrime = new bool[N + 1];

        // Инициализируем все числа как простые
        for (int i = 2; i <= N; i++)
        {
            isPrime[i] = true;
        }

        // Отмечаем все не простые числа
        for (int p = 2; p * p <= N; p++)
        {
            // Если число еще не помечено как не простое
            if (isPrime[p] == true)
            {
                // Проходимся по всем числам в диапазоне от p*p до N и отмечаем их как не простые
                for (int i = p * p; i <= N; i += p)
                {
                    isPrime[i] = false;
                }
            }
        }

        // Выводим простые числа на экран
        for (int i = 2; i <= N; i++)
        {
            if (isPrime[i] == true)
            {
                Console.Write(i + " ");
            }
        }
    }

    // Метод для проверки введенного числа на простоту
    static bool IsPrimeNumber(int number)
    {
        // Если число меньше 2, оно не является простым
        if (number < 2)
        {
            return false;
        }

        // Проверяем делители числа до квадратного корня числа
        for (int i = 2; i <= Math.Sqrt(number); i++)
        {
            // Если число делится нацело на один из делителей, оно не является простым
            if (number % i == 0)
            {
                return false;
            }
        }

        // Если ни один делитель не найден, число простое
        return true;
    }

    static void Main(string[] args)
    {
        // Вывод N первых простых чисел
        int N = 100;
        Console.WriteLine("Первые " + N + " простых чисел:");
        PrintPrimes(N);
        Console.WriteLine();

        // Проверка введенного числа на простоту
        Console.WriteLine("Введите число для проверки на простоту:");
        int number = Convert.ToInt32(Console.ReadLine());
        if (IsPrimeNumber(number))
        {
            Console.WriteLine(number + " является простым числом.");
        }
        else
        {
            Console.WriteLine(number + " не является простым числом.");
        }
    }
}