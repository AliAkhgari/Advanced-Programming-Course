#ifndef __CSV_READER_H__
#define __CSV_READER_H__ "__CSV_READER_H__"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iomanip>

typedef std::vector < std::pair < std::string, std::vector < std::string > > > Lists;
typedef std::vector < std::pair < int, std::vector < std::string > > > Rows;

class CSVReader
{
private:
    std::string file_path;
    Lists columns_of_file;
    Rows rows_of_file;
    int number_of_columns;
    int number_of_rows;

public:
    CSVReader(std::string file_path_);

    int get_number_of_columns () { return number_of_columns; }

    int get_number_of_rows () { return number_of_rows; }

    Lists get_column_information () { return columns_of_file; }

    Rows get_rows_information () { return rows_of_file; }

    std::string file_content();

    std::vector < std::string > first_line();

    void calculate_column_numbers();

    void calculate_row_numbers();

    void ignore_members(std::stringstream &file_data, int x);

    void column_datas();

    void row_datas();
    
};



#endif