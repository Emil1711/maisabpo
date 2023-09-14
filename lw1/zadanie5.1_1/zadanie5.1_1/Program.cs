using System;
using System.Text;

public class BigInteger
{
    private string number;

    public BigInteger(string num)
    {
        number = num;
    }

    public static BigInteger operator +(BigInteger num1, BigInteger num2)
    {
        StringBuilder result = new StringBuilder();

        int carry = 0;
        int limit = Math.Max(num1.number.Length, num2.number.Length);

        for (int i = 0; i < limit; i++)
        {
            int digit1 = i < num1.number.Length ? num1.number[num1.number.Length - 1 - i] - '0' : 0;
            int digit2 = i < num2.number.Length ? num2.number[num2.number.Length - 1 - i] - '0' : 0;
            int sum = digit1 + digit2 + carry;

            carry = sum / 10;
            result.Insert(0, sum % 10);
        }

        if (carry > 0)
        {
            result.Insert(0, carry);
        }

        return new BigInteger(result.ToString());
    }

    public static BigInteger operator *(BigInteger num1, BigInteger num2)
    {
        string result = "0";

        for (int i = num2.number.Length - 1; i >= 0; i--)
        {
            StringBuilder tempResult = new StringBuilder();

            int carry = 0;
            int digit2 = num2.number[i] - '0';

            for (int j = num1.number.Length - 1; j >= 0; j--)
            {
                int digit1 = num1.number[j] - '0';
                int product = digit1 * digit2 + carry;

                carry = product / 10;
                tempResult.Insert(0, product % 10);
            }

            if (carry > 0)
            {
                tempResult.Insert(0, carry);
            }

            tempResult.Append('0', num2.number.Length - 1 - i);
            result = (new BigInteger(result) + new BigInteger(tempResult.ToString())).number;
        }

        return new BigInteger(result);
    }

    public static BigInteger operator %(BigInteger num, BigInteger mod)
    {
        while (num >= mod)
        {
            num -= mod;
        }

        return num;
    }

    public override string ToString()
    {
        return number;
    }

    public static implicit operator BigInteger(string num)
    {
        return new BigInteger(num);
    }
}

class Program
{
    static void Main()
    {
        BigInteger a = "1234567890987654321";
        BigInteger b = "9876543210123456789";

        BigInteger sum = a + b;
        BigInteger product = a * b;
        BigInteger modulo = product % sum;

        Console.WriteLine("Сумма: " + sum);
        Console.WriteLine("Произведение: " + product);
        Console.WriteLine("Остаток от деления произведения на сумму: " + modulo);

        Console.ReadLine();
    }
}