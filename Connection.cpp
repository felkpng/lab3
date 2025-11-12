#include "Connection.h"
Connection::Connection(int start_id, int stop_id, int pipe_id) : start_id(start_id), stop_id(stop_id), pipe_id(pipe_id) {}

std::ostream& operator<<(std::ostream& os, const Connection& con) {
    os << con.start_id << '\n'
        << con.stop_id << '\n'
        << con.pipe_id << '\n';

    return os;
}

std::istream& operator>>(std::istream& is, Connection& con) {
    int a;
    int b;
    int c;

    is >> a >> b >> c;

    con.start_id = a;
    con.stop_id = b;
    con.pipe_id = c;

    return is;
}
