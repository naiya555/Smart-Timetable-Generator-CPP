#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<cstdlib>
#include<ctime>

using namespace std;

//======================================================
//               GLOBAL CONSTANTS
//======================================================

const int TOTAL_DAYS = 6;
const int TOTAL_PERIODS = 6;
const int MAX_LABS_PER_DAY = 2;
const int MAX_THEORY_PER_DAY = 2;

//======================================================
//                TEACHER CLASS
//======================================================

class Teacher
{
private:

    string teacherName;
    string teacherCode;

public:

    // Default Constructor

    Teacher()
    {
        teacherName = "";
        teacherCode = "";
    }

    // Parameterized Constructor

    Teacher(string name,string code)
    {
        teacherName = name;
        teacherCode = code;
    }

    // Setters

    void setTeacherName(string name)
    {
        teacherName = name;
    }

    void setTeacherCode(string code)
    {
        teacherCode = code;
    }

    // Getters

    string getTeacherName() const
    {
        return teacherName;
    }

    string getTeacherCode() const
    {
        return teacherCode;
    }

    // Display

    void displayTeacher() const
    {
        cout<<"Teacher Name : "<<teacherName<<endl;
        cout<<"Teacher Code : "<<teacherCode<<endl;
    }
};

//======================================================
//                SUBJECT CLASS
//======================================================

class Subject
{
private:

    int subjectID;

    string subjectName;

    Teacher subjectTeacher;

    int lecturesPerWeek;

    bool isLab;

public:

    // Default Constructor

    Subject()
{
    subjectID = 0;
    subjectName = "";
    lecturesPerWeek = 0;
    isLab = false;
}

    // Parameterized Constructor
Subject(int id,
        string name,
        Teacher teacher,
        int lectures,
        bool lab)
{
    subjectID = id;
    subjectName = name;
    subjectTeacher = teacher;
    lecturesPerWeek = lectures;
    isLab = lab;
}

    // Setters

    void setSubjectName(string name)
    {
        subjectName = name;
    }

    void setTeacher(Teacher teacher)
    {
        subjectTeacher = teacher;
    }

    void setLectureCount(int lecture)
    {
        lecturesPerWeek = lecture;
    }
    void setSubjectID(int id)
{
    subjectID = id;
}

int getSubjectID() const
{
    return subjectID;
}
    void setLabStatus(bool lab)
    {
        isLab = lab;
    }

    // Getters

    string getSubjectName() const
    {
        return subjectName;
    }

    Teacher getTeacher() const
    {
        return subjectTeacher;
    }

    int getLectureCount() const
    {
        return lecturesPerWeek;
    }

    bool getLabStatus() const
    {
        return isLab;
    }

    // Display

    void displaySubject() const
    {
        cout<<"\n--------------------------------------"<<endl;

        cout<<"Subject ID : "<<subjectID<<endl;
cout<<"Subject : "<<subjectName<<endl;

        cout<<"Teacher : "
            <<subjectTeacher.getTeacherName()
            <<" ("
            <<subjectTeacher.getTeacherCode()
            <<")"<<endl;

        cout<<"Lectures / Week : "
            <<lecturesPerWeek<<endl;

        if(isLab)
            cout<<"Type : LAB"<<endl;
        else
            cout<<"Type : THEORY"<<endl;

        cout<<"--------------------------------------"<<endl;
    }
};
//======================================================
//                LECTURE CLASS
//======================================================

class Lecture
{
private:

    Subject lectureSubject;
    bool isAssigned;

public:

    // Default Constructor

    Lecture()
    {
        isAssigned = false;
    }

    // Parameterized Constructor

    Lecture(Subject subject)
    {
        lectureSubject = subject;
        isAssigned = true;
    }

    // Setters

    void setLectureSubject(Subject subject)
    {
        lectureSubject = subject;
        isAssigned = true;
    }
    void assignLecture(Subject subject)
{
    lectureSubject = subject;
    isAssigned = true;
}
    void clearLecture()
    {
        isAssigned = false;
    }

    // Getters

    Subject getLectureSubject() const
    {
        return lectureSubject;
    }

    bool getAssignmentStatus() const
    {
        return isAssigned;
    }

    // Display

    void displayLecture() const
    {
        if(isAssigned)
        {
            cout << lectureSubject.getSubjectName();
        }
        else
        {
            cout << "FREE";
        }
    }
};

