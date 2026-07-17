#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int DAYS = 6;
const int PERIODS = 6;
const int BREAK_PERIOD = 4;   // Period 4 = Break
const int TOTAL_SLOTS = 30;   // 5 teaching periods × 6 days

struct Subject
{
    string subjectName;
    string teacherName;
    int lecturesPerWeek;
    bool isLab;
};

int main()
{
    vector<Subject> subjects;

    int totalSubjects;

    cout << "=========================================\n";
    cout << " SMART TIMETABLE GENERATOR (C++)\n";
    cout << "=========================================\n\n";

    cout << "Enter Number of Subjects : ";
    cin >> totalSubjects;

    int totalLectures = 0;

    for(int i=0;i<totalSubjects;i++)
    {
        Subject temp;

        cout << "\n----------------------------\n";
        cout << "Subject " << i+1 << endl;

        cin.ignore();

        cout << "Subject Name : ";
        getline(cin,temp.subjectName);

        cout << "Teacher Name : ";
        getline(cin,temp.teacherName);

        while(true)
        {
            cout << "Lectures Per Week : ";
            cin >> temp.lecturesPerWeek;

            if(temp.lecturesPerWeek<=0)
            {
                cout<<"Invalid Input!\n";
            }
            else
                break;
        }

        int choice;

        while(true)
        {
            cout<<"\nType\n";
            cout<<"1. Theory\n";
            cout<<"2. Lab\n";

            cout<<"Enter Choice : ";
            cin>>choice;

            if(choice==1)
            {
                temp.isLab=false;
                break;
            }
            else if(choice==2)
            {
                temp.isLab=true;
                break;
            }
            else
            {
                cout<<"Invalid Choice\n";
            }
        }

        totalLectures += temp.lecturesPerWeek;

        subjects.push_back(temp);
    }

    cout<<"\n=========================================\n";

    cout<<"Total Teaching Slots Available : "<<TOTAL_SLOTS<<endl;
    cout<<"Total Lectures Entered         : "<<totalLectures<<endl;

    if(totalLectures > TOTAL_SLOTS)
    {
        cout<<"\nERROR!\n";
        cout<<"You entered more lectures than available slots.\n";
        cout<<"Maximum Allowed = "<<TOTAL_SLOTS<<endl;
        cout<<"Please Restart Program.\n";

        return 0;
    }

    cout<<"\nSubject Summary\n";
    cout<<"-----------------------------------------\n";

    for(int i=0;i<subjects.size();i++)
    {
        cout<<"\nSubject : "<<subjects[i].subjectName<<endl;
        cout<<"Teacher : "<<subjects[i].teacherName<<endl;
        cout<<"Lectures : "<<subjects[i].lecturesPerWeek<<endl;

        if(subjects[i].isLab)
            cout<<"Type : Lab"<<endl;
        else
            cout<<"Type : Theory"<<endl;
    }

    cout<<"\n=========================================\n";
    cout<<"Validation Successful.\n";
    cout<<"Ready For Automatic Timetable Generation.\n";
    cout<<"=========================================\n";

    return 0;
}
