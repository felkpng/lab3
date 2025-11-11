#pragma once
#include <string>
#include <vector>
#include <map>
#include "Pipe.h"
#include "Ks.h"

class GasNetwork
{
private:
	std::string name;
	std::map<int, Pipe> pipes;
	std::map<int, Ks> stations;
	int pipes_id;
	int stations_id;

public:
	GasNetwork();
	GasNetwork(std::string name, std::map<int, Pipe> pipes, std::map<int, Ks> stations, int pipes_id, int stations_id);

	void NewPipe();
	void NewKs();
	void EditPipes(std::vector<int> selectedPipes);
	void EditStations(std::vector<int> selectedStations);
	void EditDifferent(std::vector<int> selectedPipes, std::vector<int> selectedStations);
	void SelectionToGroups(std::vector<int>& elements, std::vector<int>& selectedPipes, std::vector<int>& selectedStations);
	void EditSelection(std::vector<int> elements);
	void ShowAll();
	void Search();
	void SaveData();
	void LoadData();
	void Menu();

};

