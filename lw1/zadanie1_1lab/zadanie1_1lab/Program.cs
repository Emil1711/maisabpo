using System;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        // Проверяем, что переданы два аргумента: формат и путь к файлу
        if (args.Length != 2)
        {
            Console.WriteLine("путь к формату программы");
            return;
        }

        // Получаем формат и путь к файлу из аргументов
        string format = args[0];
        string path = args[1];

        // Читаем все байты из файла
        byte[] bytes = File.ReadAllBytes(path);

        // В зависимости от формата, выводим содержимое файла в нужном виде
        switch (format)
        {
            case "hex8":
                // Выводим каждый байт в шестнадцатеричном виде, разделенный пробелами
                foreach (byte b in bytes)
                {
                    Console.Write($"{b:X02} ");
                }
                Console.WriteLine();
                break;
            case "dec8":
                // Выводим каждый байт в десятичном виде, разделенный пробелами
                foreach (byte b in bytes)
                {
                    Console.Write($"{b:D3} ");
                }
                Console.WriteLine();
                break;
            case "hex16":
                // Выводим каждые два байта в шестнадцатеричном виде, разделенный пробелами
                for (int i = 0; i < bytes.Length; i += 2)
                {
                    // Склеиваем два байта в одно 16-битное число
                    ushort word = BitConverter.ToUInt16(bytes, i);
                    Console.Write($"{word:X4} ");
                }
                Console.WriteLine();
                break;
            case "dec16":
                // Выводим каждые два байта в десятичном виде, разделенный пробелами
                for (int i = 0; i < bytes.Length; i += 2)
                {
                    // Склеиваем два байта в одно 16-битное число
                    ushort word = BitConverter.ToUInt16(bytes, i);
                    Console.Write($"{word:D5} ");
                }
                Console.WriteLine();
                break;
            case "hex32":
                // Выводим каждые четыре байта в шестнадцатеричном виде, разделенный пробелами
                for (int i = 0; i < bytes.Length; i += 4)
                {
                    // Склеиваем четыре байта в одно 32-битное число
                    uint dword = BitConverter.ToUInt32(bytes, i);
                    Console.Write($"{dword:X8} ");
                }
                Console.WriteLine();
                break;
            default:
                // Если формат неизвестен, выводим сообщение об ошибке
                Console.WriteLine("Unknown format: {0}", format);
                break;
        }
    }
}
