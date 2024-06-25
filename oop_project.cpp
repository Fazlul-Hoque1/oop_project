#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// abstract base class for tools
class Tool
{
public:
    std::string name;
    bool is_borrowed;
    int borrowed_by;
    int borrow_time;

    explicit Tool(std::string name) : name(std::move(name)), is_borrowed(false), borrowed_by(0), borrow_time(0) {}

    virtual ~Tool() = default;

    //virtual function to check the availability of the tool
    virtual void check_availability() const = 0;

    // borrows the tool for a some (x) hours
    void borrow(int id, int hours)
    {
        is_borrowed = true;
        borrowed_by = id;
        borrow_time = hours;
    }

    // returns the tool
    void return_tool()
    {
        is_borrowed = false;
        borrowed_by = 0;
        borrow_time = 0;
    }
};

// these can be called child classes
class ConstructionTool : public Tool
{
public:
    // a constructor
    ConstructionTool(std::string name) : Tool(std::move(name)) {}

    void check_availability() const override
    {
        if (is_borrowed)
        {
            std::cout << name << " is borrowed by " << borrowed_by << ".\n";
        }
        else
        {
            std::cout << name << " is available to be borrowed.\n";
        }
    }
};

class DecorationTool : public Tool
{
public:
    bool special_handling = false;

    // constructor
    DecorationTool(std::string name, bool special_handling = false) : Tool(std::move(name)), special_handling(special_handling) {}

    void check_availability() const override
    {
        if (is_borrowed)
        {
            std::cout << name << " is borrowed by " << borrowed_by << ".\n";
            if (special_handling)
            {
                std::cout << name << " requires special handling.\n";
            }
        }
        else
        {
            if (special_handling)
            {
                std::cout << name << " is available to be borrowed and requires special handling.\n";
            }
            else
            {
                std::cout << name << " is available to be borrowed.\n";
            }
        }
    }
};

class Worker
{
public:
    std::string name;
    int id;

    Worker(std::string name, int iD) : name(std::move(name)), id(iD) {}
};

void test_tool_availability()
{
    ConstructionTool hammer("Hammer");
    assert(!hammer.is_borrowed);
    hammer.borrow(1, 2);
    assert(hammer.is_borrowed);
    hammer.return_tool();
    assert(!hammer.is_borrowed);

    DecorationTool paintBrush("Paint Brush", true);
    assert(!paintBrush.is_borrowed);
    paintBrush.borrow(2, 3);
    assert(paintBrush.is_borrowed);
    paintBrush.return_tool();
    assert(!paintBrush.is_borrowed);
}

void test_borrow_tool()
{
    ConstructionTool screwdriver("Screwdriver");
    screwdriver.borrow(1, 4);
    assert(screwdriver.is_borrowed);
    assert(screwdriver.borrowed_by == 1);
    assert(screwdriver.borrow_time == 4);
}

void test_return_tool()
{
    DecorationTool glueGun("Hot Glue Gun", true);
    glueGun.borrow(2, 5);
    assert(glueGun.is_borrowed);
    glueGun.return_tool();
    assert(!glueGun.is_borrowed);
    assert(glueGun.borrowed_by == 0);
    assert(glueGun.borrow_time == 0);
}

int main()
{
    // running the tests
    test_tool_availability();
    test_borrow_tool();
    test_return_tool();
    std::cout << "All tests passed!\n";

    std::cout << "###########################################\n";
    std::cout << "#                                         #\n";
    std::cout << "#    Welcome To Fazlul's Tool Borrowing  #\n";
    std::cout << "#               Program...               #\n";
    std::cout << "#                                         #\n";
    std::cout << "###########################################\n";

    // this bit contains all the class/names of the tools that will be used later in the program
    // the format being used for tools is ( "name_of_the_tool", "tool_description" )
    // in decoration tools I have added ', true' so that it lets the user know that this tool requires special handling
    std::vector<Tool*> tools =
            {
                    new ConstructionTool("Hammer"),
                    new ConstructionTool("Screwdriver"),
                    new ConstructionTool("Tape Measure"),
                    new ConstructionTool("Levels"),
                    new ConstructionTool("Power Drill"),
                    new DecorationTool("Paint Brush"),
                    new DecorationTool("Painter's Tape"),
                    new DecorationTool("Hot Glue Gun", true),
                    new DecorationTool("Paint Scrapper", true),
                    new DecorationTool("Sand Paper"),
            };

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



        while (true)
        {
            std::cout << "Do you want to check_availability, borrow, return, summary or end? ";
            // this will work based on what the user choice is
            std::string choice;
            std::cin >> choice;

            // this will check if the item is available to be borrowed
            if (choice == "check_availability")
            {
                std::cout << "Here is the availability of tools:\n";
                for (Tool* tool : tools)
                {
                    tool->check_availability();
                }
            }

                // this will show a list of tools that the user can borrow + will let the user pick a tool to borrow
            else if (choice == "borrow")
            {
                std::cout << "Enter your ID: ";
                int borrow_id;
                std::cin >> borrow_id;

                Worker* company_worker = nullptr; // a pointer to store the found worker
                // this will search for the worker with the entered ID
                for (Worker& worker : workers)
                {
                    if (worker.id == borrow_id)
                    {
                        company_worker = &worker;
                        break;
                    }
                }

                if (company_worker == nullptr)
                {
                    std::cout << "Invalid ID. Try again.\n";
                    continue;
                }

                std::cout << "Hello, " << company_worker->name << " (" << company_worker->id << ")!\n";

                for (int i = 0; i < tools.size(); i++)
                {
                    Tool* tool = tools[i];
                    if (!tool->is_borrowed)
                    {
                        std::cout << i + 1 << ". " << tool->name << "\n";
                    }
                    else
                    {
                        std::cout << i + 1 << ". " << tool->name << " (borrowed by " << tool->borrowed_by << ")\n";
                    }
                }

                std::cout << "Enter serial number of the tool you want to borrow: ";
                int tool_serial;
                std::cin >> tool_serial;

                // if a user does not check the check_availability then the program will automatically let them know that the tool is borrowed already
                if (tool_serial > 0 && tool_serial <= tools.size())
                {
                    if (tools[tool_serial - 1]->is_borrowed)
                    {
                        std::cout << "This tool is already borrowed. Try again.\n";
                        continue;
                    }

                    std::cout << "How long do you want to borrow " << tools[tool_serial - 1]->name << " for? (in hours): ";
                    int borrow_time;
                    std::cin >> borrow_time;

                    // cannot borrow for more than 24hours
                    while (borrow_time > 24)
                    {
                        std::cout << "Borrow time cannot be more than 24 hours. Please enter a valid time: ";
                        std::cin >> borrow_time;
                    }

                    tools[tool_serial - 1]->borrow(borrow_id, borrow_time);

                    std::cout << "You have borrowed " << tools[tool_serial - 1]->name << " for " << borrow_time << " hour/s.\n";
                }
                else
                {
                    std::cout << "Invalid choice. Try again.\n";
                }
            }

                // this will let the user return a tool that is borrowed
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

                // this will show a list of the tools that has not been returned yet
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

                // this will end the program
            else if (choice == "end")
            {
                return 0;
            }
            else
            {
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    }

