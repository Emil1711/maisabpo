using System;

class Program
{
    static void Main(string[] args)
    {
        string command = args[0];
        UInt64 num1 = UInt64.Parse(args[1]);
        UInt64 num2 = UInt64.Parse(args[2]);
        UInt64 result = 0;

        switch (command)
        {
            case "xor":
                result = num1 ^ num2;
                break;
            case "and":
                result = num1 & num2;
                break;
            case "or":
                result = num1 | num2;
                break;
            case "set1":
                result = num2 | ((UInt64)1 << (int)num1);
                break;
            case "set0":
                result = num2 & ~((UInt64)1 << (int)num1);
                break;
            case "shl":
                result = num2 << (int)num1;
                break;
            case "shr":
                result = num2 >> (int)num1;
                break;
            case "rol":
                result = (num2 << (int)num1) | (num2 >> (int)(64 - num1));
                break;
            case "ror":
                result = (num2 >> (int)num1) | (num2 << (int)(64 - num1));
                break;
            case "mix":
                for (int i = 0; i < 8; i++)
                    result |= ((num2 >> ((int)(num1 >> ((7 - i) * 8)) & 0xff)) & 1) << i;
                break;
        }

        Console.WriteLine($"Result in decimal: {result}");
        Console.WriteLine($"Result in hexadecimal: {result:X}");
        Console.WriteLine($"Result in binary: {Convert.ToString((long)result, 2)}");
    }
}
