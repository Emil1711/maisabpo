using System;
using System.IO;
using System.Net;
using System.Security.Cryptography;
using System.Text;

class Program
{
    static void Main()
    {
        Console.WriteLine("Введите данные:");
        string inputData = Console.ReadLine();

        // Проверка данных на соответствие правилам (например, не пустая строка)
        if (string.IsNullOrWhiteSpace(inputData))
        {
            Console.WriteLine("Данные не должны быть пустыми.");
            return;
        }

        // Чтение внешнего ресурса (например, файла или веб-страницы)
        Console.WriteLine("Введите URL внешнего ресурса:");
        string resourceUrl = Console.ReadLine();
        string resourceData = ReadExternalResource(resourceUrl);

        // Передача данных из ресурса в обработку
        string processedData = ProcessData(resourceData);

        // Расчет и проверка контрольных сумм до и после обработки
        string originalChecksum = CalculateChecksum(resourceData);
        string processedChecksum = CalculateChecksum(processedData);

        Console.WriteLine($"Контрольная сумма исходных данных: {originalChecksum}");
        Console.WriteLine($"Контрольная сумма обработанных данных: {processedChecksum}");

        // Дополнительные функции, такие как шифрование, передача данных и т.д., должны быть реализованы здесь
        // ...
    }

    static string ReadExternalResource(string url)
    {
        using (WebClient client = new WebClient())
        {
            try
            {
                return client.DownloadString(url);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка при чтении ресурса: " + ex.Message);
                return null;
            }
        }
    }

    static string ProcessData(string data)
    {
        // Здесь может быть любая логика обработки данных
        return data.ToUpper(); // Пример: преобразование данных в верхний регистр
    }

    static string CalculateChecksum(string data)
    {
        using (SHA256 sha256 = SHA256.Create())
        {
            byte[] hash = sha256.ComputeHash(Encoding.UTF8.GetBytes(data));
            return BitConverter.ToString(hash).Replace("-", String.Empty);
        }
    }
}
