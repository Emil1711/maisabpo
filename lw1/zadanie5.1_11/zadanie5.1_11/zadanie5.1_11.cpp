#include <iostream>
#include <vector>
#include <algorithm>

class BigInteger {
private:
    std::vector<int> digits; // Вектор для хранения цифр большого числа

public:
    BigInteger() {} // Конструктор по умолчанию

    // Конструктор, принимающий строку с числом
    BigInteger(const std::string& number) {
        for (int i = number.length() - 1; i >= 0; i--) {
            digits.push_back(number[i] - '0'); // Преобразование символа в число и добавление в вектор
        }
    }

    // Оператор сложения для больших чисел
    BigInteger operator+(const BigInteger& other) const {
        BigInteger result;
        int carry = 0;
        int maxSize = std::max(digits.size(), other.digits.size());

        for (int i = 0; i < maxSize || carry; i++) {
            if (i < digits.size())
                carry += digits[i];
            if (i < other.digits.size())
                carry += other.digits[i];

            result.digits.push_back(carry % 10);
            carry /= 10;
        }

        return result;
    }

    // Оператор умножения для больших чисел
    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        result.digits.resize(digits.size() + other.digits.size());

        for (int i = 0; i < digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; j++) {
                long long current = result.digits[i + j] + digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = current % 10;
                carry = current / 10;
            }
        }

        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();

        return result;
    }

    // Оператор остатка от деления большого числа на маленькое
    int operator%(int mod) const {
        int result = 0;

        for (int i = digits.size() - 1; i >= 0; i--) {
            result = (result * 10 + digits[i]) % mod;
        }

        return result;
    }

    // Оператор вывода для больших чисел
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& number) {
        for (int i = number.digits.size() - 1; i >= 0; i--) {
            os << number.digits[i];
        }
        return os;
    }
};

int main() {
    BigInteger num1("123456789012345678901234567890"); // Создание большого числа num1
    BigInteger num2("987654321098765432109876543210"); // Создание большого числа num2

    BigInteger sum = num1 + num2; // Сложение двух больших чисел
    BigInteger product = num1 * num2; // Умножение двух больших чисел
    int modulus = num1 % 100; // Взятие остатка от деления большого числа на маленькое

    std::cout << "Sum: " << sum << std::endl; // Вывод суммы
    std::cout << "Product: " << product << std::endl; // Вывод произведения
    std::cout << "Modulus: " << modulus << std::endl; // Вывод остатка от деления

    return 0;
}
