#ifndef Quizapp_H
#define Quizapp_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
class Attempt;
class User
{
protected:
    string name;
    string id;
    int password;

public:
    User(string n = "xxx", int i = 0) : name(n), password(i) {}
    virtual void setuser(string s) = 0;

    virtual ~User() {}
};
class Teacher : public User
{
    static int idn;

public:
    Teacher(string n, int pass) : User(n, pass)
    {
        id = "F" + std::to_string(idn);
        idn++;
    }
    void setuser(string s) override
    {
        name = s;
        id = "F" + std::to_string(idn);
    }
    void displayteach()
    {
        cout << "Name:" << name << endl
             << "Id:" << id << endl;
    }
    friend class System;

    ~Teacher() {}
};
int Teacher::idn = 0;
class Student : public User
{
    static int idnum;
    int result;

public:
    Student(string n, int pass) : User(n, pass)
    {
        id = "S" + std::to_string(idnum);
        idnum++;
        result = 0;
    }
    void setuser(string s) override
    {
        name = s;
        id = "S" + std::to_string(idnum);
    }
    void displaystudents()
    {
        cout << "Name:" << name << endl
             << "Id:" << id << endl;
    }
    friend class Attempt;
    friend class Classroom;
    friend class System;

    ~Student() {}
};
int Student::idnum = 0;
class Question
{
    string q;
    vector<string> options;
    int correctoption;

public:
    bool validateoption(int corr)
    {
        if (corr >= 0 && corr < options.size())
        {
            return true;
        }
        return false;
    }
    Question()
    {
        q = "xxx";
        correctoption = 0;
    }
    Question(string s, vector<string> op, int corr)
    {
        q = s;
        options = op;
        if (validateoption(corr))
        {
            correctoption = corr;
        }
        else
        {
            correctoption = 1;
        }
    }
    void displayquestion()
    {
        cout << "Q." << q << endl;
        for (int i = 0; i < options.size(); i++)
        {
            cout << i + 1 << "." << options[i] << endl;
        }
    }
    bool checkans(int choice)
    {
        return (choice - 1) == correctoption;
    }

    int getoptioncount() { return options.size(); }
    ~Question() {};
};
class Quiz
{
    vector<Question> questions;
    string title;
    int quizid;
    int timelim;

public:
    Quiz(string t = "xxx", int i = -1, int time = 0) : title(t), quizid(i)
    {
        if (time <= 0)
            timelim = 60;
        else
            timelim = time * 60;
    }

