// adding comments in every part for a better/clear understanding
// added libraries that is required to code and run this program
#include <iostream> // used for input and output operations
#include <vector> // used for using std::vector
#include <string> // used for std::string class

// this is our main class ( or known as the parent class )
class Tool
{
public:
    std::string name;
    bool is_borrowed;
    int borrowed_by;
    int borrow_time;

    Tool(std::string name) : name(std::move(name)), is_borrowed(false), borrowed_by(0), borrow_time(0) {}

    void borrow(int id, int hours)
    {
        is_borrowed = true;
        borrowed_by = id;
        borrow_time = hours;
    }

    void return_tool()
    {
        is_borrowed = false;
        borrowed_by = 0;
        borrow_time = 0;
    }
};

// now we will add the child classes
class ConstructionTool : public Tool
{
public:
    ConstructionTool(std::string name) : Tool(std::move(name)) {}
};
class DecorationTool : public Tool
{
public:
    DecorationTool(std::string name) : Tool(std::move(name)) {}
};
class CleaningTool : public Tool
{
public:
    CleaningTool(std::string name) : Tool(std::move(name)) {}
};

// this is the worker class
class Worker
{
public:
    std::string name;
    int id;

    Worker(std::string name, int iD) : name(std::move(name)), id(iD) {}
};

int main() {
    // this contains all the information of the workers that are working in the company ( Name and ID )
    std::vector<Worker> workers =
            {
                    Worker("Bereket Tendai", 121),
                    Worker("Galal Jameel", 122),
                    Worker("Fizza Zaahira", 123),
                    Worker("Ryan Smith", 124),
                    Worker("Jason Mendes", 125),
                    Worker("Ehsan Khan", 126),
                    Worker("Jakub Arian", 127),
                    Worker("Sarah Frazier", 128),
                    Worker("Francis Freeman", 129),
                    Worker("Fazlul Hoque", 130)
            };

    // this bit contains all the class/names of the tools that will be used later in the program
    // the format being used for tools is ( "name_of_the_tool", "tool_description" )
    std::vector<Tool *> tools =
            {
                    new ConstructionTool("Hammer"),
                    new ConstructionTool("Screwdriver"),
                    new ConstructionTool("Tape Measure"),
                    new ConstructionTool("Levels"),
                    new ConstructionTool("Power Drill"),
                    new DecorationTool("Paint Brush"),
                    new DecorationTool("Painter's Tape"),
                    new DecorationTool("Hot Glue Gun"),
                    new DecorationTool("Paint Scrapper"),
                    new DecorationTool("Sand Paper"),
                    new CleaningTool("Broom"),
                    new CleaningTool("Vacuum"),
                    new CleaningTool("Mop"),
                    new CleaningTool("Dustpan"),
                    new CleaningTool("Pressure Washer"),
            };

    while (true) {
        // ask the user to enter the iD
        int id;
        std::cout << "Please enter your ID: ";
        std::cin >> id;

        Worker *company_worker = nullptr; // a pointer to store the found worker
        // this will search for the worker with the entered ID
        for (Worker &worker: workers) {
            if (worker.id == id) {
                company_worker = &worker;
                break;
            }
        }

        // if the worker is not found, this will ask for the ID again
        if (company_worker == nullptr) {
            std::cout << "Invalid ID. Try again.\n";
            continue;
        }

        // after the ID and name has been found this part will greet the user and show them the list of the tools
        std::cout << "Hello, " << company_worker->name << " (" << company_worker->id
                  << "), What would you like to borrow today?\n";

        // displays the tools
        for (int i = 0; i < tools.size(); i++) {
            Tool *tool = tools[i];
            if (!tool->is_borrowed) {
                std::cout << i + 1 << ". " << tool->name << "\n";
            } else {
                std::cout << i + 1 << ". " << tool->name << " (borrowed by " << tool->borrowed_by << ")\n";
            }
        }
        // asks the worker to type the number of the tool that they want to borrow
        std::cout << "Enter the number of the tool you want to borrow: ";
        int tool_serial;
        std::cin >> tool_serial;

        // a small check program that checks if the tool has been borrowed already
        if (tools[tool_serial - 1]->is_borrowed) {
            std::cout << "This tool is already borrowed. Try again.\n";
            continue;
        }

        // asks the worker for how long they want to borrow the particular tool for
        std::cout << "How long do you want to borrow " << tools[tool_serial - 1]->name << " for? (in hours): ";
        int borrow_time;
        std::cin >> borrow_time;

        // checks if the borrow_time is not more than 24 hours
        while (borrow_time > 24) {
            std::cout << "Borrow time cannot be more than 24 hours. Please enter a valid time: ";
            std::cin >> borrow_time;
        }

        // marks the tool as borrowed by the worker
        tools[tool_serial - 1]->borrow(company_worker->id, borrow_time);

        std::cout << company_worker->name << " (" << company_worker->id << ") has borrowed "
                  << tools[tool_serial - 1]->name << " for " << borrow_time << " hour/s.\n";


        while (true) {
            // asks the worker what he/she wants to do next
            std::cout << "Do you want to: continue, return, summary, end\n";
            std::string choice;
            std::cin >> choice;

            // from here the following code does the action based on what the user picked from above
            if (choice == "continue") {
                break;
            } else if (choice == "return") {
                std::cout << "Enter your ID: ";
                int return_id;
                std::cin >> return_id;

                bool tool_returned = false;
                for (Tool *tool: tools) {
                    if (tool->borrowed_by == return_id) {
                        tool->return_tool();
                        std::cout << "Tool returned successfully.\n";
                        tool_returned = true;
                        break;
                    }
                }
                if (!tool_returned) {
                    std::cout << "No tool borrowed by this ID.\n";
                }
            }
            else if (choice == "summary")
            {
                for (Tool *tool: tools) {
                    if (tool->is_borrowed) {
                        std::cout << tool->name << " --- Borrowed by " << tool->borrowed_by << " --- "
                                  << tool->borrow_time << " hour/s || Not Returned\n";
                    }
                }
            }
            else if (choice == "end"){
            }
        }
    }

}