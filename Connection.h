#pragma once
#include <fstream>
class Connection
{
public:
	int start_id;
	int stop_id;
	int pipe_id;
	Connection(int start_id, int stop_id, int pipe_id);
};

std::ostream& operator<<(std::ostream& os, const Connection& con);
std::istream& operator>>(std::istream& is, Connection& con);
