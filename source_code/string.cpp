//
// "Copyright 2019 Semenov Pavel Corporation"  [legal]

#include "../include/string.hpp"

String::~String() {
    if (Data == nullptr) return;
    delete[] Data;
}

String::String() {
    Data = nullptr;
}

String::String(const String &rhs) {
    Data = nullptr;
    *this = rhs;   //0x602000000451
}

String::String(const char *data) {
    /*  size_t ind = 0;
      while (data[ind]) ind++;
      //capasity = size_t((ind) * 1.5);
      capasity = ind + 1;
      Data = nullptr;
      if (capasity != 0) {
          Data = new char[capasity];
          for (size_t i = 0; i <= ind; i++) {
              Data[i] = data[i];
          }*/
    size_t ind;
    for (ind = 0; data[ind] != 0; ind++) continue;
    Data = new char[ind + 2];
    for (size_t i = 0; i <= ind; i++) {
        Data[i] = data[i];
    }
}

String &String::operator=(const String &rhs) {
    if (this != &rhs) {
        //capasity = size_t((rhs.Size()) * 1.5);
        capasity = rhs.Size() + 1;
        Data = new char[capasity+1];
        int ind = 0;
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
/*    //    if (capasity < this->Size() + rhs.Size() + 1) {
        //capasity = size_t((capasity + rhs.Size() + 1) * 1.5);
        capasity = Size() + rhs.Size() + 1;
        char *temp = new char[capasity];
        for (size_t i = 0; i < capasity; i++) {
            temp[i] = Data[i];
//        }
        delete[] Data;
        Data = temp;
        temp = nullptr;
    }
    size_t tempSize = this->Size(), rhSize = rhs.Size();
    for (size_t ind = tempSize, i = 0; ind <= tempSize + \
    rhSize + 1; ind++) {
        Data[ind] = rhs[i];
        i++;
    }
    return (*this);*/
    size_t thisSize = Size();
    size_t fSize = rhs.Size() + thisSize + 1;
    char *tmp = new char[fSize];
    for (size_t a = 0; a < fSize; a++) {
        if (a < thisSize) {
            tmp[a] = Data[a];
        } else {
            tmp[a] = rhs.Data[a - thisSize];
        }
    }
    if (!Empty()) delete[] Data;
    Data = tmp;
    tmp = nullptr;
    // delete []temp;
    return *this;
}

/// Оператор +=
/// Чтоб Тревис не ныл
/// <param name="rhs">Объект, который стоит после знака '+=' </param>
/// <returns>Возвращаем ссылку на себя</returns>
String &String::operator+=(const char *rhs) {
    /* size_t len = 0;
     size_t thisSize = this->Size();
     while (rhs[len]) len++;

     if (capasity < thisSize + len + 1) {
         //capasity = size_t((capasity + len + 1) * 1.5);
         capasity = capasity + len + 1; //+1
         //Data = reinterpret_cast<char *>(realloc(Data, capasity));
         char *tmp = new char[capasity];
         for (size_t i = 0; i < capasity; i++) {
             tmp[i] = Data[i];
         }
         delete[] Data;
         Data = tmp;
         tmp = nullptr;
     }
     thisSize = this->Size();
     for (size_t ind = thisSize, i = 0; i <= len; ind++) {
         Data[ind] = rhs[i++];
     }
     return (*this);*/
    size_t thisSize = Size();
    size_t ind;
    for (ind = 0; rhs[ind] != 0; ind++) {
    }
    size_t fSize = thisSize + ind + 1;
    char *temp = new char[fSize];
    for (size_t ind2 = 0; ind2 < fSize; ind2++) {
        if (ind2 < thisSize) {
            temp[ind2] = Data[ind2];
        } else {
            temp[ind2] = rhs[ind2 - thisSize];
        }
    }
    if (!Empty()) delete[] Data;
    Data = temp;
    temp = nullptr;
    return *this;
}

/// Оператор *=
/// <returns>Возвращаем ссылку на себя</returns>
String &String::operator*=(unsigned int m) {
/*    if (capasity < this->Size() * m + 1) {
        //capasity = size_t(this->Size() * m * 1.5 + 1);
        capasity = this->Size() * m + 1;
        //Data = reinterpret_cast<char *>(realloc(Data, capasity));
        char *tmp = new char[capasity];
        for (size_t i = 0; i < capasity; i++) {
            tmp[i] = Data[i];
        }
        delete[] Data;
        Data = tmp;
        tmp = nullptr;
    }
    size_t startSize = this->Size();
    for (size_t ind = this->Size(); ind < startSize * m; ind++) {
        Data[ind] = Data[ind % startSize];
    }
    //Data[startSize * m] = 0;
    return (*this);*/
    capasity = Size() * m + 1;
    size_t size = Size();
    char *tmp = new char[capasity];
    for (size_t i = 0; i < capasity; i++) {
        tmp[i] = Data[i%size];
    }
    tmp[size*m] = 0;
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
    size_t thisSize = this->Size();
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
    size_t subSize = 0;
    while (str[subSize]) subSize++;
    size_t thisSize = this->Size();
    for (size_t i = 0; i < thisSize; i++) {
        if (Data[i] != str[0]) continue;
        for (size_t j = 0; j < subSize; j++) {
            if (i + j > thisSize) return static_cast<size_t>(-1);
            if (Data[i + j] != str[j]) break;
            else if (j == subSize - 1) return i;
        }
    }

    return static_cast<size_t>(-1);
}

/// Функция замены символов, заменяет все символы oldSymbol на newSymbol.
/// <param name="oldSymbol">Символ, который требуется заменить </param>
/// <param name="newSymbol">Символ, на который требуется заменить </param>
void String::Replace(char oldSymbol, char newSymbol) {
    size_t thisSize = this->Size();
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
    size_t ind = this->Size() - 1;
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
    size_t thisSize = this->Size();
    while (Data[pos] == symbol) pos++;
    for (size_t ind = 0; ind <= thisSize + 1 - pos; ind++) {
        Data[ind] = Data[ind + pos];
    }
}

void String::swap(String &oth) {
    String temp = *this;
    *this = oth;
    oth = temp;
}

void String::shrink_to_fit() {
    capasity = this->Size() + 1;
    //Data = reinterpret_cast<char *>(realloc(Data, capasity));
    char *tmp = new char[capasity];
    for (size_t i = 0; i < capasity; i++) {
        tmp[i] = Data[i];
    }
    delete[] Data;
    Data = tmp;
    tmp = nullptr;
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
    size_t aSz = a.Size(), bSz = b.Size();
    size_t full = aSz + bSz + 1;
    //char *tmp = static_cast<char *>(calloc(full, sizeof(char)));
    char *tmp = new char[full];
    for (size_t ind = 0; ind < full; ind++) {
        if (ind < aSz) {
            tmp[ind] = a[ind];
        } else {
            tmp[ind] = b[ind - aSz];
        }
    }
    String itog(tmp);
    delete[]tmp;
    return itog;
}

/// Оператор *
/// <example>
/// <code>
/// String a = "A";
/// String c = a * 5; // c равна "AAAAA"
/// </code>
/// </example>
String operator*(const String &a, unsigned int b) {
    size_t thisSize = a.Size();
    //char *tmp = static_cast<char *>(calloc(thisSize * b + 1, sizeof(char)));
    char *tmp = new char[thisSize * b + 1];
    for (size_t i = 0; i < b; i++) {
        for (size_t j = 0; j < thisSize; j++) {
            tmp[j + i * thisSize] = a[j];
        }
    }
    tmp[thisSize * b] = 0;
    String tmpNew(tmp);
    delete[]tmp;
    return tmpNew;
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
