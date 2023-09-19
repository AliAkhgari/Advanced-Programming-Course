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
void remove_passed_courses(CourseTable course_table, GradeTable grade_table, ID &takable_course);
void remove_courses_with_prerequisity_problem(CourseTable course_table, GradeTable grade_table, ID &takable_course);
void sort_course_names(CourseTable course_table, ID &takable_course);
bool is_have_prerequisity(int input, GradeTable grade_table);
ID all_courses_id(CourseTable course_table);
ID generate_output(CourseTable course_table, GradeTable grade_table);
int string_in_int_type(string input, int last_index);
void remove_item_from_vector(vector <int> &input, int item);
void remove_courses_need_each_other(CourseTable course_table, ID &takable_course);
int find_course_prerequisites(CourseTable course_table, int id);
bool is_between(float time, float start_time, float end_time);
void swap(int &a, int &b);
float average(GradeTable grade_table, CourseTable course_table);
void sort_takable_courses(CourseTable course_table, ID &takable_courses);
void sort_takable_courses_by_units(CourseTable course_table, ID &takable_courses);
ID choose_courses(CourseTable course_table, GradeTable grade_table, ID takable_courses, float average, int counter);
bool has_overlap(CourseTable course_table, int first_id, int second_id);
float time_format(string time);
int find_course_by_id(CourseTable course_table, int id);
void consider_last_grade(GradeTable &grade_table);

void print_in_file(ID chosen_courses, int counter);
bool is_failed(GradeTable grade_table, int id);
void find_courses_program(CourseTable &course_table, GradeTable &grade_table, float term_average, int countder);

int main(int argc, char *argv[])
{
    FilePath courses_file_path = argv[1];
    FilePath grades_file_path = argv[2];
    FileContent courses = file_content(courses_file_path);
    FileContent grades = file_content(grades_file_path);
    CourseTable course_info = courses_info(courses);
    GradeTable grade_info = grades_info(grades);
    float term_average = average(grade_info, course_info);
    find_courses_program(course_info, grade_info, term_average, 1);
}

int string_in_int_type(string input, int last_index)
{
	if(last_index == 0)
		return input[last_index] - '0';
	int smallAns = string_in_int_type(input,last_index-1);       
	int a = input[last_index] - '0';
	return smallAns * 10 + a;
}

void print_vector(vector <int> input)
{
    for(int i = 0; i < input.size(); i++)
    {
        cout << input[i] << '\n';
    }
}
string file_content(string file_name)
{
    ifstream input_file(file_name);
    input_file.ignore(numeric_limits <streamsize>::max(),'\n');
    stringstream file_content;
    file_content << input_file.rdbuf();
    return file_content.str();
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
    consider_last_grade(grade_table);
    return grade_table;    
}
void remove_passed_courses(CourseTable course_table, GradeTable grade_table, ID &takable_course)
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

void sort_course_names(CourseTable course_table, ID &takable_course)
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
    for(int i = 0 ; i < takable_courses_name.size(); i++)
    {
        for(int j = 0; j < course_table.size(); j++)
        {
            if(takable_courses_name[i] == course_table[j].name)
                takable_course[i] = course_table[j].id;
        }
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
    remove_passed_courses(course_table, grade_table, takable_courses);
    remove_courses_with_prerequisity_problem(course_table, grade_table, takable_courses);
    remove_courses_need_each_other(course_table, takable_courses);
    sort_course_names(course_table, takable_courses);
    return takable_courses;
}

float average(GradeTable grade_table, CourseTable course_table)
{
    float average;
    float grades_sum = 0;
    int units_sum = 0;
    for(int i = 0; i < grade_table.size(); i++)
    {
        for(int j = 0; j < course_table.size(); j++)
        {
            if(grade_table[i].id == course_table[j].id)
            {
                units_sum += course_table[j].units;
                grades_sum += grade_table[i].grade * course_table[j].units;
            }
        }
    }
    average = grades_sum/units_sum;
    return average;
}
int find_course_by_id(CourseTable course_table, int id)
{
    for(int i = 0; i < course_table.size(); i++)
    {
        if(course_table[i].id == id)
            return i;
    }
    return -1;
}
void swap(int &a, int &b)
{
    int tmp;
    tmp = b;
    b = a;
    a = tmp;
}
void sort_takable_courses_by_units(CourseTable course_table, ID &takable_courses)
{
    sort_course_names(course_table, takable_courses);
    for(int  i = 0; i < takable_courses.size(); i++)
    {
        for(int j = i+1; j < takable_courses.size(); j++)
        {
            if(course_table[find_course_by_id(course_table, takable_courses[i])].units < course_table[find_course_by_id(course_table, takable_courses[j])].units)
            {
                swap(takable_courses[i], takable_courses[j]);
            }
        }
    }
}
void sort_takable_courses(CourseTable course_table, ID &takable_courses)
{
    sort_takable_courses_by_units(course_table, takable_courses);
    vector <int> takable_courses_with_same_units;
    vector <int> tmp;
    for(int  i = 0; i < takable_courses.size(); i++)
    {
        for(int j = i; j < takable_courses.size(); j++)
        {
            if(course_table[find_course_by_id(course_table, takable_courses[i])].units == course_table[find_course_by_id(course_table, takable_courses[j])].units)
            {
                takable_courses_with_same_units.push_back(takable_courses[j]);
                if(j == takable_courses.size() - 1)
                {
                    i = j;
                    break;
                }
            }
            else
            {
                i = j - 1;
                break;
            }
        }
        sort_course_names(course_table, takable_courses_with_same_units);
        for(int i = 0; i < takable_courses_with_same_units.size(); i++)
        {
            tmp.push_back(takable_courses_with_same_units[i]);
        }
        takable_courses_with_same_units.clear();
    }
    for(int i = 0; i < takable_courses.size(); i++)
    {
        takable_courses[i] = tmp[i];
    }
}

