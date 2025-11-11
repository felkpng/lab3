#include "Ks.h"
#include <string>
#include <iostream>

#include "temp.h"

Ks::Ks() : name(""), workshops_count(0), workshops_working(0), type("") {}
Ks::Ks(std::string name, int workshops_count, int workshops_working, std::string type) : name(name), workshops_count(workshops_count), workshops_working(workshops_working), type(type) {}

std::ostream& operator<<(std::ostream& os, const Ks& station) {
    bool toConsole = (&os == &std::cout);

    if (toConsole) {
        os << "Информация о станции:\n"
            << "Название: " << station.getName() << '\n'
            << "Количество цехов: " << station.getWorkshopsCount() << " (" << station.getWorkshopsWorking() << " в работе)\n"
            << "Тип: " << station.getType() << "\n";
    }
    else {
        os << station.getName() << '\n'
            << station.getWorkshopsCount() << '\n'
            << station.getWorkshopsWorking() << '\n'
            << station.getType() << '\n';
    }

    return os;
}

std::istream& operator>>(std::istream& is, Ks& station) {
    bool fromConsole = (&is == &std::cin);

    if (fromConsole) {
        std::cout << "\nСоздание компрессорной станции\n";
        std::cout << "Название: ";
        std::string n;
        std::getline(std::cin, n);

        std::cout << "Количество цехов: ";
        int c = Enter<int>();
        while (c < 0) {
            std::cout << "Число должно быть положительным\nПовторите ввод: ";
            c = Enter<int>();
        }

        std::cout << "Количество цехов в работе: ";
        int w = Enter<int>();
        while (w > c || w < 0) {
            std::cout << "Количество не должно превышать общее количество цехов.\nПовторите ввод: ";
            w = Enter<int>();
        }

        std::cout << "Тип: ";
        std::string t = Enter<std::string>();

        station.setName(n);
        station.setWorkshopsCount(c);
        station.setWorkshopsWorking(w);
        station.setType(t);
    }
    else {
        std::string n;
        int c;
        int w;
        std::string t;

        std::getline(is >> std::ws, n);
        is >> c >> w >> t;

        station.setName(n);
        station.setWorkshopsCount(c);
        station.setWorkshopsWorking(w);
        station.setType(t);
    }

    return is;
}
