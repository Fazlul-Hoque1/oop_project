// adding comments in every part for a better/clear understanding
// added libraries that is required to code and run this program
#include <iostream> // used for input and output operations
#include <vector> // used for using std::vector
#include <string> // used for std::string class
#include <cassert> // used for testing

// this is our main class ( or known as the parent class )
class Tool
{
public:
    std::string name;
    bool is_borrowed;
    int borrowed_by;
    int borrow_time;

    explicit Tool(std::string name) : name(std::move(name)), is_borrowed(false), borrowed_by(0), borrow_time(0) {}

    virtual ~Tool() = default;

    // used virtual function as we can use that to redefine in a derived class to achieve polymorphism
    virtual void borrow(int id, int hours)
    {
        is_borrowed = true;
        borrowed_by = id;
        borrow_time = hours;
    }

    virtual void return_tool()
    {
        is_borrowed = false;
        borrowed_by = 0;
        borrow_time = 0;
    }
};

// now we will add the child classes , derived class representing the tools
class ConstructionTool : public Tool
{
public:
    // a constructor that sets the name of the construction tool
    explicit ConstructionTool(std::string name) : Tool(std::move(name)) {}

    // override the borrow function to use base implementation
    void borrow(int id, int hours) override
    {
        Tool::borrow(id, hours);
    }

    // override the return_tool function to use base implementation
    void return_tool() override
    {
        Tool::return_tool();
    }
};
class DecorationTool : public Tool
{
public:
    // a constructor that sets the name of the decoration tool
    explicit DecorationTool(std::string name) : Tool(std::move(name)) {}

    // override the borrow function to use base implementation
    void borrow(int id, int hours) override
    {
        Tool::borrow(id, hours);
    }

    // override the return_tool function to use base implementation
    void return_tool() override
    {
        Tool::return_tool();
    }
};
class CleaningTool : public Tool
{
public:
    // a constructor that sets the name of the cleaning tool
    explicit CleaningTool(std::string name) : Tool(std::move(name)) {}

    // override the borrow function to use base implementation
    void borrow(int id, int hours) override
    {
        Tool::borrow(id, hours);
    }

    // override the borrow function to use base implementation
    void return_tool() override
    {
        Tool::return_tool();
    }
};

// this is the worker class
class Worker
{
public:
    std::string name;
    int id;

    Worker(std::string name, int iD) : name(std::move(name)), id(iD) {}
};

void test_borrow_return_summary()
{
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
            new CleaningTool("Pressure Washer")
    };

    // borrow a tool
    workers[0].id; // Bereket Tendai's ID is 121
    tools[0]->borrow(workers[0].id, 5); // Borrow Hammer for 5 hours
    assert(tools[0]->is_borrowed == true);
    assert(tools[0]->borrowed_by == 121);
    assert(tools[0]->borrow_time == 5);

    // try to borrow the same tool again
    bool borrow_attempt = false;
    if (!tools[0]->is_borrowed)
    {
        tools[0]->borrow(workers[1].id, 3); // Galal Jameel tries to borrow Hammer
        borrow_attempt = true;
    }
    assert(borrow_attempt == false);

    // return the tool
    tools[0]->return_tool();
    assert(tools[0]->is_borrowed == false);
    assert(tools[0]->borrowed_by == 0);
    assert(tools[0]->borrow_time == 0);

    // summary of borrowed tools
    tools[1]->borrow(workers[1].id, 4); // Borrow Screwdriver for 4 hours by Galal Jameel
    tools[2]->borrow(workers[2].id, 6); // Borrow Tape Measure for 6 hours by Fizza Zaahira

    std::vector<std::string> summary;
    for (Tool* tool : tools)
    {
        if (tool->is_borrowed)
        {
            summary.push_back(tool->name + " --- Borrowed by " + std::to_string(tool->borrowed_by) + " --- " + std::to_string(tool->borrow_time) + " hour/s || Not Returned");
        }
    }
    assert(summary.size() == 2);
    assert(summary[0] == "Screwdriver --- Borrowed by 122 --- 4 hour/s || Not Returned");
    assert(summary[1] == "Tape Measure --- Borrowed by 123 --- 6 hour/s || Not Returned");

    // clean up dynamically allocated memory
    for (Tool* tool : tools)
    {
        delete tool;
    }
}

