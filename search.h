#pragma once
#include <string>
#include <vector>
#include <map>

#include "Pipe.h"
#include "Ks.h"
#include "temp.h"

using namespace std;

vector<int> SearchByName(map<int, Pipe>& pipes, map<int, Ks>& stations) {
	string enter;
	cout << "Поиск по имени: ";
	getline(cin, enter);

	vector<int> elements = {};
	for (const auto& pair : pipes) {
		string name = pair.second.getName();
		if (name.find(enter) != string::npos)
			elements.push_back(pair.first);
	}

	for (const auto& pair : stations) {
		string name = pair.second.getName();
		if (name.find(enter) != string::npos)
			elements.push_back(pair.first);
	}

	return elements;
}

vector<int> SearchByRepair(map<int, Pipe>& pipes) {
	cout << "Поиск по состоянию(0/1): ";
	bool enter = Enter<bool>();

	vector<int> elements = {};
	for (const auto& pair : pipes) {
		bool repair = pair.second.isRepair();
		if (repair == enter)
			elements.push_back(pair.first);
	}
	return elements;
}

vector<int> SearchByWorkshops(map<int, Ks>& stations) {
	cout << "Поиск по проценту незадействованных цехов: ";
	float enter = Enter<float>();

	vector<int> elements = {};
	for (const auto& pair : stations) {
		float workshops_count = (float)pair.second.getWorkshopsCount();
		float workshops_working = (float)pair.second.getWorkshopsWorking();
		float rate = (workshops_count - workshops_working) / workshops_count;
		if (rate == enter)
			elements.push_back(pair.first);
	}
	return elements;
}
