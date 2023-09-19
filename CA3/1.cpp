#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector <int> ID;
struct Course
{
    int id;
    string name;
    int units;
    struct schedule
    {
        vector <string> day;
        vector <string> start_time;
        vector <string> end_time;
    }course_schedule;
    ID prerequisites;
};
struct Grade
{
    int id;
    float grade;
};

typedef vector <Course> CourseTable;
typedef vector <Grade> GradeTable;
typedef vector <string> CourseNames;
typedef string FilePath;
typedef string FileContent;

string file_content(FilePath file_name);
CourseTable courses_info(FileContent file_content);
GradeTable grades_info(FileContent file_content);
void put_prerequisites_info_to_struct(string prerequisites, CourseTable &course_table, int course_no);
void put_schedule_info_to_struct(string schedule_info, CourseTable &course_table, int info_number);
void remove_passed_courses(GradeTable grade_table, ID &takable_course);
void remove_courses_with_prerequisity_problem(CourseTable course_table, GradeTable grade_table, ID &takable_course);
CourseNames sorted_course_names(CourseTable course_table, ID takable_course);
void print_tackable_courses(CourseTable course_table, ID takable_course);
bool is_have_prerequisity(int input, GradeTable grade_table);
ID generate_output(CourseTable course_table, GradeTable grade_table);
int string_in_int_type(string input, int last_index);
void remove_item_from_vector(vector <int> &input, int item);
void remove_courses_need_each_other(CourseTable course_table, ID &takable_course);
int find_course_prerequisites(CourseTable course_table, int id);
ID all_courses_id(CourseTable course_table);
void sort_takable_courses(CourseTable course_table, ID &takable_course);
void consider_last_grade(GradeTable &grade_table);

int main(int argc, char *argv[])
{
    FilePath courses_file_path = argv[1];
    FilePath grades_file_path = argv[2];
    FileContent courses = file_content(courses_file_path);
    FileContent grades = file_content(grades_file_path);
    CourseTable course_info = courses_info(courses);
    GradeTable grade_info = grades_info(grades);
    consider_last_grade(grade_info);
    ID takable_courses = generate_output(course_info, grade_info);
}

string file_content(FilePath file_name)
{
    ifstream input_file(file_name);
    input_file.ignore(numeric_limits <streamsize>::max(),'\n');
    stringstream file_content;
    file_content << input_file.rdbuf();
    return file_content.str();
}

int string_in_int_type(string input, int last_index)
{
	if(last_index == 0)
		return input[last_index] - '0';
	int smallAns = string_in_int_type(input,last_index-1);       
	int a = input[last_index] - '0';
	return smallAns * 10 + a;
}

void put_schedule_info_to_struct(string schedule_info, CourseTable &course_table, int course_no)
{
    string input;
    int data_no = 0;
    for(int i = 0; i <= schedule_info.length(); i++)
    {
        if(schedule_info[i] == '-' || schedule_info[i] == '/' || i == schedule_info.length())
        {
            if(data_no == 0)
                course_table[course_no].course_schedule.day.push_back(input);
            else if(data_no == 1)
                course_table[course_no].course_schedule.start_time.push_back(input);
            else if(data_no == 2)
                course_table[course_no].course_schedule.end_time.push_back(input);
            data_no++;
            if(schedule_info[i] == '/')
                data_no = 0;
            input.clear();
        }
        else
        {
            input += schedule_info[i];
        }
    }
}

void put_prerequisites_info_to_struct(string prerequisites, CourseTable &course_table, int course_no)
{
    vector <int> pre;
    string input;
    int data_no = 0;
    for(int i = 0; i <= prerequisites.length(); i++)
    {
        if(prerequisites[i] == '-' || i == prerequisites.length())
        {
            course_table[course_no].prerequisites.push_back(string_in_int_type(input, input.length() - 1));
            input.clear();
        }
        else
        {
            input += prerequisites[i];
        }
    }
}

CourseTable courses_info(FileContent file_content)
{
    CourseTable course_table;
    course_table.push_back(Course());
    stringstream file_data(file_content);
    int course_no = 0, data_no = 0;
    string line, data_between_commas;
    while(getline(file_data, line, '\n'))
    {
        stringstream line_data(line);
        while(getline(line_data, data_between_commas, ','))
        {
            if(data_no  == 0)
                course_table[course_no].id = string_in_int_type(data_between_commas, data_between_commas.length() - 1);
            if(data_no  == 1)
                course_table[course_no].name = data_between_commas;
            if(data_no == 2)
                course_table[course_no].units = string_in_int_type(data_between_commas, data_between_commas.length() - 1);
            if(data_no == 3)
                put_schedule_info_to_struct(data_between_commas, course_table, course_no);
            if(data_no == 4)
            {
                put_prerequisites_info_to_struct(data_between_commas, course_table, course_no);
                course_table.push_back(Course());
                course_no++;
                data_no = -1;
            }
            data_no++;
        }
    }
    course_table.pop_back();
    return course_table;
}

