Console.WriteLine("Введите одну из следующих команд: xor, and, or, set1, set0, shl, shr, shlc, shrc, mix.");
string commandType = Console.ReadLine();

if (!ValidateCommandType(commandType))
{
    Console.WriteLine("Вы ввели некорректно одну из следующих комманд: xor, and, or, set1, set0, shl, shr, shlc, shrc, mix.");
    return;
}

Console.WriteLine("\nВведите число 1: ");
string stringNumber1 = Console.ReadLine();

Console.WriteLine("\nВведите число 2: ");
string stringNumber2 = Console.ReadLine();

if (!ulong.TryParse(stringNumber1, out ulong num1) || !ulong.TryParse(stringNumber2, out ulong num2))
{
    Console.WriteLine("Неверный формат числа.");
    return;
}

ulong result = commandType switch
{
    "xor" => num1 ^ num2,
    "and" => num1 & num2,
    "or" => num1 | num2,
    "set1" => num2 | (1UL << (int)num1),
    "set0" => num2 & ~(1UL << (int)num1),
    "shl" => num2 << (int)num1,
    "shr" => num2 >> (int)num1,
    "shlc" => (num2 << (int)num1) | (num2 >> (64 - (int)num1)),
    "shrc" => (num2 >> (int)num1) | (num2 << (64 - (int)num1)),
    "mix" => Mix(num1, num2),
    _ => throw new InvalidOperationException("Недопустимая команда")
};

PrintResult(result);

bool ValidateCommandType(string formatType)
{
    string[] validCommands = { "xor", "and", "or", "set1", "set0", "shl", "shr", "shlc", "shrc", "mix" };
    return validCommands.Contains(formatType);
}

ulong Mix(ulong order, ulong num)
{
    string orderString = order.ToString();
    string numBinary = Convert.ToString((long)num, 2).PadLeft(8, '0');

    char[] mixedNum = new char[8];
    for (int i = 0; i < 8; i++)
    {
        int index = int.Parse(orderString[i].ToString());
        mixedNum[i] = numBinary[index];
    }

    ulong mixedNumDecimal = Convert.ToUInt64(new string(mixedNum), 2);
    return mixedNumDecimal;
}

void PrintResult(ulong result)
{
    Console.WriteLine("Результат:");
    Console.WriteLine($"Двоичный: {Convert.ToString((long)result, 2)}");
    Console.WriteLine($"Десятичный: {result}");
    Console.WriteLine($"Шестнадцатеричный: 0x{result:X}");
    
}
