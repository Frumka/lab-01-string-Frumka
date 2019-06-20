//
// "Copyright 2019 Semenov Pavel Corporation"  [legal]

#include "../include/string.hpp"

/// Деструктор
String::~String() {
    delete[] Data;
}

/// Конструктор по умолчанию
String::String() {
    Data = new char[1];
    Data[0] = 0;
    capasity = 1;
}

/// Конструктор копирования
String::String(const String &rhs) {
    delete[] Data;
    capasity = rhs.capasity;
    Data = new char[capasity];
    size_t rSize = rhs.Size();
    for (size_t i = 0; i < rSize; i++) {
        Data[i] = rhs.Data[i];
    }
    Data[rSize] = 0;
}

/// Конструктор из *char
String::String(const char *data) {
    size_t ind;
    for (ind = 0; data[ind] != 0; ind++) continue;
    capasity = size_t((ind + 1) * 1.5);
    Data = new char[capasity];
    for (size_t i = 0; i <= ind; i++) {
        Data[i] = data[i];
    }
}

/// Оператор присваивания
String &String::operator=(const String &rhs) {
    delete[] Data;
    if (this != &rhs) {
        capasity = size_t((rhs.Size() + 1) * 1.5);
        Data = new char[capasity];
        size_t ind = 0;
        while (rhs[ind] != 0) {
            Data[ind] = rhs[ind];
            ind++;
        }
        Data[ind] = 0;
    }
    return (*this);
}

/// Оператор +=
/// <param name="rhs">Объект, который стоит после знака '+=' </param>
/// <returns>Возвращаем ссылку на себя</returns>
String &String::operator+=(const String &rhs) {
    size_t thisSize = Size();
    size_t fSize = rhs.Size() + thisSize + 1;
    char *tmp;
    if (fSize <= capasity) {
        for (size_t i = thisSize; i < fSize; i++)
            Data[i] = rhs.Data[i - thisSize];

        Data[fSize] = 0;
        return *this;

    } else {
        capasity = size_t(fSize * 1.5);
        tmp = new char[capasity];
    }
    for (size_t ind = 0; ind < fSize; ind++) {
        if (ind < thisSize) {
            tmp[ind] = Data[ind];
        } else {
            tmp[ind] = rhs.Data[ind - thisSize];
        }
    }
    delete[] Data;
    Data = tmp;
    return *this;
}

/// Оператор +=
/// Чтоб Тревис не ныл
/// <param name="rhs">Объект, который стоит после знака '+=' </param>
/// <returns>Возвращаем ссылку на себя</returns>
String &String::operator+=(const char *rhs) {
    String tmp(rhs);
    *this += tmp;
    return *this;
}

/// Оператор *=
/// <returns>Возвращаем ссылку на себя</returns>
String &String::operator*=(unsigned int m) {
    size_t thisSize = Size();
    size_t fSize = thisSize * m + 1;

    if (capasity >= fSize) {
        for (size_t i = thisSize; i < fSize; i++) {
            Data[i] = Data[i % thisSize];
        }
        Data[fSize] = 0;
        return *this;
    }

    capasity = size_t(fSize * 1.5);

    char *tmp = new char[capasity];
    for (size_t i = 0; i < fSize; i++) {
        tmp[i] = Data[i % thisSize];
    }
    tmp[thisSize * m] = 0;
    delete[] Data;
    Data = tmp;

    return (*this);
}

/// Оператор ==
/// <param name="rhs">Объект, который стоит после знака '==' </param>
/// <returns>Возвращаем значения равенства двух строк</returns>
bool String::operator==(const String &rhs) const {
    size_t ind = 0;
    while (Data[ind] || rhs[ind]) {
        if (Data[ind] == rhs[ind]) {
            ind++;
            continue;
        } else {
            return false;
        }
    }
    return true;
}


/// Оператор &lt;
/// <param name="rhs">Объект, который стоит после знака "&lt;" </param>
/// <returns>Возвращаем значения сравнения двух строк</returns>
bool String::operator<(const String &rhs) const {
    size_t ind = 0;
    while (Data[ind] || rhs[ind]) {
        if (Data[ind] < rhs[ind]) {
            ind++;
            continue;
        } else {
            return false;
        }
    }
    return true;
}

/// Функция поиска подстроки
/// <param name="substr">Подстрока, которую необходимо найти </param>
/// <returns>Возвращаем позицию substr. Если подстрока не найдена, то
/// возвратить -1</returns>
size_t String::Find(const String &substr) const {
    size_t thisSize = Size();
    size_t subSize = substr.Size();
    for (size_t ind = 0; ind < thisSize; ind++) {
        if (Data[ind] != substr[0]) continue;
        for (size_t subInd = 0; subInd < subSize; subInd++) {
            if (ind + subInd > thisSize) return static_cast<size_t>(-1);
            if (Data[ind + subInd] != substr[subInd]) break;
            else if (subInd == subSize - 1) return ind;
        }
    }
    return static_cast<size_t>(-1);
}

