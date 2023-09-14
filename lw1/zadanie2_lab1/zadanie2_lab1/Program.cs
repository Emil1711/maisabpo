using System;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            // Проверяем, что аргументов достаточно
            if (args.Length < 3)
            {
                Console.WriteLine("Недостаточно аргументов");
                return;
            }

            // Получаем команду, число1 и число2 из аргументов
            string command = args[0];
            ulong number1 = ulong.Parse(args[1]);
            ulong number2 = ulong.Parse(args[2]);

            // Объявляем переменную для результата
            ulong result = 0;

            // Выполняем команду в зависимости от ее названия
            switch (command)
            {
                case "xor":
                    result = number1 ^ number2;
                    break;
                case "and":
                    result = number1 & number2;
                    break;
                case "or":
                    result = number1 | number2;
                    break;
                case "set1":
                    result = number2 | (1UL << (int)number1);
                    break;
                case "set0":
                    result = number2 & ~(1UL << (int)number1);
                    break;
                case "shl":
                    result = number2 << (int)number1;
                    break;
                case "shr":
                    result = number2 >> (int)number1;
                    break;
                case "rol":
                    result = (number2 << (int)number1) | (number2 >> (64 - (int)number1));
                    break;
                case "ror":
                    result = (number2 >> (int)number1) | (number2 << (64 - (int)number1));
                    break;
                case "mix":
                    result = Mix(number1, number2);
                    break;
                default:
                    Console.WriteLine("Неверная команда");
                    return;
            }

            // Выводим результат в десятичном, шестнадцатеричном и бинарном виде
            Console.WriteLine($"Результат: {result}");
            Console.WriteLine($"Шестнадцатеричный вид: {result:X}");
            Console.WriteLine($"Бинарный вид: {Convert.ToString((long)result, 2)}");
        }

        // Метод для перестановки байтов числа в указанном порядке
        static ulong Mix(ulong order, ulong number)
        {
            // Создаем массив из 8 байтов числа
            byte[] bytes = BitConverter.GetBytes(number);

            // Создаем массив из 8 цифр порядка
            byte[] digits = new byte[8];
            for (int i = 0; i < 8; i++)
            {
                digits[i] = (byte)(order % 10);
                order /= 10;
            }

            // Создаем новый массив для переставленных байтов
            byte[] newBytes = new byte[8];

            // Копируем байты в новый массив в соответствии с порядком
            for (int i = 0; i < 8; i++)
            {
                newBytes[i] = bytes[digits[i]];
            }

            // Возвращаем новое число из нового массива байтов
            return BitConverter.ToUInt64(newBytes);
        }
    }
}
