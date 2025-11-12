#pragma once
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "GasNetwork.h"
#include "Connection.h"
#include "Pipe.h"
#include "Ks.h"
#include "temp.h"
#include "search.h"
#include "logger.h"

using namespace std;

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

template<typename T>
vector<int> IdList(map<int, T> m) {
    vector<int> keys;

    for (const auto& pair : m) {
        keys.push_back(pair.first);
    }

    return keys;
}

bool is_element(vector<int> vec, int n) {
    for (int m : vec) 
        if (m == n) return true;
    return false;
}

GasNetwork::GasNetwork() : name(""), pipes({}), stations({}), pipes_id(0), stations_id(0) {}

bool GasNetwork::can_be_paired(int start_id, int stop_id) {
    if (start_id == stop_id) return false;
    for (Connection con : connections)
        if ((con.start_id == start_id && con.stop_id == stop_id) || (con.start_id == stop_id && con.stop_id == start_id)) return false;
    return true;
}

bool GasNetwork::can_be_pipe(int pipe_id) {
    for (Connection con : connections)
        if (con.pipe_id == pipe_id) return false;
    return true;
}

vector<int> GasNetwork::search_by_diameter(int diameter) {

    vector<int> elements = {};
    for (const auto& pair : pipes) {
        if (pair.second.getDiameter() == diameter && !pair.second.isRepair() && can_be_pipe(pair.first))
            elements.push_back(pair.first);
    }
    return elements;
}

void GasNetwork::EraseConnection() {
    cout << "\nВыберите соединение для удаления. Для этого введите номер трубы в этом соединении: ";
    int enter = Enter<int>();
    int x = 0;

    for (Connection con : connections)
        if (con.pipe_id == enter) {
            connections.erase(connections.begin() + x);
            x++;
        }
}

void GasNetwork::EraseConnections_byPipe(int pipe_id) {
    int x = 0;
    for (Connection con : connections) {
        if (con.pipe_id == pipe_id)
            connections.erase(connections.begin() + x);
        else { x++; }
    }     
}

void GasNetwork::EraseConnections_byKs(int station_id) {
    int x = 0;
    for (Connection con : connections) {
        if (con.start_id == station_id || con.stop_id == station_id)
            connections.erase(connections.begin() + x);
        else { x++; }
    }
}

void GasNetwork::NewPipe() {
    Pipe newPipe;
    cin >> newPipe;

    pipes[pipes_id] = newPipe;
    pipes_id++;

    system("cls");
}

void GasNetwork::NewKs() {
    Ks newKs;
    cin >> newKs;

    stations[stations_id] = newKs;
    stations_id++;

    system("cls");
}

void GasNetwork::NewConnection() {
    int start_id = -2;
    bool no_exit = true;
    vector<int> station_ids = IdList(stations);

    cout << "(-1 для выхода в меню)\n";
    while (no_exit) {
        cout << "Введите ID КС входа: ";
        start_id = Enter<int>();

        if (start_id == -1) { no_exit = false; }
        if (is_element(station_ids, start_id) || !no_exit) break;
        cout << "Ошибка! Попробуйте еще\n";
    }

    int stop_id = -2;
    while (no_exit) {
        cout << "Введите ID КС выхода: ";
        stop_id = Enter<int>();

        if (stop_id == -1) { no_exit = false; }
        if ((is_element(station_ids, stop_id) && can_be_paired(start_id, stop_id)) || !no_exit) break;
        cout << "Ошибка! Попробуйте еще\n";
    }

    int diameter = 0;
    while (no_exit) {
        cout << "Диаметр трубы: ";
        diameter = Enter<int>();

        if (diameter == -1) { no_exit = false; }
        if (diameter == 500 || diameter == 700 || diameter == 1000 || diameter == 1400 || !no_exit) break;
        cout << "Некорректный ввод!\n";
    }

    int pipe_id = -2;
    if (no_exit) {
        vector<int> pipe_ids = search_by_diameter(diameter);

        if (pipe_ids.size() == 0) {
            cout << "Нет подходящей трубы. Переходим к созданию\n";
            
            Pipe newPipe;
            newPipe.with_diameter(diameter);

            pipes[pipes_id] = newPipe;
            pipe_id = pipes_id;
            pipes_id++;
        }
        else {
            cout << "\nПодходящие трубы:\n";

            for (const auto& pair : pipes) {
                if (is_element(pipe_ids, pair.first)) {
                    cout << "ID: " << pair.first << endl;
                    cout << pair.second << endl;
                }
            }

            while (true) {
                cout << "Выбор трубы: ";
                pipe_id = Enter<int>();

                if (is_element(pipe_ids, pipe_id)) break;
                cout << "Некорректный ввод!" << endl;
            }
        }

        Connection newConnection(start_id, stop_id, pipe_id);
        connections.push_back(newConnection);
    }

    system("cls");
}

void GasNetwork::EditPipes(vector<int> selectedPipes) {
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
        for (const auto& x : selectedPipes) {
            EraseConnections_byPipe(x);
            pipes.erase(x);
        }
        break;
    case 6:
        break;
    }
}

void GasNetwork::EditStations(vector<int> selectedStations) {
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
        for (const auto& x : selectedStations) {
            EraseConnections_byKs(x);
            stations.erase(x);
        }
        break;
    case 6:
        break;
    }
}

