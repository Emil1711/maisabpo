typedef unsigned char byte; // Определение типа byte как unsigned char
typedef unsigned int uint; // Определение типа uint как unsigned int
#include <random> // Включает заголовки для работы с генераторами случайных чисел
#include <Windows.h> // Включает Windows-specific заголовки для работы с Windows API
#include <boost/crc.hpp>  // Для CRC16 и CRC32
#include <vector>

int corruptedBits = 0;
int recoveredBits = 0;
int totalBits = 0;

void addParityBit(byte* data, int N) {
    for (int i = 0; i < N; ++i) {
        byte parity = 0;
        for (int j = 0; j < 7; ++j) {
            parity ^= (data[i] >> j) & 1;
            totalBits++; // Увеличиваем счетчик общего количества битов
        }
        data[i] = (data[i] & 0x7F) | (parity << 7);
    }
}

// Функция для проверки бита паритета
void checkParityBit(byte* data, int N) {
    for (int i = 0; i < N; ++i) {
        byte parity = 0;
        for (int j = 0; j < 8; ++j) {
            parity ^= (data[i] >> j) & 1;
        }
        if (parity != 0) {
            printf("Corrupted byte at index %d: %02X\n", i, data[i]);
            corruptedBits++; // Увеличиваем количество поврежденных битов
        }
    }
}


void recoverBits(byte* data, int N) {
    for (int i = 0; i < N; ++i) {
        byte parity = 0;
        for (int j = 0; j < 8; ++j) {
            parity ^= (data[i] >> j) & 1;
        }
        if (parity != 0) { // Если байт поврежден
            // Попытка восстановить бит
            for (int j = 0; j < 8; ++j) {
                byte temp = data[i] ^ (1 << j);
                byte tempParity = 0;
                for (int k = 0; k < 8; ++k) {
                    tempParity ^= (temp >> k) & 1;
                }
                if (tempParity == 0) { // Если бит паритета теперь равен нулю
                    data[i] = temp; // Восстанавливаем бит
                    recoveredBits++; // Увеличиваем количество восстановленных битов
                    break;
                }
            }
        }
    }
}

uint chksum_xor(byte*, int n); // Объявление функции, которая вычисляет контрольную сумму XOR
uint chksum_crc16(byte*, int n); // Объявление функции, которая вычисляет контрольную сумму CRC16
uint chksum_crc32(byte*, int n); // Объявление функции, которая вычисляет контрольную сумму CRC32

int main() // Главная функция программы
{
    int N = 64 * 1024 * 1024; // Объявление и инициализация переменной размером буфера в байтах
    byte* memory = new byte[N]; // Создание буфера заданного размера
    time_t t = time(nullptr); // Получение текущего времени
    srand(t); // Инициализация генератора случайных чисел текущим временем

    printf("Ptr = %016llX\n", (unsigned long long)memory); // Вывод адреса буфера
    printf("press Enter key for continue");
    getchar(); // Ожидание нажатия Enter

    while (true) // Бесконечный цикл
    {
        for (int i = 0; i < 16; i++)
            memory[i] = 0xab; // Заполнение первых 16 байтов буфера значением 0xab
        for (int i = 16; i < N - 16; ++i)
            memory[i] = (byte)rand(); // Заполнение остальной части буфера случайными значениями

        uint chksum_0 = chksum_xor(memory, N); // Вычисление контрольной суммы XOR для буфера
        printf("Chksum XOR before= %08X\n", chksum_0);
        uint chksum_1 = chksum_crc16(memory, N); // Вычисление контрольной суммы CRC16 для буфера
        printf("Chksum CRC16 before= %08X\n", chksum_1);
        uint chksum_2 = chksum_crc32(memory, N); // Вычисление контрольной суммы CRC32 для буфера
        printf("Chksum CRC32 before= %08X\n", chksum_2);

        for (int i = 0; i < 32; ++i)
            printf("%02X ", memory[i]);
        printf("\n");

        Sleep(1000); // Приостановка выполнения программы на 1 секунду

        uint chksum_3 = chksum_xor(memory, N);
        printf("Chksum XOR after= %08X\n", chksum_3);
        uint chksum_4 = chksum_crc16(memory, N);
        printf("Chksum CRC16 after= %08X\n", chksum_4);
        uint chksum_5 = chksum_crc32(memory, N);
        printf("Chksum CRC32 after= %08X\n", chksum_5);

        for (int i = 0; i < 32; ++i)
            printf("%02X ", memory[i]);
        printf("\n");

        if (chksum_0 != chksum_3 || chksum_1 != chksum_4 || chksum_2 != chksum_5) {
            printf("Corrupt!!!\n");
            printf("Number of corrupted bits: %d\n", corruptedBits);
            printf("Number of recovered bits: %d\n", recoveredBits);
            printf("Total number of bits: %d\n", totalBits);
        }

        Sleep(1000);
    }
    delete[] memory;
    return 0;
}

uint chksum_xor(byte* data, int N) // Функция вычисления контрольной суммы XOR
{
    uint chk = 0;
    for (int n = 0; n < N; ++n)
        chk ^= data[n]; // Применение операции XOR к каждому байту данных
    return chk;
}

uint chksum_crc16(byte* data, int N) // Функция вычисления контрольной суммы CRC16
{
    boost::crc_16_type result;
    result.process_bytes(data, N);
    return result.checksum();
}

uint chksum_crc32(byte* data, int N) // Функция вычисления контрольной суммы CRC32
{
    boost::crc_32_type result;
    result.process_bytes(data, N);
    return result.checksum();
}
