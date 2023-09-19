#include "CSVReader.hpp"

using namespace std;

CSVReader::CSVReader(string file_path_)
{
    file_path = file_path_;
    calculate_column_numbers();
    calculate_row_numbers();
    column_datas();
    row_datas();
}

string CSVReader::file_content()
{
    ifstream input_file(file_path);
    stringstream file_ss;
    file_ss << input_file.rdbuf();
    return file_ss.str();
}

vector <string> CSVReader::first_line()
{
    vector <string> topics;
    stringstream file_data(file_content());
    string first_line;
    string cell;
    while(getline(file_data, first_line, '\n'))
    {
        stringstream line_data(first_line);
        while(getline(line_data, cell, ','))
            topics.push_back(cell);

        break;
    }
    return topics;
}

void CSVReader::calculate_row_numbers()
{
    stringstream file_data(file_content());
    string line;
    int row_numbers = 0;
    while(getline(file_data, line, '\n'))
        row_numbers++;

    number_of_rows = row_numbers;
}

void CSVReader::calculate_column_numbers()
{
    stringstream file_data(file_content());
    string line, line_member;
    int column_numbers = 0;
    while(getline(file_data, line, '\n'))
    {
        stringstream line_data(line);
        while(getline(line_data, line_member, ','))
            column_numbers++;

        break;
    }
    number_of_columns = column_numbers;
}

void CSVReader::ignore_members(stringstream &file_data, int x)
{
    for(int i = 0; i < x; i++)
        file_data.ignore(numeric_limits <streamsize>::max(),',');
}

void CSVReader::column_datas()
{
    vector <string> topics;
    string line, line_member;
    for(int i = 0; i < number_of_columns; i++)
    {
        stringstream file_data(file_content());
        file_data.ignore(numeric_limits <streamsize>::max(),'\n');
        while(getline(file_data, line, '\n'))
        {
            stringstream line_data(line);
            ignore_members(line_data, i);
            while(getline(line_data, line_member, ','))
            {
                topics.push_back(line_member);
                break;
            }
        }
        columns_of_file.push_back(make_pair(first_line()[i], topics));
        topics.clear();
    }
}

void CSVReader::row_datas()
{
    vector <string> topics;
    string line, line_member;
    for(int i = 0; i < number_of_rows; i++)
    {
        stringstream file_data(file_content());
        for(int j = 0; j < i + 1; j++)
            file_data.ignore(numeric_limits <streamsize>::max(),'\n');

        while(getline(file_data, line, '\n'))
        {
            stringstream line_data(line);
            while(getline(line_data, line_member, ','))
            {
                topics.push_back(line_member);
            }
        }
        rows_of_file.push_back(make_pair(i + 1, topics));
        topics.clear();
    }
}