/// Функция поиска подстроки
/// Только в этот раз для char*, привет тревис...
/// <param name="substr">Подстрока, которую необходимо найти </param>
/// <returns>Возвращаем позицию substr. Если подстрока не найдена, то
/// возвратить -1</returns>
size_t String::Find(const char *str) const {
    String tmp(str);
    return Find(tmp);
}

/// Функция замены символов, заменяет все символы oldSymbol на newSymbol.
/// <param name="oldSymbol">Символ, который требуется заменить </param>
/// <param name="newSymbol">Символ, на который требуется заменить </param>
void String::Replace(char oldSymbol, char newSymbol) {
    size_t thisSize = Size();
    for (size_t ind = 0; ind < thisSize + 1; ind++) {
        if (Data[ind] == oldSymbol) Data[ind] = newSymbol;
    }
}

/// Функция возвращает длину строки
/// <returns>Возвращаем длину строки</returns>
size_t String::Size() const {
    size_t ind = 0;
    while (Data[ind]) ind++;
    return ind;
} /// returns number of characters in container before null-terminator


/// Функция для определения пуста ли строка
bool String::Empty() const {
    return (Data[0] == 0);
}

/// Оператор []
/// <example>
/// <code>
/// String str = "some string";
/// char symbol = str[2]; // symbol == 'm'
/// </code>
/// </example>
/// <param name="index"> Индекс символа </param>
/// <returns> Значение символа в строке с индексом index</returns>
char String::operator[](size_t index) const {
    return Data[index];
}

/// Оператор []
/// <example>
/// <code>
/// String str = "some string";
/// str[0] = 'S'; // теперь переменная str равна "Some string"
/// </code>
/// </example>
/// <param name="index"> Индекс символа </param>
/// <returns> Ссылка на символ в строке с индексом index</returns>
char &String::operator[](size_t index) {
    return Data[index];
}

/// Смотри пример
/// <example>
/// <code>
/// String str = "___some string___";
/// str.RTrim('_'); // теперь переменная str равна "___some string"
/// </code>
/// </example>
/// <param name="symbol"> Значение символов, которе отрезаем </param>
void String::RTrim(char symbol) {
    size_t ind = Size() - 1;
    do {
        if (Data[ind] != symbol) return;
        Data[ind] = 0;
    } while (ind-- != 0);
}

/// Смотри пример
/// <example>
/// <code>
/// String str = "___some string___";
/// str.LTrim('_'); // теперь переменная str равна "some string___"
/// </code>
/// </example>
/// <param name="symbol"> Значение символов, которе отрезаем </param>
void String::LTrim(char symbol) {
    size_t pos = 0;
    size_t thisSize = Size();
    while (Data[pos] == symbol) pos++;
    for (size_t ind = 0; ind <= thisSize + 1 - pos; ind++) {
        Data[ind] = Data[ind + pos];
    }
}

//Обойдемся без <utility>, раз уж первая даба
void String::swap(String &oth) {
    char *tmpData = Data;
    size_t tmpCapasity = capasity;

    Data = oth.Data;
    capasity = oth.capasity;

    oth.Data = tmpData;
    oth.capasity = tmpCapasity;
}

/// Освобождает неиспользуемую память

void String::shrink_to_fit() {
    capasity = Size() + 1;
    char *tmp = new char[capasity];
    for (size_t i = 0; i < capasity; i++) {
        tmp[i] = Data[i];
    }
    delete[] Data;
    Data = tmp;
}

///outer-class functions


/// Оператор +
/// <example>
/// <code>
/// String a = "Hello";
/// String b = "World";
/// String c = a + b; // c равна "HelloWorld"
/// </code>
/// </example>
/// <returns>Возвращаем строку равную a + b</returns>
String operator+(const String &a, const String &b) {
    String tmp(a);
    tmp += b;
    return tmp;
}

/// Оператор *
/// <example>
/// <code>
/// String a = "A";
/// String c = a * 5; // c равна "AAAAA"
/// </code>
/// </example>
String operator*(const String &a, unsigned int b) {
    String tmp(a);
    tmp *= b;
    return tmp;
}

/// Оператор !=
bool operator!=(const String &a, const String &b) {
    return !(a == b);
}

/// Оператор &gt;
bool operator>(const String &a, const String &b) {
    return !(a < b || a == b);
}

/// Оператор вывода
/// <param name="out">Поток куда выводим строку </param>
/// <param name="str">Строка, которую выводим </param>
/// <returns>Возвращаем ссылку на поток</returns>
std::ostream &operator<<(std::ostream &out, const String &str) {
    for (size_t ind = 0; ind < str.Size(); ind++) out << str.Data[ind];
    return out;
}

/// Оператор ==
/// Сравнивает левый операнд const char* и правый const String&
/// Все ради тебя, тревис (；⌣̀_⌣́)

bool operator==(const char *ls, const String &rs) {
    size_t ind = 0;
    while (ls[ind] || rs[ind]) {
        if (ls[ind] != rs[ind]) return false;
        ind++;
    }
    return true;
}
