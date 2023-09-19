#ifndef FOLLOWEDGE_H
#define FOLLOWEDGE_H "FOLLOWEDGE_H"
#include <vector>
#include <string>
#include "Functions.hpp"
typedef std::string Name;
typedef std::string Genre;
typedef std::string Date;
typedef int Id;
typedef std::vector <std::string> Genres;
typedef std::vector <std::string> BooksId;
typedef std::vector <std::string> AuthorsId;


class FollowEdge
{
private:
    Id id;
    std::vector <std::string> following;
public:
    std::vector <FollowEdge> follow_edge_info(std::vector <std::string> data);
    Id get_id() { return id; }
    std::vector <std::string> get_following ();
};

#endif