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

//std::vector<int> alpha_to(n);
//std::vector<int> index_of(n);
//std::vector<int> recd(n);
//std::vector<int> s(n - k + 1);
//std::vector<std::vector<int>> elp(n - k + 2, std::vector<int>(n - k));
//std::vector<int> d(n - k + 2);
//std::vector<int> l(n - k + 2);
//std::vector<int> u_lu(n - k + 2);
//std::vector<int> root(t);
//std::vector<int> loc(t);
//std::vector<int> z(t + 1);
//std::vector<int> err(n);
//std::vector<int> reg(t + 1);
//
//
//
//void decode_rs()
//{
//	int i, j, u, q;
//	std::vector<int> s(n - k + 1);
//	std::vector<std::vector<int>> elp(n - k + 2, std::vector<int>(n - k));
//	std::vector<int> d(n - k + 2);
//	std::vector<int> l(n - k + 2);
//	std::vector<int> u_lu(n - k + 2);
//	int count = 0, syn_error = 0;
//	std::vector<int> root(t), loc(t), z(t + 1), err(n), reg(t + 1);
//
//
//	for (i = 0; i < n; i++)
//		recd[i] = index_of[recd[i]];
//
//	for (i = 1; i <= n - k; i++)
//	{
//		s[i] = 0;
//		for (j = 0; j < n; j++)
//			if (recd[j] != -1)
//				s[i] ^= alpha_to[(recd[j] + i * j) % n];
//		if (s[i] != 0)
//			syn_error = 1;
//		s[i] = index_of[s[i]];
//	}
//
//	if (syn_error)
//		d[0] = 0;
//	d[1] = s[1];
//	elp[0][0] = 0;
//	elp[1][0] = 1;
//	for (i = 1; i < n - k; i++)
//	{
//		elp[0][i] = -1;
//		elp[1][i] = 0;
//	}
//	l[0] = 0; l[1] = 0; u_lu[0] = -1; u_lu[1] = 0; u = 0;
//	do
//	{
//		u++;
//		if (d[u] == -1)
//		{
//			l[u + 1] = l[u];
//			for (i = 0; i <= l[u]; i++)
//			{
//				elp[u + 1][i] = elp[u][i];
//				elp[u][i] = index_of[elp[u][i]];
//			}
//		}
//		else
//		{
//
//			q = u - 1;
//			while ((d[q] == -1) && (q > 0))
//				q--;
//
//			if (q > 0)
//			{
//				j = q;
//				do
//				{
//					j--;
//					if ((d[j] != -1) && (u_lu[q] < u_lu[j]))
//						q = j;
//				} while (j > 0);
//			};
//
//			if (l[u] > l[q] + u - q)
//				l[u + 1] = l[u];
//			else
//				l[u + 1] = l[q] + u - q;
//			// формируем новый elp(x)
//			for (i = 0; i < n - k; i++)
//				elp[u + 1][i] = 0;
//			for (i = 0; i <= l[q]; i++)
//				if (elp[q][i] != -1)
//					elp[u + 1][i + u - q] = alpha_to[(d[u] + n - d[q] + elp[q][i]) % n];
//			for (i = 0; i <= l[u]; i++)
//			{
//				elp[u + 1][i] ^= elp[u][i];
//
//				elp[u][i] = index_of[elp[u][i]];
//			}
//		}
//		u_lu[u + 1] = u - l[u + 1];
//		(u < n - k);
//		{
//			if (s[u + 1] != -1)
//				d[u + 1] = alpha_to[s[u + 1]];
//			else
//				d[u + 1] = 0;
//			for (i = 1; i <= l[u + 1]; i++)
//				if ((s[u + 1 - i] != -1) && (elp[u + 1][i] != 0))
//					d[u + 1] ^= alpha_to[(s[u + 1 - i] + index_of[elp[u + 1][i]]) % n];
//
//			d[u + 1] = index_of[d[u + 1]];
//		}
//	} while ((u < n - k) && (l[u + 1] <= t));
//
//	u++;
//	if (l[u] <= t)
//	{
//		for (i = 0; i <= l[u]; i++)
//			elp[u][i] = index_of[elp[u][i]];
//
//		for (i = 1; i <= l[u]; i++)
//			reg[i] = elp[u][i];
//		count = 0;
//		for (i = 1; i <= n; i++)
//		{
//			q = 1;
//			for (j = 1; j <= l[u]; j++)
//				if (reg[j] != -1)
//				{
//					reg[j] = (reg[j] + j) % n;
//					q ^= alpha_to[reg[j]];
//				}
//			if (!q)
//			{
//				root[count] = i;
//				loc[count] = n - i;
//				count++;
//			}
//		}
//		if (count == l[u])
//		{
//			for (i = 1; i <= l[u]; i++)
//			{
//				if ((s[i] != -1) && (elp[u][i] != -1))
//					z[i] = alpha_to[s[i]] ^ alpha_to[elp[u][i]];
//				else
//					if ((s[i] != -1) && (elp[u][i] == -1))
//						z[i] = alpha_to[s[i]];
//					else
//						if ((s[i] == -1) && (elp[u][i] != -1))
//							z[i] = alpha_to[elp[u][i]];
//						else
//							z[i] = 0;
//				for (j = 1; j < i; j++)
//					if ((s[j] != -1) && (elp[u][i - j] != -1))
//						z[i] ^= alpha_to[(elp[u][i - j] + s[j]) % n];
//
//				z[i] = index_of[z[i]];
//			}
//
//			for (i = 0; i < n; i++)
//			{
//				err[i] = 0;
//				if (recd[i] != -1)
//					recd[i] = alpha_to[recd[i]];
//				else
//					recd[i] = 0;
//			}
//
//			for (i = 0; i < l[u]; i++)
//			{
//				err[loc[i]] = 1;
//				for (j = 1; j <= l[u]; j++)
//					if (z[j] != -1)
//						err[loc[i]] ^= alpha_to[(z[j] + j * root[i]) % n];
//				if (err[loc[i]] != 0)
//				{
//					err[loc[i]] = index_of[err[loc[i]]];
//					q = 0;
//					for (j = 0; j < l[u]; j++)
//						if (j != i)
//							q += index_of[1 ^ alpha_to[(loc[j] + root[i]) % n]];
//					q = q % n;
//					err[loc[i]] = alpha_to[(err[loc[i]] - q + n) % n];
//
//					recd[loc[i]] ^= err[loc[i]];
//				}
//			}
//		}
//		else
//		{
//
//			for (i = 0; i < n; i++)
//				if (recd[i] != -1) recd[i] = alpha_to[recd[i]];
//				else
//					recd[i] = 0;
//		}
//	}
//	else
//	{
//		for (i = 0; i < n; i++)
//		{
//			if (recd[i] != -1)
//				recd[i] = alpha_to[recd[i]];
//			else
//				recd[i] = 0;
//		}
//	}
//
//	
//}



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


			/*decode_rs();*/



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
