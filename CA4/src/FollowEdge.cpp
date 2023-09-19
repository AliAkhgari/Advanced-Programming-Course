#include "FollowEdge.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector <FollowEdge> FollowEdge::follow_edge_info(vector <string> data)
{
    vector <FollowEdge> follow_edges;
    int counter = 0;
    for(int i = 0; i < data.size(); i++)
    {
        if(i % 2 == 0)
        {
            follow_edges.push_back(FollowEdge());
            follow_edges[counter].id = stoi(data[i]);
        }
        if(i % 2 == 1)
        {
            follow_edges[counter].following = file_seperated_data(data[i], '$');
            counter++;
        }
    }
    return follow_edges;
}

vector <string> FollowEdge::get_following () { return following; }