    void addquestions()
    {
        string quest;
        vector<string> opts;
        int corr;
        int numopts;

        cin.ignore(1000, '\n');

        cout << "Enter Question: ";
        getline(cin, quest);

        while (true)
        {
            cout << "Enter number of options: ";
            if (cin >> numopts && numopts > 0)
            {
                break;
            }
            else
            {
                cout << "Please enter a valid positive number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }

        cin.ignore(1000, '\n');

        for (int i = 0; i < numopts; i++)
        {
            string t;
            cout << "Enter Option " << i + 1 << ": ";
            getline(cin, t);
            opts.push_back(t);
        }

        while (true)
        {
            cout << "Enter index of the Correct option (1-" << numopts << "): ";
            if (cin >> corr && corr >= 1 && corr <= numopts)
            {
                corr--;
                break;
            }
            else
            {
                cout << "Invalid choice. Must be a number between 1 and " << numopts << "." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }

        questions.emplace_back(quest, opts, corr);
        cout << "Question added successfully!" << endl;
    }
    void displayquiz()
    {
        cout << "==========" << title << "==========" << endl;
        for (int i = 0; i < questions.size(); i++)
        {
            questions[i].displayquestion();
        }
    }
    void displayquizname()
    {
        cout << "Title:" << title << endl
             << "Number Of Questions:" << questions.size() << "            Time limit:" << timelim;
    }
    friend class Attempt;

    ~Quiz() {};
};
class Classroom
{
    string nam;
    Teacher *t;
    vector<Student *> s;
    int pass;
    static int idn;
    string id;
    vector<Quiz> q;

public:
    Classroom(Teacher *teach, int p, string n) : t(teach), pass(p), nam(n)
    {
        id = "C" + std::to_string(idn);
        idn++;
    }
    void displayclass()
    {
        cout << "==========Teacher==========" << endl;
        t->displayteach();
        cout << "==========Students==========" << endl;
        if (s.size() == 0)
            cout << endl
                 << "No Students in class";
        else
        {
            for (int i = 0; i < s.size(); i++)
            {
                s[i]->displaystudents();
            }
        }
        cout << "==========Quizes==========" << endl;
        if (q.size() == 0)
            cout << endl
                 << "No Quizes in class";
        else
        {
            for (int i = 0; i < q.size(); i++)
            {
                q[i].displayquizname();
            }
        }
    }
    void addstudent(Student *S)
    {
        s.push_back(S);
    }
    void createQuiz()
    {
        int t, id, numq;
        string ti;
        cout << endl
             << "Enter Quiz Title:";
        cin >> ti;
        cout << endl
             << "Enter Quiz Time limit:";
        cin >> t;
        cout << endl
             << "Enter Quiz Code:";
        cin >> id;

        cout << endl
             << "Enter Number Of Questions:";
        cin >> numq;
        Quiz temp(ti, id, t);
        for (int i = 0; i < numq; i++)
        {
            temp.addquestions();
        }
        q.push_back(temp);
    }
    void showleaderboard()
    {
        if (s.size() == 0)
        {
            cout << "==========Leaderboard==========" << endl;
            cout << "No students enrolled in this class yet." << endl;
            return;
        }
        vector<Student *> sorted = s;
        for (int i = 0; i < sorted.size() - 1; i++)
        {
            for (int j = 0; j < sorted.size() - i - 1; j++)
            {
                if (sorted[j]->result < sorted[j + 1]->result)
                {
                    Student *temp = sorted[j];
                    sorted[j] = sorted[j + 1];
                    sorted[j + 1] = temp;
                }
            }
        }

        cout << "==========Leaderboard==========" << endl;
        for (int i = 0; i < sorted.size(); i++)
        {
            cout << i + 1 << ". ";
            sorted[i]->displaystudents();
            cout << "Score: " << sorted[i]->result << endl;
        }
    }
    void removeStudent(string studentId)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i]->id == studentId)
            {
                cout << "Student " << s[i]->name << " removed from class." << endl;
                s.erase(s.begin() + i);
                return;
            }
        }
        cout << "Student with ID " << studentId << " not found in this class." << endl;
    }

    bool isStudentEnrolled(string studentId)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i]->id == studentId)
                return true;
        }
        return false;
    }
    friend class System;

    ~Classroom()
    {
        cout << "Classroom " << nam << " destroyed." << endl;
    }
};
int Classroom::idn = 0;
class Attempt
{
    Student *s;
    Quiz *quiz;
    int marks;
    time_t starttime;

public:
    Attempt(Student *stu, Quiz *qu) : s(stu), quiz(qu)
    {
        marks = 0;
        starttime = 0;
    }
    void startattempt()
    {
        starttime = time(0);
        cout << "Time Limit:" << quiz->timelim;
        quiz->displayquiz();
        for (int i = 0; i < quiz->questions.size(); i++)
        {
            if (istimeover())
            {
                cout << "Time UP!" << endl;
                break;
            }
            time_t now = time(0);
            int remaining = quiz->timelim - (int)difftime(now, starttime);
            cout << "&#x23F2 Time Remaining: " << remaining / 60 << "m " << remaining % 60 << "s" << endl;

            int ans;
            while (true)
            {
                cout << "Enter Answer for Question " << i + 1 << ": ";

                if (cin >> ans)
                {
                    if (ans >= 1 && ans <= quiz->questions[i].getoptioncount())
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid choice. Please pick a number between 1 and "
                             << quiz->questions[i].getoptioncount() << "." << endl;
                    }
                }
                else
                {
                    cout << "Invalid input. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                if (istimeover())
                    break;
            }

            if (istimeover())
            {
                cout << "Time UP!" << endl;
                break;
            }
            if (quiz->questions[i].checkans(ans))
                marks++;
        }
        s->result += marks;
        showattempt();
    }
    bool istimeover()
    {
        time_t now = time(0);
        return difftime(now, starttime) >= quiz->timelim;
    }
    void showattempt()
    {
        cout << "Marks Gained:" << marks << endl
             << "Percentage:" << (float(marks) / float(quiz->questions.size())) * 100;
    }