void GasNetwork::SelectionToGroups(vector<int>& elements, vector<int>& selectedPipes, vector<int>& selectedStations) {
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

void GasNetwork::EditSelection(vector<int> elements, bool isPipes) {
    if (isPipes) {
        for (int elem : elements) {
            cout << "ID: " << elem << endl;
            cout << pipes[elem];
            cout << endl;
        }

        EditPipes(elements);
    }
    else {
        for (int elem : elements) {
            cout << "ID: " << elem << endl;
            cout << stations[elem];
            cout << endl;
        }

        EditStations(elements);
    }

    system("cls");
    cout << "Операция выполнена!" << endl;
}

void GasNetwork::ShowAll() {
    system("cls");
    for (const auto& pair : pipes) {
        cout << "ID: " << pair.first << endl;
        cout << pipes[pair.first];
        cout << endl;
    }

    for (const auto& pair : stations) {
        cout << "ID: " << pair.first << endl;
        cout << stations[pair.first];
        cout << endl;
    }

    cout << "Соединения:" << endl;
    for (Connection con : connections) {
        cout << con.start_id << " -> " << con.stop_id << " (труба " << con.pipe_id << ")" << endl;

    }

    cout << "\nРедактировать:\n1. Трубы\n2. КС\n3. Удалить соединение\n0. В меню\nВыбор: ";
    int choice = Enter<int>();

    if (choice == 1 || choice == 2) {
        cout << "Выберите элементы через пробел: ";
        string enter;
        enter = LoggedInput();

        vector<int> elements = Selections(enter);
        if (elements.size() == 0) { return; }
        if (choice == 1) EditSelection(elements, true);
        else EditSelection(elements, false);
    }
    else if (choice == 3) EraseConnection();

    system("cls");
}

void GasNetwork::Search() {
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

    if (elements.size() == 0)
        cout << "Не найдено элементов по заданным параметрам" << endl;
    else if (enter != 1) {
        EditSelection(elements, (enter == 2));
    }
}

void GasNetwork::SaveData() {
    cout << "Введите имя файла: ";
    string fileName = Enter<string>();

    ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (const auto& pair : pipes) {
            outFile << "#PIPE" << endl;
            outFile << pair.first << endl;
            outFile << pipes[pair.first] << endl;
        }

        for (const auto& pair : stations) {
            outFile << "#KS" << endl;
            outFile << pair.first << endl;
            outFile << stations[pair.first] << endl;
        }

        for (Connection con : connections) {
            outFile << "#CONNECTION" << endl;
            outFile << con << endl;
        }

        outFile.close();

        system("cls");
        cout << "Сохранено в data.txt" << endl;
    }

    else
        cout << "Ошибка открытия файла";
}

void GasNetwork::LoadData() {
    cout << "Введите имя файла: ";
    string fileName = Enter<string>();

    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл " << fileName << endl;
        return;
    }
    
    pipes.clear();
    stations.clear();
    connections = {};
    pipes_id = 0;
    stations_id = 0;

    string line;
    while (getline(inFile, line)) {
        if (line == "#PIPE") {
            int id;
            if (!(inFile >> id)) { cout << "Ошибка ID трубы\n"; return; }
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

        else if (line == "#CONNECTION") {
            int start_id;
            int stop_id;
            int pipe_id;

            if (!(inFile >> start_id)) { cout << "Ошибка start_id\n"; return; }
            inFile.ignore();

            if (!(inFile >> stop_id)) { cout << "Ошибка stop_id\n"; return; }
            inFile.ignore();

            if (!(inFile >> pipe_id)) { cout << "Ошибка pipe_id\n"; return; }
            inFile.ignore();

            Connection newConnection(start_id, stop_id, pipe_id);
            connections.push_back(newConnection);
        }
    }

    system("cls");
    cout << "Данные успешно загружены!\n";
}

vector<vector<int>> GasNetwork::TopoSort() {
    vector<vector<int>> topoList = {};

    map<int, int> inCounts;
    for (const auto& pair : stations)
        inCounts[pair.first] = 0;
    
    for (Connection con : connections)
        inCounts[con.stop_id]++;
    
    vector<int> current_level;
    vector<int> to_delete;
    vector<int> to_decrease;
    while (!inCounts.empty()) {
        current_level = {};
        to_delete = {};
        to_decrease = {};
        for (const auto& pair : inCounts) {
            if (pair.second == 0) {
                for (Connection con : connections)
                    if (con.start_id == pair.first)
                        to_decrease.push_back(con.stop_id);

                current_level.push_back(pair.first);
                to_delete.push_back(pair.first);
            }
        }

        for (int x : to_decrease)
            inCounts[x]--;

        for (int x : to_delete)
            inCounts.erase(x);

        if (current_level.empty()) return { {-1} };
        topoList.push_back(current_level);
    }

    return topoList;
}

void GasNetwork::ShowTopo() {
    vector<vector<int>> topoList = TopoSort();

    if (topoList.empty()) cout << "У вас нет КС!";
    else if (topoList[0][0] == -1) cout << "Сортировка невозможна граф имеет цикл!";
    else {
        cout << "Топологическая сортировка графа\n";
        for (vector<int> s : topoList) {
            cout << "[ ";

            for (int elem : s)
                cout << elem << " ";

            cout << "]\n";
        }
    }

}

void GasNetwork::NetMenu() {
    while (true) {
        cout << "Меню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Поиск\n5. Соединить КС\n6. Сохранить\n7. Загрузить\n8. Топологическая сортировка\n0. Выход\nВыбор: ";

        int choice = Enter<int>();
        switch (choice) {
        case 1:
            NewPipe();
            break;
        case 2:
            NewKs();
            break;
        case 3:
            ShowAll();
            break;
        case 4:
            Search();
            break;
        case 5:
            NewConnection();
            break;
        case 6:
            SaveData();
            break;
        case 7:
            LoadData();
            break;
        case 8:
            ShowTopo();
            break;
        case 0:
            exit(0);
        }
    }
}
