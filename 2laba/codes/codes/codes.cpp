#include <Windows.h> // Включает Windows-specific заголовки для работы с Windows API
#include <tlhelp32.h> // Включает заголовки для работы с инструментами, такими как снимки процессов
#include <random> // Включает заголовки для работы с генераторами случайных чисел
#include <string> // Включает заголовки для работы со строками
#include <iostream> // Включает заголовки для ввода/вывода

void EnableDebugPriv(); // Объявление функции, которая включает привилегии отладки для текущего процесса

int main() // Главная функция программы
{
    SIZE_T bytesRW = 0; // Объявление переменной для хранения количества прочитанных/записанных байтов
    int N = 64 * 1024 * 1024; // Объявление и инициализация переменной размером буфера в байтах
    byte* buffer = new byte[N]; // Создание буфера заданного размера
    time_t t = time(nullptr); // Получение текущего времени
    srand(t); // Инициализация генератора случайных чисел текущим временем

    printf("Ptr="); // Вывод строки "Ptr="
    std::string str; // Объявление строки для хранения ввода пользователя
    std::getline(std::cin, str); // Получение строки от пользователя
    LPVOID lpAddress = (LPVOID)strtoull(str.c_str(), NULL, 16); // Преобразование строки в адрес памяти

    EnableDebugPriv(); // Включение привилегий отладки

    PROCESSENTRY32 entry; // Объявление структуры для хранения информации о процессе
    entry.dwSize = sizeof(PROCESSENTRY32); // Установка размера структуры

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); // Создание снимка всех процессов в системе

    if (Process32First(snapshot, &entry) == TRUE) // Если удалось получить информацию о первом процессе в снимке...
    {
        while (Process32Next(snapshot, &entry) == TRUE) // ...то перебираем все остальные процессы в снимке...
        {
            if (_stricmp(entry.szExeFile, "loop.exe") == 0) // ...и если имя исполняемого файла процесса равно "loop.exe"...
            {
                HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID); // ...то открываем этот процесс с полным доступом...

                do
                {
                    ReadProcessMemory(processHandle, lpAddress, buffer, N, &bytesRW); // ...читаем память процесса...
                    printf("Read %lld from %08llX\n", bytesRW, (unsigned long long)lpAddress);
                    for (int i = 0; i < 32; ++i)
                        printf("%02X ", buffer[i]);
                    printf("\n");

                    int M = (unsigned)rand() % N;
                    buffer[0] = (byte)~buffer[M];
                    printf("Corrupt %dth byte\n", M);
                    for (int i = 0; i < 32; ++i)
                        printf("%02X ", buffer[i]);
                    printf("\n");

                    WriteProcessMemory(processHandle, lpAddress, buffer, N, &bytesRW);
                    printf("Wrote %lld to %08llX\n", bytesRW, (unsigned long long)lpAddress);
                    printf("Press Enter to continue");
                    getchar();
                } while (true);

                CloseHandle(processHandle);
            }
        }
    }

    CloseHandle(snapshot);

}

void EnableDebugPriv()
{
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkp;

    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);

    CloseHandle(hToken);
}
