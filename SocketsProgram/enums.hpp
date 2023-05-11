#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>

enum sockStat {ACK, NACK, QUIT}; // used in mom.cpp
static string sockString[] = {"ACK", "NACK", "QUIT"};

enum jobStat {notStarted, working, complete}; // used in mom.cpp and kid.cpp
enum mood {lazy, prissy, overtired, greedy, cooperative}; // used in kid

#endif