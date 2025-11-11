#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Pipe.h"
#include "Ks.h"
#include "temp.h"
#include "search.h"
#include "logger.h"

using namespace std;

void NewPipe(map<int, Pipe>& Pipes, int& pipes_id) {
    Pipe newPipe;
    cin >> newPipe;

    Pipes[pipes_id] = newPipe;
    pipes_id++;

    system("cls");
}

void NewKs(map<int, Ks>& stations, int& stations_id) {
    Ks newKs;
    cin >> newKs;

    stations[stations_id] = newKs;
    stations_id++;

    system("cls");
}

vector<int> Selections(const std::string& enter) {
    std::vector<int> elements;
    std::stringstream ss(enter);
    int n;

    while (ss >> n) {
        elements.push_back(n);
    }

    if (!ss.eof()) {
        return {};
    }

    return elements;
}

void EditPipes(map<int, Pipe>& pipes, vector<int> selectedPipes) {
    cout << "\nДействия\n1. Изменить имя\n2. Изменить длину\n3. Изменить диаметр\n4. Изменить состояние\n5. Удалить\n0. Выход в меню\nВыбор: ";

    int choice = Enter<int>();
    string n;
    float l;
    int d;
    bool r;

    switch (choice) {
    case 1:
        cout << "Новое имя: ";
        n = Enter<string>();
        for (const auto& x : selectedPipes)
            pipes[x].setName(n);
        break;
    case 2:
        cout << "Новая длина: ";
        l = Enter<float>();
        while (l <= 0) {
            std::cout << "Длина должна превышать 0\nПовторите ввод";
            l = Enter<float>();
        }

        for (const auto& x : selectedPipes)
            pipes[x].setLength(l);
        break;
    case 3:
        cout << "Новый диаметр: ";
        d = Enter<int>();
        while (d <= 0) {
            std::cout << "Диаметр должен превышать 0\nПовторите ввод";
            d = Enter<int>();
        }

        for (const auto& x : selectedPipes)
            pipes[x].setDiameter(d);
        break;
    case 4:
        cout << "Новое состояние (0/1): ";
        r = Enter<bool>();

        for (const auto& x : selectedPipes)
            pipes[x].setRepair(r);
        break;
    case 5:
        for (const auto& x : selectedPipes)
            pipes.erase(x);
        break;
    case 6:
        break;
    }
}

void EditStations(map<int, Ks>& stations, vector<int> selectedStations) {
    cout << "\nДействия\n1. Изменить имя\n2. Изменить количество цехов\n3. Изменить количество цехов в работе\n4. Изменить тип\n5. Удалить\n0. Выход в меню\nВыбор: ";

    int choice = Enter<int>();
    int c;
    string n;
    int w;

    switch (choice) {
    case 1:
        cout << "Новое имя: ";
        n = Enter<string>();
        for (const auto& x : selectedStations)
            stations[x].setName(n);
        break;
    case 2:
        c = 0;
        for (const auto& x : selectedStations)
            if (stations[x].getWorkshopsWorking() > c)
                c = stations[x].getWorkshopsWorking();

        cout << "Новое количество цехов: ";
        w = Enter<int>();
        while (w < 0 || w < c) {
            std::cout << "Число должно быть положительным и больше" << c << "\nПовторите ввод: ";
            w = Enter<int>();
        }

        for (const auto& x : selectedStations)
            stations[x].setWorkshopsCount(w);
        break;
    case 3:
        c = 100000000;
        for (const auto& x : selectedStations)
            if (stations[x].getWorkshopsCount() < c)
                c = stations[x].getWorkshopsCount();

        cout << "Новое количество цехов в работе: ";
        w = Enter<int>();

        while (w > c || w < 0) {
            std::cout << "Количество не должно превышать общее количество цехов. (0 <= count <= " << c << ")\nПовторите ввод : ";
            w = Enter<int>();
        }

        for (const auto& x : selectedStations)
            stations[x].setWorkshopsWorking(w);
        break;
    case 4:
        cout << "Новый тип: ";
        n = Enter<string>();

        for (const auto& x : selectedStations)
            stations[x].setType(n);
        break;
    case 5:
        for (const auto& x : selectedStations)
            stations.erase(x);
        break;
    case 6:
        break;
    }
}

void EditDifferent(map<int, Pipe>& pipes, map<int, Ks>& stations, vector<int> selectedPipes, vector<int> selectedStations) {
    cout << "\nДействия\n1. Изменить имя\n2. Удалить\n0. Назад в меню\nВыбор: ";

    int choice = Enter<int>();
    string n;

    switch (choice) {
    case 1:
        cout << "Новое имя: ";
        n = Enter<string>();
        for (const auto& x : selectedPipes)
            pipes[x].setName(n);
        for (const auto& x : selectedStations)
            stations[x].setName(n);
        break;
    case 2:
        for (const auto& x : selectedPipes)
            pipes.erase(x);
        for (const auto& x : selectedStations)
            stations.erase(x);
    case 0:
        break;
    }
}

void SelectionToGroups(map<int, Pipe>& pipes, map<int, Ks>& stations, vector<int>& elements, vector<int>& selectedPipes, vector<int>& selectedStations) {
    for (int i = 0; i < elements.size(); i++) {
        if (pipes.count(elements[i]) > 0)
            selectedPipes.push_back(elements[i]);
        if (stations.count(elements[i]) > 0)
            selectedStations.push_back(elements[i]);
    }

    system("cls");
    cout << "Элементы: ";
    for (const auto& x : selectedPipes) {
        cout << "ID: " << x << endl;
        cout << pipes[x];
        cout << endl;
    }

    for (const auto& x : selectedStations) {
        cout << "ID: " << x << endl;
        cout << stations[x];
        cout << endl;
    }
}

