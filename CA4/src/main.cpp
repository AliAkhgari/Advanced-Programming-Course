#include "Goodreads.hpp"
#include "Functions.hpp"
#include <iostream>

#define USERS_FILE_PATH "/users.csv"
#define AUTHORS_FILE_PATH "/authors.csv"
#define BOOKS_FILE_PATH "/books.csv"
#define REVIEWS_FILE_PATH "/reviews.csv"
#define FOLLOW_EDGES_FILE_PATH "/follow_edges.csv"

using namespace std;

int main(int argc, char const *argv[])
{
    string folder = argv[1];
    Goodreads goodreads = push_file_datas(folder + USERS_FILE_PATH, folder + AUTHORS_FILE_PATH,
                                          folder + BOOKS_FILE_PATH, folder + REVIEWS_FILE_PATH,
                                          folder + FOLLOW_EDGES_FILE_PATH);
    string command;
    while (cin >> command)
    {
        get_command(command, goodreads);
    }

    return 0;
}