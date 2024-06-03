#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;


template<typename K, typename T>
class MyUnorderedMap {
private:
    vector < list < pair<K, T>>> table;
    size_t size;

    size_t hashFunc(const K& key) {
        return hash<K>{}(key) % table.size();
    }


public:
    MyUnorderedMap(size_t initialSize) : size(initialSize) {
        table.resize(size);
    }

    MyUnorderedMap(initializer_list < pair < K, T>> values) {
        size = values.size() * 2; 
        table.resize(size);
        for (const auto& pair : values) {
            insert(pair.first, pair.second);
        }
    }

    MyUnorderedMap(const MyUnorderedMap& other) : size(other.size), table(other.table) {}

    ~MyUnorderedMap() {}

    MyUnorderedMap& operator=(const MyUnorderedMap& other) {
        if (this != &other) {
            size = other.size;
            table = other.table;
        }
        return *this;
    }

    void print() {
        for (size_t i = 0; i < size; ++i) {
            cout << i << ": ";
            for (const auto& pair : table[i]) {
                cout << pair.first << " -> " << pair.second << " ";
            }
            cout << endl;
        }
    }

    void insert(K key, T value) {
        size_t index = hashFunc(key);
        bool inserted = false;
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                cout << "Ошибка! Ключ дублируется, вставлять отказываемся." << endl;
                system("pause");
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            table[index].push_back(make_pair(key, value));
        }
    }

    void insert_or_assign(K key, T value) {
        size_t index = hashFunc(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back(make_pair(key, value));
    }

    bool contains(K key) {
        size_t index = hashFunc(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    T* search(K key) {
        size_t index = hashFunc(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    bool erase(K key) {
        size_t index = hashFunc(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    int count(K key) {
        size_t index = hashFunc(key);
        int count = 0;
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                count++;
            }
        }
        return count;
    }
    

};

int romanToDecimal(const std::string& roman) {
    MyUnorderedMap<char, int> romanMap(10);

    romanMap.insert('I', 1);
    romanMap.insert('V', 5);
    romanMap.insert('X', 10);
    romanMap.insert('L', 50);
    romanMap.insert('C', 100);
    romanMap.insert('D', 500);
    romanMap.insert('M', 1000);

    int result = 0;
    int prevValue = 0;

    for (char c : roman) {
        int curValue = *romanMap.search(c);
        if (curValue > prevValue) {
            result = result - 2 * prevValue + curValue; // Вычитание дважды предыдущего значения, так как оно уже было добавлено
        }
        else {
            result += curValue;
        }
        prevValue = curValue;
    }

    return result;
}


int main() {
    setlocale(LC_ALL, "Russian");
    MyUnorderedMap<int, string> map(10);
    int choice;
    do {
        cout << "Выберите действие" << endl;
        cout << "1 - Вставка значения по ключу" << endl;
        cout << "2 - Вставка или присвоение значения по ключу" << endl;
        cout << "3 - Печать содержимого" << endl;
        cout << "4 - Проверка наличия элемента" << endl;
        cout << "5 - Поиск элемента" << endl;
        cout << "6 - Удаление элемента по значению" << endl;
        cout << "7 - Возвращает количество элементов по соответствующему ключу." << endl;
        cout << "8 - Задание" << endl;
        cout << "0 - Выход" << endl;
        cout << "Операция: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            int key;
            string value;
            cout << "Введите ключ: ";
            cin >> key;
            cout << "Введите значение: ";
            cin >> value;
            map.insert(key, value);
            system("cls");
            break; 
        }
        case 2: {
            int key2;
            string value2;
            cout << "Введите ключ: ";
            cin >> key2;
            cout << "Введите значение: ";
            cin >> value2;
            map.insert_or_assign(key2, value2);
            system("cls");
            break; }
        case 3:
            map.print();
            break;
        case 4:
            int key3;
            cout << "Введите ключ: ";
            cin >> key3;
            if (map.contains(key3)) {
                cout << "Элемент существует\n";
            }
            else {
                cout << "Элемент не существует\n";
            }
            break;
        case 5:
            int key4;
            cout << "Введите ключ: ";
            cin >> key4;
            cout << "Значение: " << map.search(key4) << endl;
            break;
        case 6:
            int key5;
            cout << "Введите ключ: ";
            cin >> key5;
            map.erase(key5);
            break;
        case 7:
            int key6;
            cout << "Введите ключ: ";
            cin >> key6;
            cout << "Количество: " << map.count(key6) << endl;
            break;
        case 8: 
            string romanNum;

            cout << "Введите римское число: ";
            cin >> romanNum;

            int decimalNum = romanToDecimal(romanNum);

            if (decimalNum != -1) {
                cout << "Десятичное представление: " << decimalNum << endl;
            } else {
                cout << "Введено некорректное римское число." << endl;
            }
            break;


}
    } while (choice != 0);
    return 0;
}
