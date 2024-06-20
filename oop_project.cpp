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

int main()
{
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
    std::vector<Tool*> tools =
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

    int id;
    std::cout << "Please enter your ID: ";
    std::cin >> id;

    Worker* company_worker = nullptr; // a pointer to store the found worker
    // this will search for the worker with the entered ID
    for (Worker& worker : workers)
    {
        if (worker.id == id)
        {
            company_worker = &worker;
            break;
        }
    }

    // if the worker is not found, this will ask for the ID again
    if (company_worker == nullptr)
    {
        std::cout << "Invalid ID. Try again.\n";
    }

    // after the ID and name has been found this part will greet the user and show them the list of the tools
    std::cout << "Hello, " << company_worker->name << " (" << company_worker->id << "), TEST COMPLETED\n";
};