int main()
{
    // this will run the test function above
    test_borrow_return_summary();
    std::cout << "All tests passed successfully!\n";

    // a basic "cout" program that adds some design to the program as it starts
    std::cout << "###########################################\n";
    std::cout << "#                                         #\n";
    std::cout << "#    Welcome To Fazlul's Tool Borrowing  #\n";
    std::cout << "#               Program...               #\n";
    std::cout << "#                                         #\n";
    std::cout << "###########################################\n";

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

    while (true)
    {
        // asks the user to enter the iD
        int id;
        std::cout << "Please enter your ID: ";
        std::cin >> id;

        Worker *company_worker = nullptr; // a pointer to store the found worker
        // this will search for the worker with the entered ID
        for (Worker &worker: workers)
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
            continue;
        }

        // after the ID and name has been found this part will greet the user and show them the list of the tools
        std::cout << "Hello, " << company_worker->name << " (" << company_worker->id
                  << "), What would you like to borrow today?\n";

        // displays the tools
        for (int i = 0; i < tools.size(); i++)
        {
            Tool *tool = tools[i];
            if (!tool->is_borrowed)
            {
                std::cout << i + 1 << ". " << tool->name << "\n";
            }
            else
            {
                std::cout << i + 1 << ". " << tool->name << " (borrowed by " << tool->borrowed_by << ")\n";
            }
        }
        // asks the worker to type the number of the tool that they want to borrow
        std::cout << "Enter the number of the tool you want to borrow: ";
        int tool_serial;
        std::cin >> tool_serial;

        // a small check program that checks if the tool has been borrowed already
        if (tools[tool_serial - 1]->is_borrowed)
        {
            std::cout << "This tool is already borrowed. Try again.\n";
            continue;
        }

        // asks the worker for how long they want to borrow the particular tool for
        std::cout << "How long do you want to borrow " << tools[tool_serial - 1]->name << " for? (in hours): ";
        int borrow_time;
        std::cin >> borrow_time;

        // checks if the borrow_time is not more than 24 hours
        while (borrow_time > 24)
        {
            std::cout << "Borrow time cannot be more than 24 hours. Please enter a valid time: ";
            std::cin >> borrow_time;
        }

        // marks the tool as borrowed by the worker
        tools[tool_serial - 1]->borrow(company_worker->id, borrow_time);

        std::cout << company_worker->name << " (" << company_worker->id << ") has borrowed "
                  << tools[tool_serial - 1]->name << " for " << borrow_time << " hour/s.\n";

        while (true)
        {
            // asks the worker what he/she wants to do next
            std::cout << "Do you want to: continue, return, summary, end\n";
            std::string choice;
            std::cin >> choice;

            // from here the following code does the action based on what the user picked from above
            if (choice == "continue")
            {
                break;
            }
            else if (choice == "return")
            {
                std::cout << "Enter your ID: ";
                int return_id;
                std::cin >> return_id;

                bool tool_returned = false;
                for (Tool* tool : tools)
                {
                    if (tool->borrowed_by == return_id)
                    {
                        tool->return_tool();
                        std::cout << "Tool returned successfully.\n";
                        tool_returned = true;
                        break;
                    }
                }
                if (!tool_returned)
                {
                    std::cout << "No tool borrowed by this ID.\n";
                }
            }
            else if (choice == "summary")
            {
                for (Tool* tool : tools)
                {
                    if (tool->is_borrowed)
                    {
                        std::cout << tool->name << " --- Borrowed by " << tool->borrowed_by << " --- " << tool->borrow_time << " hour/s || Not Returned\n";
                    }
                }
            }
            else if (choice == "end")
            {
                return 0;
            }
        }

    }
}