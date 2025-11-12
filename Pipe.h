#pragma once
#include <iostream>
#include <string>

class Pipe {
public:
	Pipe();
	Pipe(std::string name, float length, int diameter, bool repair);
	void with_diameter(int d);

	std::string getName() const { return name; }
	float getLength() const { return length; }
	int getDiameter() const { return diameter; }
	bool isRepair() const { return repair; }

	void setName(std::string n) { name = n; }
	void setLength(float l) { length = l; }
	void setDiameter(int d) { diameter = d; }
	void setRepair(bool r) { repair = r; }
private:
	std::string name;
	float length;
	int diameter;
	bool repair;
};

std::ostream& operator<<(std::ostream& os, const Pipe& truba);
std::istream& operator>>(std::istream& os, Pipe& truba);
