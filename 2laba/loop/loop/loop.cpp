typedef unsigned char byte; // Определение типа byte как unsigned char
typedef unsigned int uint; // Определение типа uint как unsigned int
#include <random> // Включает заголовки для работы с генераторами случайных чисел
#include <Windows.h> // Включает Windows-specific заголовки для работы с Windows API
#include <boost/crc.hpp>  // Для CRC16 и CRC32
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>


int corruptedBits = 0;
int recoveredBits = 0;
int totalBits = 0;
const int t = 10;
int k = 10;
int n = 15;



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

int main() {
	int N = 64 * 1024 * 1024;
	byte* memory = new byte[N];
	time_t t = time(nullptr);
	srand(t);

	printf("Ptr = %016llX\n", (unsigned long long)memory);
	printf("press Enter key for continue");
	getchar();


	while (true) {
		for (int i = 0; i < 16; i++)
			memory[i] = 0xab;
		for (int i = 16; i < N - 16; ++i)
			memory[i] = (byte)rand();

		uint chksum_0 = chksum_xor(memory, N);
		printf("Chksum XOR before= %08X\n", chksum_0);
		uint chksum_1 = chksum_crc16(memory, N);
		printf("Chksum CRC16 before= %08X\n", chksum_1);
		uint chksum_2 = chksum_crc32(memory, N);
		printf("Chksum CRC32 before= %08X\n", chksum_2);



		int M = (unsigned)rand() % N;
		memory[0] = (byte)~memory[M];
		printf("Corrupt %dth byte\n", M);

		Sleep(1000);

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