GradeTable grades_info(FileContent file_content)
{
    GradeTable grade_table;
    grade_table.push_back(Grade());
    stringstream file_data(file_content);
    int grade_no = 0, data_no = 0;
    string line, data_between_commas;
    while(getline(file_data, line, '\n'))
    {
        stringstream line_data(line);
        while(getline(line_data, data_between_commas, ','))
        {
            if(data_no == 0)
                grade_table[grade_no].id = string_in_int_type(data_between_commas, data_between_commas.length() - 1);                
            if(data_no == 1)
            {
                grade_table[grade_no].grade = stof(data_between_commas);
                grade_table.push_back(Grade());
                grade_no++;
                data_no = -1;
            }
            data_no++;
        }
    }
    grade_table.pop_back();
    return grade_table;    
}

void remove_passed_courses(GradeTable grade_table, ID &takable_course)
{
    for(int i = 0; i < grade_table.size(); i++)
    {
        if(grade_table[i].grade >= 10)
        {
            takable_course.erase(remove(takable_course.begin(), takable_course.end(), grade_table[i].id), takable_course.end());
        }
    }
}

bool is_have_prerequisity(int course_prerequisity, GradeTable grade_table)
{
    for(int i = 0; i < grade_table.size(); i++)
    {
        if(course_prerequisity == grade_table[i].id)
            return true;
    }
    return false;
}
void consider_last_grade(GradeTable &grade_table)
{
    for(int i = grade_table.size() - 1; i >= 0; i--)
    {
        for(int j = 0; j < grade_table.size(); j++)
        {
            if(grade_table[i].id == grade_table[j].id)
                grade_table[j].grade = grade_table[i].grade;
        }
    }
}

void remove_item_from_vector(vector <int> &input, int item)
{
    input.erase(remove(input.begin(), input.end(), item), input.end());
}

int find_course_prerequisites(CourseTable course_table, int id)
{
    for(int i = 0; i < course_table.size(); i++)
    {
        for(int j = 0; j < course_table[i].prerequisites.size(); j++)
        {
            if(course_table[i].prerequisites[j] == id)
                return i;
        }
    }
    return -1;
}

void remove_courses_need_each_other(CourseTable course_table, ID &takable_course)
{
    for(int t = 0; t < takable_course.size(); t++)
    {
        int course_no = find_course_prerequisites(course_table, takable_course[t]);
        remove_item_from_vector(takable_course, course_table[course_no].id);
    }
}

void remove_courses_with_prerequisity_problem(CourseTable course_table, GradeTable grade_table, ID &takable_course)
{
    for(int i = 0; i < course_table.size(); i++)
    {
        for(int j = grade_table.size() - 1; j >= 0; j--)
        {
            for(int x = 0; x < course_table[i].prerequisites.size(); x++)
            {
                if(course_table[i].prerequisites[x] == grade_table[j].id && grade_table[j].grade < 10)
                    remove_item_from_vector(takable_course, course_table[i].id);
                if(is_have_prerequisity(course_table[i].prerequisites[x], grade_table) == false && course_table[i].prerequisites[x] != 0)
                    remove_item_from_vector(takable_course, course_table[i].id);
            }
        }
    }
    
}

CourseNames sorted_course_names(CourseTable course_table, ID takable_course)
{
    CourseNames takable_courses_name;
    for(int j = 0; j < course_table.size(); j++)
    {
        for(int i = 0; i < takable_course.size(); i++)
        {
            if(takable_course[i] == course_table[j].id)
                takable_courses_name.push_back(course_table[j].name);
        }
    }
    sort(takable_courses_name.begin(), takable_courses_name.end());
    return takable_courses_name;
}

void sort_takable_courses(CourseTable course_table, ID &takable_course)
{
    CourseNames takable_courses_name = sorted_course_names(course_table, takable_course);
    for(int i = 0 ; i < takable_courses_name.size(); i++)
    {
        for(int j = 0; j < course_table.size(); j++)
        {
            if(takable_courses_name[i] == course_table[j].name)
                takable_course[i] = course_table[j].id;
        }
    }
}

void print_tackable_courses(CourseTable course_table, ID takable_course)
{
    for(int i = 0; i < takable_course.size(); i++)
    {
        cout << takable_course[i] << endl;
    }
}

ID all_courses_id(CourseTable course_table)
{
    ID courses_id;
    for(int i = 0; i <course_table.size(); i++)
        courses_id.push_back(course_table[i].id);
    return courses_id;
}

ID generate_output(CourseTable course_table, GradeTable grade_table)
{
    ID takable_courses;
    takable_courses = all_courses_id(course_table);
    remove_passed_courses(grade_table, takable_courses);
    remove_courses_with_prerequisity_problem(course_table, grade_table, takable_courses);
    remove_courses_need_each_other(course_table, takable_courses);
    sort_takable_courses(course_table, takable_courses);
    print_tackable_courses(course_table, takable_courses);
    return takable_courses;
}
