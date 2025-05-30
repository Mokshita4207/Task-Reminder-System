#include <iostream>
#include <thread> //for pausing program
#include <chrono> //for handling durations
#include <vector> //for storing list of tasks
#include <string>

using namespace std;
using namespace chrono;

// Base class using Inheritance
class ITask {
protected:
    string name;
    int duration;

public:
    ITask(const string& taskName, int taskDuration)
        : name(taskName), duration(taskDuration) {} //parameterized constructor

    // Virtual function for Polymorphism
    virtual void remind() const {
        cout << "Task: " << name << " (Base Task)\n";
    }

    virtual ~ITask() {}
};

// Derived class overrides remind()
class Task : public ITask {
public:
    Task(const string& taskName, int taskDuration)
        : ITask(taskName, taskDuration) {}

    void remind() const override {
        cout << "\nStarting task: " << name << " (Duration: " << duration << " sec)" << endl;

        if (duration > 10) {
            this_thread::sleep_for(seconds(duration - 10));
            cout << "Reminder: Only 10 seconds left for task: " << name << endl;
            this_thread::sleep_for(seconds(10));
        } else {
            this_thread::sleep_for(seconds(duration));
        }

        cout << "Task finished: " << name << endl;
    }
};

// Manages list of tasks
class WorkList {
private:
    vector<Task> tasks; // STL vector to store tasks

public:
    void inputTasks() {
        int n;
        cout << "Enter number of tasks: ";
        cin >> n;

        // Error handling for negative or zero task count
        while (cin.fail() || n <= 0) {
            cin.clear(); // Clear the error flag
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Invalid number! Please enter a positive number of tasks: ";
            cin >> n;
        }

        cin.ignore(); // Clear input buffer

        for (int i = 0; i < n; ++i) {
            string name;
            int duration;

            cout << "\nEnter name of task " << i + 1 << ": ";
            getline(cin, name);

            cout << "Enter duration (in seconds): ";
            cin >> duration;

            // Clear input if user types letters instead of numbers
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a number: ";
                cin >> duration;
            }

            cin.ignore();

            try {
                if (duration <= 0) {
                    throw "Duration must be greater than 0.";
                }

                tasks.emplace_back(name, duration);
            }
            catch (const char* e) {
                cout << "Error: " << e << " Skipping this task.\n";
            }
        }
    }

    void startTasks() const {
        cout << "\n--- Starting your Work List ---\n";
        for (const Task& task : tasks) {
            task.remind();
        }
    }
    ~ WorkList(){ //distructor
    cout<<endl<<"All tasks completed!!"<<endl;
    }
};

// Main function
int main() {
    WorkList myWorkList;

    try {
        myWorkList.inputTasks();
        myWorkList.startTasks();
    }
    catch (const char* e) {
        cout << "Unexpected error: " << e << endl;
    }

    return 0;
}