    ~Attempt() {}
};
class System
{
    vector<Teacher *> t;
    vector<Student *> s;
    vector<Classroom *> c;

public:
    void registerTeacher()
    {
        int pass;
        string name;
        cout << "Enter Name:";
        getline(cin, name);
        cout << "Enter Password:";
        cin >> pass;
        Teacher *teach = new Teacher(name, pass);
        cout << endl
             << "Your Id is:" << teach->id << endl;
        t.push_back(teach);
    }
    void registerStudent()
    {
        int pass;
        string name;
        cout << "Enter Name:";
        getline(cin, name);
        cout << "Enter Password:";
        cin >> pass;
        Student *stu = new Student(name, pass);
        cout << endl
             << "Your Id is:" << stu->id << endl;
        s.push_back(stu);
    }

    void createClass()
    {
        string teachId;
        cout << "Enter your Teacher Id:";
        getline(cin, teachId);
        int pass;
        cout << endl
             << "Enter Password:";
        cin >> pass;
        cin.ignore();
        Teacher *tea = findTeacher(teachId);
        if (tea == nullptr)
        {
            cout << "No teacher Found!" << endl;
            return;
        }
        int index = findteach(teachId);
        if (t[index]->password != pass)
        {
            cout << "Wrong Password!" << endl;
            return;
        }

        int classpass;
        string n;
        cout << "Enter Class Name:";
        getline(cin, n);
        cout << endl
             << "Enter Password:";
        cin >> classpass;
        cin.ignore();
        Classroom *cls = new Classroom(tea, classpass, n);
        c.push_back(cls);

        cout << "\n====================================" << endl;
        cout << "Classroom Created Successfully!" << endl;
        cout << "Class Name: " << n << endl;
        cout << "Teacher   : " << tea->name << endl;
        cout << "CLASS ID  : " << cls->id << "  <-- (Share this with your students)" << endl;
        cout << "====================================" << endl;
    }
    Student *finStudent(string Id)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i]->id == Id)
            {
                return s[i];
            }
        }
        return nullptr;
    }
    Teacher *findTeacher(string Id)
    {
        for (int i = 0; i < t.size(); i++)
        {
            if (t[i]->id == Id)
            {
                return t[i];
            }
        }
        return nullptr;
    }
    Classroom *findClass(string Id)
    {
        for (int i = 0; i < c.size(); i++)
        {
            if (c[i]->id == Id)
            {
                return c[i];
            }
        }
        return nullptr;
    }
    int findclass(string id)
    {
        for (int i = 0; i < c.size(); i++)
        {
            if (c[i]->id == id)
            {
                return i;
            }
        }
        return -1;
    }
    int findteach(string id)
    {
        for (int i = 0; i < t.size(); i++)
        {
            if (t[i]->id == id)
            {
                return i;
            }
        }
        return -1;
    }
    int findstudent(string id)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i]->id == id)
            {
                return i;
            }
        }
        return -1;
    }
    void JoinClass()
    {
        string Id;
        cout << "Enter student Id:";
        getline(cin, Id);
        Student *stud = finStudent(Id);
        if (stud == nullptr)
        {
            cout << "No Student Found!" << endl;
            return;
        }
        int pass;
        cout << endl
             << "Enter Student Password:";
        cin >> pass;
        cin.ignore();
        int index = findstudent(Id);
        if (s[index]->password != pass)
        {
            cout << endl
                 << "Incorrect Password!";
            return;
        }
        string idd;
        cout << "Enter Class Id:";
        getline(cin, idd);
        int classIndex = findclass(idd);
        if (classIndex == -1)
        {
            cout << "No class Found";
            return;
        }
        int pas;
        cout << "Enter Class Password:";
        cin >> pas;
        if (c[classIndex]->pass == pas)
        {
            c[classIndex]->addstudent(stud);
            cout << "Joined Class Successfully" << endl;
        }
        else
            cout << "Wrong Password!" << endl;
    }

    void RemoveStudent()
    {
        string teachId;
        cout << "Enter your Teacher Id: ";
        getline(cin, teachId);

        Teacher *tea = findTeacher(teachId);
        if (tea == nullptr)
        {
            cout << "No Teacher Found!" << endl;
            return;
        }

        int pass;
        cout << "Enter Teacher Password: ";
        cin >> pass;
        cin.ignore();
        if (tea->password != pass)
        {
            cout << "Wrong Password!" << endl;
            return;
        }

        string classId;
        cout << "Enter Class Id: ";
        getline(cin, classId);

        int classIndex = findclass(classId);
        if (classIndex == -1)
        {
            cout << "No Class Found!" << endl;
            return;
        }

        if (c[classIndex]->t != tea)
        {
            cout << "You do not own this class!" << endl;
            return;
        }

        string studentId;
        cout << "Enter Student Id to remove: ";
        getline(cin, studentId);

        c[classIndex]->removeStudent(studentId);
    }

    void LeaveClass()
    {
        string studentId;
        cout << "Enter your Student Id: ";
        getline(cin, studentId);

        Student *stud = finStudent(studentId);
        if (stud == nullptr)
        {
            cout << "No Student Found!" << endl;
            return;
        }

        int pass;
        cout << "Enter Student Password: ";
        cin >> pass;
        if (stud->password != pass)
        {
            cout << "Wrong Password!" << endl;
            return;
        }

        string classId;
        cout << "Enter Class Id to leave: ";
        cin.ignore(1000, '\n');
        getline(cin, classId);

        int classIndex = findclass(classId);
        if (classIndex == -1)
        {
            cout << "No Class Found!" << endl;
            return;
        }

        c[classIndex]->removeStudent(studentId);
    }

    void CreateQuiz()
    {
        string teachId;
        cout << "Enter Teacher Id: ";
        getline(cin, teachId);

        Teacher *tea = findTeacher(teachId);
        if (tea == nullptr)
        {
            cout << "No Teacher Found!" << endl;
            return;
        }

        int pass;
        cout << "Enter Teacher Password: ";
        cin >> pass;
        cin.ignore(1000, '\n');
        if (tea->password != pass)
        {
            cout << "Wrong Password!" << endl;
            return;
        }

        string classId;
        cout << "Enter Class Id: ";
        getline(cin, classId);

        int classIndex = findclass(classId);
        if (classIndex == -1)
        {
            cout << "No Class Found!" << endl;
            return;
        }

        if (c[classIndex]->t != tea)
        {
            cout << "You do not own this class!" << endl;
            return;
        }

        c[classIndex]->createQuiz();
    }

    void DisplayClass()
    {
        string classId;
        cout << "Enter Class Id: ";
        getline(cin, classId);

        int classIndex = findclass(classId);
        if (classIndex == -1)
        {
            cout << "No Class Found!" << endl;
            return;
        }
        c[classIndex]->displayclass();
    }

    void ShowLeaderboard()
    {
        string classId;
        cout << "Enter Class Id: ";
        getline(cin, classId);

        int classIndex = findclass(classId);
        if (classIndex == -1)
        {
            cout << "No Class Found!" << endl;
            return;
        }
        c[classIndex]->showleaderboard();
    }
    void AttemptQuiz()
    {
        string studentId;
        cout << "Enter Student Id: ";
        getline(cin, studentId);

        Student *stud = finStudent(studentId);
        if (stud == nullptr)
        {
            cout << "No Student Found!" << endl;
            return;
        }

        int pass;
        cout << "Enter Student Password: ";
        cin >> pass;
        cin.ignore(1000, '\n');
        if (stud->password != pass)
        {
            cout << "Wrong Password!" << endl;
            return;
        }

        string classId;
        cout << "Enter Class Id: ";
        getline(cin, classId);

        int classIndex = findclass(classId);
        if (classIndex == -1)
        {
            cout << "No Class Found!" << endl;
            return;
        }

        if (!c[classIndex]->isStudentEnrolled(studentId))
        {
            cout << "Access Denied! You are not enrolled in this class." << endl;
            cout << "Please join the class first using option 8." << endl;
            return;
        }

        cout << "Available Quizzes:" << endl;
        for (int i = 0; i < c[classIndex]->q.size(); i++)
        {
            cout << i + 1 << ". ";
            c[classIndex]->q[i].displayquizname();
            cout << endl;
        }

        if (c[classIndex]->q.size() == 0)
        {
            cout << "No quizzes available in this class!" << endl;
            return;
        }

        int qIndex;
        cout << "Select Quiz Number: ";
        cin >> qIndex;
        cin.ignore(1000, '\n');
        qIndex--;

        if (qIndex < 0 || qIndex >= c[classIndex]->q.size())
        {
            cout << "Invalid quiz selection!" << endl;
            return;
        }

        Attempt attempt(stud, &c[classIndex]->q[qIndex]);
        attempt.startattempt();
    }

    ~System()
    {
        for (int i = 0; i < c.size(); i++)
            delete c[i];
        c.clear();

        for (int i = 0; i < t.size(); i++)
            delete t[i];
        t.clear();

        for (int i = 0; i < s.size(); i++)
            delete s[i];
        s.clear();

        cout << "System shut down. All memory freed." << endl;
    }
};
#endif
