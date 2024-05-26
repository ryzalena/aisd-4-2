#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;


template<typename K, typename T>
class MyUnorderedMap {
private:
    std::vector < std::list < std::pair<K, T>>> table;
    size_t size;

    size_t hashFunc(const K& key) {
        return std::hash<K>{}(key) % table.size();
    }

public:
    MyUnorderedMap(size_t initialSize) : size(initialSize) {
        table.resize(size);
    }

    MyUnorderedMap(std::initializer_list < std::pair < K, T>> values) {
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
            std::cout << i << ": ";
            for (const auto& pair : table[i]) {
                std::cout << pair.first << " -> " << pair.second << " ";
            }
            std::cout << std::endl;
        }
    }

    void insert(K key, T value) {
        size_t index = hashFunc(key);
        table[index].push_back(std::make_pair(key, value));
    }

    void insert_or_assign(K key, T value) {
        size_t index = hashFunc(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back(std::make_pair(key, value));
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

class HashMap {
private:
    static const int TABLE_SIZE = 10;

    struct Node {
        std::string key;
        int value;
        Node* next;
        Node(const std::string& key, int value) : key(key), value(value), next(nullptr) {}
    };

    Node* table[TABLE_SIZE];

    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char c : key) {
            hash += static_cast<int>(c);
        }
        return hash % TABLE_SIZE;
    }

public:
    HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    void insert(const std::string& key, int value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    int get(const std::string& key) {
        int index = hashFunction(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return -1;
    }
};

int romanToDecimal(const std::string& roman) {
    HashMap romanMap;
    romanMap.insert("I", 1);
    romanMap.insert("V", 5);
    romanMap.insert("X", 10);
    romanMap.insert("L", 50);
    romanMap.insert("C", 100);
    romanMap.insert("D", 500);
    romanMap.insert("M", 1000);

    int result = 0;
    for (size_t i = 0; i < roman.size(); ++i) {
        int currentValue = romanMap.get(std::string(1, roman[i]));
        if (i + 1 < roman.size()) {
            int nextValue = romanMap.get(std::string(1, roman[i + 1]));
            if (currentValue < nextValue) {
                result += nextValue - currentValue;
                ++i;
            }
            else {
                result += currentValue;
            }
        }
        else {
            result += currentValue;
        }
    }

    return result;
}


int main() {
    setlocale(LC_ALL, "Russian");
    MyUnorderedMap<int, std::string> map(10);
    //MyHashMap<int, std::string> map(10);
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
        std::cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            int key;
            std::string value;
            std::cout << "Введите ключ: ";
            std::cin >> key;
            std::cout << "Введите значение: ";
            std::cin >> value;
            map.insert(key, value);
            system("cls");
            break; 
        }
        case 2: {
            int key2;
            std::string value2;
            std::cout << "Введите ключ: ";
            std::cin >> key2;
            std::cout << "Введите значение: ";
            std::cin >> value2;
            map.insert_or_assign(key2, value2);
            system("cls");
            break; }
        case 3:
            map.print();
            break;
        case 4:
            int key3;
            std::cout << "Введите ключ: ";
            std::cin >> key3;
            if (map.contains(key3)) {
                std::cout << "Элемент существует\n";
            }
            else {
                std::cout << "Элемент не существует\n";
            }
            break;
        case 5:
            int key4;
            std::cout << "Введите ключ: ";
            std::cin >> key4;
            std::cout << "Значение: " << map.search(key4) << std::endl;
            break;
        case 6:
            int key5;
            std::cout << "Введите ключ: ";
            std::cin >> key5;
            map.erase(key5);
            break;
        case 7:
            int key6;
            std::cout << "Введите ключ: ";
            std::cin >> key6;
            std::cout << "Количество: " << map.count(key6) << std::endl;
            break;
        case 8:
            std::string romanNumber;
            std::cout << "Введите римское число: ";
            std::cin >> romanNumber;

            int decimalNumber = romanToDecimal(romanNumber);
            std::cout << "Десятичный вид: " << decimalNumber << std::endl;
            break;


}
    } while (choice != 0);
    return 0;
}
