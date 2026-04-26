#include "Quizapp.H"

void printHeader(string title)
{
    cout << "\n========================================" << endl;
    cout << "   " << title << endl;
    cout << "========================================" << endl;
}

void pause()
{
    cout << "\nPress Enter to continue...";
    cin.get();
}

int main()
{
    System sys;
    int choice;

    while (true)
    {
        printHeader("QUIZ APPLICATION - DEMO MENU");
        cout << "---------- TEACHER ----------" << endl;
        cout << "  1. Register Teacher" << endl;
        cout << "  2. Create Classroom" << endl;
        cout << "  3. Create Quiz (inside class)" << endl;
        cout << "  4. Remove Student from Class" << endl;
        cout << "  5. Display Classroom Info" << endl;
        cout << "  6. Show Leaderboard" << endl;
        cout << "---------- STUDENT ----------" << endl;
        cout << "  7. Register Student" << endl;
        cout << "  8. Join a Class" << endl;
        cout << "  9. Attempt Quiz" << endl;
        cout << " 10. Leave a Class" << endl;
        cout << "-----------------------------" << endl;
        cout << "  0. Exit" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
            // ─── TEACHER FEATURES ───────────────────────────────────────────────

        case 1:
        {
            printHeader("REGISTER TEACHER");
            sys.registerTeacher();
            pause();
            break;
        }

        case 2:
        {
            printHeader("CREATE CLASSROOM");
            sys.createClass();
            pause();
            break;
        }

        case 3:
        {
            printHeader("CREATE QUIZ");
            sys.CreateQuiz();
            pause();
            break;
        }

        case 4:
        {
            printHeader("REMOVE STUDENT (Teacher Action)");
            sys.RemoveStudent();
            pause();
            break;
        }

        case 5:
        {
            printHeader("DISPLAY CLASSROOM INFO");
            sys.DisplayClass();
            pause();
            break;
        }

        case 6:
        {
            printHeader("LEADERBOARD");
            sys.ShowLeaderboard();
            pause();
            break;
        }

            // ─── STUDENT FEATURES ───────────────────────────────────────────────

        case 7:
        {
            printHeader("REGISTER STUDENT");
            sys.registerStudent();
            pause();
            break;
        }

        case 8:
        {
            printHeader("JOIN CLASS");
            sys.JoinClass();
            pause();
            break;
        }

        case 9:
        {
            printHeader("ATTEMPT QUIZ");
            sys.AttemptQuiz();
            pause();
            break;
        }

        case 10:
        {
            printHeader("LEAVE CLASS (Student Action)");
            sys.LeaveClass();
            pause();
            break;
        }

        case 0:
            printHeader("GOODBYE!");
            return 0;

        default:
            cout << "Invalid choice. Try again." << endl;
            pause();
        }
    }

    return 0;
}