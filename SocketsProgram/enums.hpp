#ifndef ENUMS_HPP
#define ENUMS_HPP

enum sockStat {ACK, NACK, QUIT}; // used in mom.cpp
enum jobStat {notStarted, working, complete}; // used in mom.cpp and kid.cpp
enum mood {lazy, prissy, overtired, greedy, cooperative}; // used in kid

#endif