void EditSelection(map<int, Pipe>& pipes, map<int, Ks>& stations, vector<int> elements) {
    vector<int> selectedPipes = {};
    vector<int> selectedStations = {};

    SelectionToGroups(pipes, stations, elements, selectedPipes, selectedStations);

    if (selectedPipes.size() == 0 && selectedStations.size() == 0) return;
    else if (selectedPipes.size() == 0 || selectedStations.size() == 0) {
        if (selectedPipes.size() > 0)
            EditPipes(pipes, selectedPipes);
        else
            EditStations(stations, selectedStations);
    }
    else
        EditDifferent(pipes, stations, selectedPipes, selectedStations);

    system("cls");
    cout << "Операция выполнена!" << endl;
}

void ShowAll(map<int, Pipe>& Pipes, map<int, Ks>& stations) {
    system("cls");
    for (const auto& pair : Pipes) {
        cout << "ID: " << pair.first << endl;
        cout << Pipes[pair.first];
        cout << endl;
    }

    for (const auto& pair : stations) {
        cout << "ID: " << pair.first << endl;
        cout << stations[pair.first];
        cout << endl;
    }

    cout << "Выберите элементы через пробел или нажмите Enter, чтобы вернуться в меню:\n";
    string enter;
    enter = LoggedInput();

    vector<int> elements = Selections(enter);
    if (elements.size() == 0) { return; }
    else { EditSelection(Pipes, stations, elements); }
}

void Search(map<int, Pipe>& pipes, map<int, Ks>& stations) {
    system("cls");
    cout << "Искать: \n1. по имени\n2. трубы по признаку 'в ремонте'\n3. станции по проценту незадействованных цехов\nВыбор: ";
    int enter = Enter<int>();
    vector<int> elements = {};

    system("cls");
    switch (enter) {
    case 1:
        elements = SearchByName(pipes, stations);
        break;
    case 2:
        elements = SearchByRepair(pipes);
        break;
    case 3:
        elements = SearchByWorkshops(stations);
        break;
    };
    system("cls");

    if (elements.size() == 0)
        cout << "Не найдено элементов по заданным параметрам" << endl;
    else {
        EditSelection(pipes, stations, elements);
    }
}

void SaveData(map<int, Pipe>& pipes, map<int, Ks>& stations) {
    cout << "Введите имя файла: ";
    string fileName = Enter<string>();

    ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (const auto& pair : pipes) {
            outFile << "#PIPE" << endl;
            outFile << pipes[pair.first] << endl;
        }

        for (const auto& pair : stations) {
            outFile << "#KS" << endl;
            outFile << pair.first << endl;
            outFile << stations[pair.first].getName() << endl;
            outFile << stations[pair.first].getWorkshopsCount() << endl;
            outFile << stations[pair.first].getWorkshopsWorking() << endl;
            outFile << stations[pair.first].getType() << endl;
            outFile << endl;
        }

        outFile.close();

        system("cls");
        cout << "Сохранено в data.txt" << endl;
    }

    else
        cout << "Ошибка открытия файла";
}

void LoadData(std::map<int, Pipe>& pipes, std::map<int, Ks>& stations, int& pipes_id, int& stations_id) {
    cout << "Введите имя файла: ";
    string fileName = Enter<string>();

    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл " << fileName << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line == "#PIPE") {
            int id;
            if (!(inFile >> id)) { cout << "Ошибка ID станции\n"; return; }
            inFile.ignore();

            Pipe truba;
            inFile >> truba;
            pipes[id] = truba;
            if (id >= pipes_id) pipes_id = id + 1;
        }

        else if (line == "#KS") {
            int id;
            string name;
            int workshops_count;
            int workshops_working;
            string type;

            if (!(inFile >> id)) { cout << "Ошибка ID станции\n"; return; }
            inFile.ignore();

            getline(inFile, name);
            if (!(inFile >> workshops_count)) { cout << "Ошибка количества цехов\n"; return; }
            inFile.ignore();

            if (!(inFile >> workshops_working)) { cout << "Ошибка количества работающих цехов\n"; return; }
            inFile.ignore();

            getline(inFile, type);

            stations[id] = Ks(name, workshops_count, workshops_working, type);
            if (id >= stations_id) stations_id = id + 1;
        }
    }

    system("cls");
    cout << "Данные успешно загружены!\n";
}

void Menu(map<int, Pipe>& pipes, map<int, Ks>& stations, int& pipes_id, int& stations_id) {
    while (true) {
        cout << "Меню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Поиск\n5. Сохранить\n6. Загрузить\n0. Выход\nВыбор: ";

        int choice = Enter<int>();
        switch (choice) {
        case 1:
            NewPipe(pipes, pipes_id);
            break;
        case 2:
            NewKs(stations, stations_id);
            break;
        case 3:
            ShowAll(pipes, stations);
            break;
        case 4:
            Search(pipes, stations);
            break;
        case 5:
            SaveData(pipes, stations);
            break;
        case 6:
            LoadData(pipes, stations, pipes_id, stations_id);
            break;
        case 0:
            exit(0);
        }
    }
}

int main()
{
    map<int, Pipe> pipes;
    map<int, Ks> stations;
    int pipes_id = 0;
    int stations_id = 0;

    setlocale(LC_ALL, "rus");
    Menu(pipes, stations, pipes_id, stations_id);
    return 0;
}