float time_format(string time)
{
    string input;
    vector <float> number;
    for(int i = 0; i <= time.length(); i++)
    {
        if(time[i] == ':' || i == time.length())
        {
            number.push_back(stof(input));
            input.clear();
        }
        else
        {
            input += time[i];
        }
    }
    return number[0] + number[1]/60;
}
bool is_between(float time, float start_time, float end_time)
{
    if(time > start_time && time < end_time)
        return true;
    return false;
}
bool has_overlap(CourseTable course_table, int first_id, int second_id)
{
    for(int i = 0; i < course_table[first_id].course_schedule.day.size(); i++)
    {
        for(int j = 0; j < course_table[second_id].course_schedule.day.size(); j++)
        {
            if(course_table[first_id].course_schedule.day[i] == course_table[second_id].course_schedule.day[j])
            {
                float first_course_start_time =  time_format(course_table[first_id].course_schedule.start_time[i]);
                float second_course_start_time = time_format(course_table[second_id].course_schedule.start_time[j]);
                float first_course_end_time =  time_format(course_table[first_id].course_schedule.end_time[i]);
                float second_course_end_time =  time_format(course_table[second_id].course_schedule.end_time[j]);
                if(is_between(second_course_start_time, first_course_start_time, first_course_end_time))
                    return true;
                if(is_between(first_course_start_time, second_course_start_time, second_course_end_time))
                    return true;
                if(first_course_start_time == second_course_start_time && first_course_end_time == second_course_end_time)
                    return true;
            }
        }
    }
    return false;
}

void print_in_file(ID chosen_courses, int counter)
{
    ofstream output_file;
    FilePath file_name;
    file_name = "semester";
    file_name += to_string(counter);
    file_name += ".sched";
    output_file.open(file_name);
    for(int i = 0; i < chosen_courses.size(); i++)
        output_file << chosen_courses[i] << endl;
}
ID choose_courses(CourseTable course_table, GradeTable grade_table, ID takable_courses, float average, int counter)
{
    int taken_units = 0;
    ID taken_courses;
    taken_courses.push_back(takable_courses[0]);
    taken_units += course_table[takable_courses[0]].units;
    vector <int> previous_class;
    previous_class.push_back(takable_courses[0]);
    int max_units;
    
    if(average >= 17)
        max_units = 24;
    else
        max_units = 20;
    for(int i = 1; i < takable_courses.size(); i++)
    {
        for(int j = 0; j < previous_class.size(); j++)
        {
            if(has_overlap(course_table, find_course_by_id(course_table, takable_courses[i]) , find_course_by_id(course_table, previous_class[j])) == false)
            {
                if(j == previous_class.size() - 1  && taken_units + course_table[find_course_by_id(course_table, takable_courses[i])].units <= max_units)
                {
                    previous_class.push_back(takable_courses[i]);
                    taken_courses.push_back(takable_courses[i]);
                    taken_units += course_table[find_course_by_id(course_table, takable_courses[i])].units;
                    break;
                }
            }
            else
                break;
        }
    }
    sort_course_names(course_table, taken_courses);
    print_in_file(taken_courses, counter);
    return taken_courses;
}
bool is_failed(GradeTable grade_table, int id)
{
    for(int i = 0; i < grade_table.size(); i++)
    {
        if(grade_table[i].id == id && grade_table[i].grade < 10)
            return true;
    }
    return false;
}
void find_courses_program(CourseTable &course_table, GradeTable &grade_table, float term_average, int counter)
{
    vector <int> all_courses_id;
    vector <int> all_grades_id;
    for(int i = 0; i < course_table.size(); i++)
    {
        all_courses_id.push_back(course_table[i].id);
    }
    for(int i = 0; i < grade_table.size(); i++)
    {
        all_grades_id.push_back(grade_table[i].id);
    }
    ID takable_courses = generate_output(course_table, grade_table);
    sort_takable_courses(course_table, takable_courses);
    ID takan_courses = choose_courses(course_table, grade_table, takable_courses, term_average, counter);
    for(int i = 0; i < course_table.size(); i++)
    {
        for(int j = 0; j < grade_table.size(); j++)
        {
            if(course_table[i].id == grade_table[j].id && grade_table[j].grade >= 10)
            {
                all_courses_id.erase(remove(all_courses_id.begin(), all_courses_id.end(), course_table[i].id), all_courses_id.end());
            }
        }
    }
    for(int i = 0; i < course_table.size(); i++)
    {
        for(int j = 0; j < takan_courses.size(); j++)
        {
            if(course_table[i].id == takan_courses[j] && is_failed(grade_table, course_table[i].id) == false)
            {
                grade_table.push_back(Grade());
                int size = grade_table.size();
                grade_table[size - 1].id = takan_courses[j];
                grade_table[size - 1].grade = 10;
                all_courses_id.erase(remove(all_courses_id.begin(), all_courses_id.end(), course_table[i].id), all_courses_id.end());
            }
            else
            {
                for(int i = 0; i < grade_table.size(); i++)
                {
                    if(grade_table[i].id == takan_courses[j])
                        grade_table[i].grade = 10;
                }
            }
        }
    }
    if(all_courses_id.size() == 0)
    {
        return;
    }
    term_average = (term_average + 1.05 * term_average)/2;
    find_courses_program(course_table, grade_table, term_average, counter + 1);
}