//======================================================
//                TIMETABLE CLASS
//======================================================

class Timetable
{
private:

    vector<Subject> subjects;

    Lecture timetable[TOTAL_DAYS][TOTAL_PERIODS];

public:

    // Constructor

    Timetable()
    {
        initializeTimetable();
    }

    //==================================================
    // Initialize Timetable
    //==================================================

    void initializeTimetable()
    {
        for(int day=0; day<TOTAL_DAYS; day++)
        {
            for(int period=0; period<TOTAL_PERIODS; period++)
            {
                timetable[day][period].clearLecture();
            }
        }
    }

    //==================================================
    // Add Subject
    //==================================================

    void addSubject(const Subject &subject)
    {
        subjects.push_back(subject);
    }

    //==================================================
    // Display All Subjects
    //==================================================

    void displaySubjects() const
    {
        if(subjects.empty())
        {
            cout << "\nNo subjects added yet.\n";
            return;
        }

        cout << "\n=========== SUBJECT LIST ===========\n";

        for(size_t i=0; i<subjects.size(); i++)
        {
            cout << "\nSubject " << i+1 << endl;
            subjects[i].displaySubject();
        }
    }

    //==================================================
    // Validate Weekly Lecture Count
    //==================================================

    bool validateLectureCount(int lectures, bool lab)
    {
        if(lab)
        {
            if(lectures < 1 || lectures > 3)
            {
                return false;
            }
        }
        else
        {
            if(lectures < 1 || lectures > 6)
            {
                return false;
            }
        }

        return true;
    }

    //==================================================
    // Total Weekly Lectures
    //==================================================

    int calculateTotalWeeklyLectures() const
    {
        int total = 0;

        for(size_t i=0; i<subjects.size(); i++)
        {
            total += subjects[i].getLectureCount();
        }

        return total;
    }

    //==================================================
    // Check Capacity
    //==================================================

    bool timetableHasCapacity() const
    {
        int maximumCapacity = TOTAL_DAYS * TOTAL_PERIODS;

        if(calculateTotalWeeklyLectures() > maximumCapacity)
        {
            return false;
        }

        return true;
    }

    //==================================================
    // Get Subject List
    //==================================================

  const vector<Subject>& getSubjects() const
{
    return subjects;
}
Lecture& getLecture(int day, int period)
{
    return timetable[day][period];
}
//==================================================
// Check Theory Placement
//==================================================
//==================================================
// Generate Timetable (Greedy Algorithm Foundation)
//==================================================
void generateTimetable()
{
    if(subjects.empty())
    {
        cout << "\nNo subjects available.\n";
        return;
    }

    initializeTimetable();

    vector<int> remainingLectures(subjects.size());

    vector<vector<int>> dailyLectureCount(
        subjects.size(),
        vector<int>(TOTAL_DAYS,0)
    );

    vector<int> labsPerDay(TOTAL_DAYS,0);

    // Store remaining lectures

    for(size_t i=0;i<subjects.size();i++)
    {
        remainingLectures[i]=subjects[i].getLectureCount();
    }

    // Sort subjects
    // Labs first, then Theory

vector<Subject> schedulingQueue = subjects;

sort(
    schedulingQueue.begin(),
    schedulingQueue.end(),
    [](const Subject &a, const Subject &b)
    {
        if(a.getLabStatus() != b.getLabStatus())
            return a.getLabStatus() > b.getLabStatus();

        return a.getLectureCount() > b.getLectureCount();
    }
);

    cout<<"\nGenerating Timetable...\n";

    // Display scheduling queue

    cout<<"\nScheduling Order\n";
    cout<<"-----------------------------\n";

    for(size_t i=0;i<subjects.size();i++)
    {
        cout
        <<schedulingQueue[i].getSubjectName()
        <<" ("
        <<remainingLectures[i]
        <<" Lectures)"
        <<endl;
    }
//==================================================
// Start Greedy Allocation
//==================================================

for(size_t subjectIndex = 0; subjectIndex < schedulingQueue.size(); subjectIndex++)
{
    Subject currentSubject = schedulingQueue[subjectIndex];

    int lecturesToAssign = currentSubject.getLectureCount();

    for(int lecture = 0; lecture < lecturesToAssign; lecture++)
    {
        bool placed = false;

        for(int day = 0; day < TOTAL_DAYS && !placed; day++)
        {
            for(int period = 0; period < TOTAL_PERIODS && !placed; period++)
            {
                if(!timetable[day][period].getAssignmentStatus())
                {
                    timetable[day][period].assignLecture(currentSubject);

                    placed = true;
                }
            }
        }
    }
}

cout << "\nTimetable Generated Successfully!\n";

}
    //==================================================
    // Display Empty Timetable
    //==================================================

