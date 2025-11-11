#pragma once
#include <string>

class Ks {
public:
	Ks();
	Ks(std::string name, int workshops_count, int workshops_working, std::string type);

	std::string getName() const { return name; }
	int getWorkshopsCount() const { return workshops_count; }
	int getWorkshopsWorking() const { return workshops_working; }
	std::string getType() const { return type; }

	void setName(std::string n) { name = n; }
	void setWorkshopsCount(int c) { workshops_count = c; }
	void setWorkshopsWorking(int w) { workshops_working = w; }
	void setType(std::string t) { type = t; }
private:
	std::string name;
	int workshops_count;
	int workshops_working;
	std::string type;
};

std::ostream& operator<<(std::ostream& os, const Ks& station);
std::istream& operator>>(std::istream& os, Ks& station);