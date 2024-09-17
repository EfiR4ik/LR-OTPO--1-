#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void fileInput(vector<vector<int>>& arrays) {
    ifstream infile("D:/input.txt");
    if (!infile) {
        cout << "Ошибка открытия файла\n";
        return;
    }
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        int size;
        ss >> size; // Первое число - это размер массива
        vector<int> array(size);
        for (int i = 0; i < size; ++i) {
            ss >> array[i]; // Чтение элементов массива
        }
        arrays.push_back(array); // Добавление массива в вектор
    }
    infile.close();
}

void sortedFileInput(vector<vector<int>>& sortedArrays) {
    ifstream infile("D:/sorted.txt");
    if (!infile) {
        cout << "Ошибка открытия файла с отсортированными массивами\n";
        return;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        int size;
        ss >> size; // Первое число - это размер массива
        vector<int> array(size);
        for (int i = 0; i < size; ++i) {
            ss >> array[i]; // Чтение элементов массива
        }
        sortedArrays.push_back(array); // Добавление массива в вектор
    }
    infile.close();
}

void input(int* a, int size) {
    for (int i = 0; i < size; ++i) {
        cin >> a[i]; // ввод массива
    }
}

int bubbleSort(int* array, int size) { // сортировка
    int swap_counter = 0;
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j <= size - i; ++j) {
            if (array[j - 1] > array[j]) {
                swap(array[j - 1], array[j]);
                swap_counter++;
            }
        }
    }
    return swap_counter;
}

bool test(const vector<int>& sortedArray, const vector<int>& computedArray) {
    return sortedArray == computedArray;
}

int main() {
    SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

    cout << "Выберите режим: \n 1. Ручной ввод\n 2. Файл \n";
    string com;
    cin >> com;

    if (com == "1") {
        cout << "Вы выбрали ручной ввод.\n";
        int size;
        cout << "Вход ";
        cin >> size;
        int* mainArray{ new int[size] };
        // cout << "Введите элементы массива: ";
        input(mainArray, size);
        cout << "Ответ ";
        cout << bubbleSort(mainArray, size) << " ";
        for (int j = 0; j < size; ++j) {
            cout << mainArray[j] << " ";
        }
        delete[] mainArray;
    }
    else if (com == "2") {
        cout << "Вы выбрали ввод из файла.\n";
        vector<vector<int>> arrays; // Вектор для хранения массивов
        fileInput(arrays); // Читаем массивы из файла

        // Вектор для хранения заранее отсортированных массивов
        vector<vector<int>> sortedArrays;
        sortedFileInput(sortedArrays); // Читаем отсортированные массивы

        vector<vector<int>> computedArrays; // Вектор для хранения отсортированных массивов
        int testCounter = 0;
        int testCounterNum = 1;
        for (size_t i = 0; i < arrays.size(); ++i) {
            // Вывод исходного массива
            cout << "Вход " << arrays[i].size() << " ";
            for (auto num : arrays[i]) {
                cout << num << " ";
            }

            // Сортируем каждый массив
            int size = arrays[i].size();
            int* arrayToSort = new int[size];
            copy(arrays[i].begin(), arrays[i].end(), arrayToSort); // Копируем данные в массив
            cout << " Ответ ";
            int swaps = bubbleSort(arrayToSort, size); // Сортируем массив и получаем количество смен

            // Вывод отсортированного массива
            for (int j = 0; j < size; ++j) {
                cout << arrayToSort[j] << " ";
            }
            cout << "\nКоличество обменов: " << swaps << "\n";

            // Сохраняем отсортированный массив для проверки
            computedArrays.push_back(vector<int>(arrayToSort, arrayToSort + size));

            // Проверка отсортированных массивов
            if (test(sortedArrays[i], computedArrays[i])) {
                cout << " Тест " << testCounterNum++ << " Результат да\n" << endl;
                testCounter++;

            }
            else {
                cout << " Тест " << testCounterNum++ << " Результат нет\n" << endl;
            }
            delete[] arrayToSort; // Освобождаем память
        }

        cout << "Тестов пройдено " << testCounter << endl;
        system("Pause");
        return 0;
    }
    else {
        cout << "Ошибка ввода";
        system("Pause");
        return 0;
    }
}