    void displayTimetable() const
    {
        cout << "\n=========== WEEKLY TIMETABLE ===========\n\n";

        cout << setw(10) << "Day";

        for(int period=1; period<=TOTAL_PERIODS; period++)
        {
            cout << setw(15) << ("P" + to_string(period));
        }

        cout << endl;

        string days[TOTAL_DAYS] =
        {
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday"
        };

        for(int day=0; day<TOTAL_DAYS; day++)
        {
            cout << setw(10) << days[day];

            for(int period=0; period<TOTAL_PERIODS; period++)
            {
                cout << setw(15);

                timetable[day][period].displayLecture();
            }

            cout << endl;
        }
    }
};
//======================================================
//            FILE HANDLING FUNCTIONS
//======================================================

void saveSubjectsToFile(const Timetable &timetable)
{
    ofstream file("subjects.txt");

    if(!file)
    {
        cout << "\nError creating file!\n";
        return;
    }

   const vector<Subject> &subjects = timetable.getSubjects();
    for(size_t i=0; i<subjects.size(); i++)
    {
        file
            << subjects[i].getSubjectName() << "|"
            << subjects[i].getTeacher().getTeacherName() << "|"
            << subjects[i].getTeacher().getTeacherCode() << "|"
            << subjects[i].getLectureCount() << "|"
            << subjects[i].getLabStatus()
            << endl;
    }

    file.close();

    cout << "\nSubjects saved successfully.\n";
}

//======================================================
//            ADD SUBJECT FUNCTION
//======================================================

void addSubjectMenu(Timetable &timetable)
{
    string subjectName;
    string teacherName;
    string teacherCode;

    int lectures;

    int typeChoice;

    cout << "\nEnter Subject Name : ";
    cin.ignore();
    getline(cin, subjectName);

    cout << "Enter Teacher Name : ";
    getline(cin, teacherName);

    cout << "Enter Teacher Code : ";
    getline(cin, teacherCode);

    do
    {
        cout << "Enter Lectures Per Week : ";
        cin >> lectures;

    }while(lectures <= 0 || lectures > 6);

    do
    {
        cout << "\n1. Theory";
        cout << "\n2. Lab";
        cout << "\nChoice : ";
        cin >> typeChoice;

    }while(typeChoice != 1 && typeChoice != 2);

    bool isLab = (typeChoice == 2);

    if(!timetable.validateLectureCount(lectures,isLab))
    {
        cout << "\nInvalid lecture count.\n";
        return;
    }

    Teacher teacher(
        teacherName,
        teacherCode
    );

   int subjectID = timetable.getSubjects().size() + 1;

Subject subject(
    subjectID,
    subjectName,
    teacher,
    lectures,
    isLab
);

    timetable.addSubject(subject);

    cout << "\nSubject Added Successfully!\n";
}

//======================================================
//                 MAIN FUNCTION
//======================================================

int main()
{
    Timetable timetable;

    int choice;

    do
    {
        cout << "\n========================================";
        cout << "\n SMART TIMETABLE GENERATOR";
        cout << "\n========================================";

        cout << "\n\n1. Add Subject";
        cout << "\n2. View Subjects";
        cout << "\n3. View Empty Timetable";
        cout << "\n4. Save Subjects";
        cout << "\n5. Check Weekly Capacity";
        cout << "\n0. Exit";

        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:

                addSubjectMenu(timetable);

                break;

            case 2:

                timetable.displaySubjects();

                break;

            case 3:

                timetable.displayTimetable();

                break;

            case 4:

                saveSubjectsToFile(timetable);

                break;

            case 5:

                if(timetable.timetableHasCapacity())
                {
                    cout << "\nTimetable capacity is valid.\n";
                }
                else
                {
                    cout << "\nTotal lectures exceed timetable capacity.\n";
                }

                break;

            case 0:

                cout << "\nThank You!\n";

                break;

            default:

                cout << "\nInvalid Choice!\n";
        }

    }while(choice != 0);

    return 0;
}
