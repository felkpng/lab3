#pragma once
#include <string>
#include <vector>
#include <map>

#include "Connection.h"
#include "Pipe.h"
#include "Ks.h"

class GasNetwork
{
private:
	std::string name;
	std::map<int, Pipe> pipes;
	std::map<int, Ks> stations;
	std::vector<Connection> connections;
	int pipes_id;
	int stations_id;

	bool can_be_paired(int start_id, int stop_id);
	bool can_be_pipe(int pipe);
	std::vector<int> search_by_diameter(int diameter);
	void EraseConnections_byPipe(int pipe_id);
	void EraseConnections_byKs(int station_id);
	void EraseConnection();
	std::vector<std::vector<int>> TopoSort();
	void ShowTopo();

public:
	GasNetwork();

	void NewPipe();
	void NewKs();
	void NewConnection();
	void EditPipes(std::vector<int> selectedPipes);
	void EditStations(std::vector<int> selectedStations);
	void SelectionToGroups(std::vector<int>& elements, std::vector<int>& selectedPipes, std::vector<int>& selectedStations);
	void EditSelection(std::vector<int> elements, bool isPipes);
	void ShowAll();
	void Search();
	void SaveData();
	void LoadData();

	void NetMenu();

};

