#include "Vector2D.h"
#include "Point2D.h"
#include "GameObject.h"
#include "Building.h"
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Student.h"
#include "Model.h"
#include "GameCommand.h"
#include "View.h"
#include "Input_Handling.h"
#include <stdlib.h>
#include <typeinfo>
#include <sstream>
#include <vector>

// run using updated compiler: c++11 string to data type functions used

int main()
{
    View view;
    Model model;

    string in_com;
    char c_code = '0';          //stores the command code
    int second_arg = 0;         //is always student ID or is not
    double* third_arg = new double;     //is either class/office id(int), location x value(double), vaccine/assignment amount(unsigned int), or is not
    int third_arg_int = 0;
    unsigned int* third_arg_uint = new unsigned int;
    double* fourth_arg = new double;    //always location y value or is not

    model.ShowStatus();
    model.Display(view);

    while (true)
    {
        try
        {
            cout << "Enter command code" << endl;
            getline(cin, in_com);
            char* ptr = nullptr;

            vector <string> tokens;
            stringstream check(in_com);
            string temp_str;
            while (getline(check, temp_str, ' '))
            {
                tokens.push_back(temp_str);
            }

            int com_size = tokens.size();
            c_code = *tokens[0].c_str();

            
            switch (c_code)
                {
                    case 'm':
                    {
                        if (com_size != 4)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        if (!isdigit(*(tokens[1].c_str())))
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        else
                        {
                            second_arg = stoi(tokens[1]);
                        }
                        *third_arg = strtod(tokens[2].c_str(), &ptr);
                        if (ptr == (tokens[2].c_str()) || *ptr != '\0')
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        *fourth_arg = strtod(tokens[3].c_str(), &ptr);
                        if (ptr == (tokens[3].c_str()) || *ptr != '\0')
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        Point2D* p1 = new Point2D(*third_arg, *fourth_arg);
                        cout << "attempting to move " << second_arg << " to " << *p1 << endl;
                        DoMoveCommand(model, second_arg, *p1);
                    }
                    break;
                    case 'd':
                    {
                        if (com_size != 3)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        if (!isdigit(*(tokens[1].c_str())) || !isdigit(*(tokens[2].c_str())))
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        else
                        {
                            second_arg = stoi(tokens[1]);
                            third_arg_int = stoi(tokens[2]);
                        }
                        cout << "attempting to move " << second_arg << " to doctors office id " << third_arg_int << endl;
                        DoMoveToDoctorCommand(model, second_arg, third_arg_int);
                    }
                    break;
                    case 'c':
                    {
                        if (com_size != 3)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        if (!isdigit(*(tokens[1].c_str())) || !isdigit(*(tokens[2].c_str())))
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        else
                        {
                            second_arg = stoi(tokens[1]);
                            third_arg_int = stoi(tokens[2]);
                        }
                        cout << "attempting to move " << second_arg << " to classroom id " << third_arg_int << endl;
                        DoMoveToClassCommand(model, second_arg, third_arg_int);
                    }
                    break;
                    case 's':
                    {
                        if (com_size != 2)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        if (!isdigit(*(tokens[1].c_str())))
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        else
                        {
                            second_arg = stoi(tokens[1]);
                        }
                        cout << "attempting to stop " << second_arg << endl;
                        DoStopCommand(model, second_arg);
                    }
                    break;
                    case 'v':
                    {
                        if (com_size != 3)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        if (!isdigit(*(tokens[1].c_str())))
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        else
                        {
                            second_arg = stoi(tokens[1]);
                        }
                        *third_arg_uint = strtoul(tokens[2].c_str(), &ptr, 10);
                        if (ptr == (tokens[2].c_str()) || *ptr != '\0')
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        cout << " attempting to recover " << *third_arg_uint << " vaccines for " << second_arg << endl;
                        DoRecoverInOfficeCommand(model, second_arg, *third_arg_uint);
                    }
                    break;
                    case 'a':
                    {
                        if (com_size != 3)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        if (!isdigit(*(tokens[1].c_str())))
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        else
                        {
                            second_arg = stoi(tokens[1]);
                        }
                        *third_arg_uint = strtoul(tokens[2].c_str(), &ptr, 10);
                        if (ptr == (tokens[2].c_str()) || *ptr != '\0')
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        cout << "attempting to teach " << *third_arg_uint << " assignments to " << second_arg << endl;
                        DoLearningCommand(model, second_arg, *third_arg_uint);
                    }
                    break;
                    case 'g':
                    {
                        if (com_size != 1)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        cout << "go one step" << endl;
                        DoGoCommand(model, view);
                    }
                    break;
                    case 'r':
                    {
                        if (com_size != 1)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        cout << "run event" << endl;
                        DoRunCommand(model, view);
                    }
                    break;
                    case 'q':
                    {
                        if (com_size != 1)
                        {
                            throw Invalid_Input("Wrong number of arguments");
                        }
                        cout << "exiting" << endl;
                        return 0;
                    }
                    break;
                    case 'n':
                    {
                        char type = *tokens[1].c_str();
                        int id;
                        double* in_x = new double;
                        double* in_y = new double;
                        if (type != 'd' && type != 'c' && type != 's' && type != 'v')
                        {
                            throw Invalid_Input("Wrong type");
                        }
                        if (!isdigit(*(tokens[2].c_str())))
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        else
                        {
                            id = stoi(tokens[2]);
                        }
                        *in_x = strtod(tokens[3].c_str(), &ptr);
                        if (ptr == (tokens[3].c_str()) || *ptr != '\0')
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        *in_y = strtod(tokens[4].c_str(), &ptr);
                        if (ptr == (tokens[4].c_str()) || *ptr != '\0')
                        {
                            throw Invalid_Input("Wrong arguments");
                        }
                        model.NewCommand(type, id, *in_x, *in_y);
                    }
                        break;
                    default:
                    {
                        throw Invalid_Input("No such command code");
                    }
                }
            
        }
        catch (Invalid_Input& except)
        {
            cout << "Invalid Input - " << except.msg_ptr << endl;
        }
    }
    return 0;
}