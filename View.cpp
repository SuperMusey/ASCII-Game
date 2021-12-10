#include "View.h"

bool View::GetSubscripts(int& out_x, int& out_y, Point2D location)
{
    out_x = (int)(((location - origin) / scale).x);
    out_y = (int)(((location - origin) / scale).y);
    if ((out_x < 11 && out_x >= 0) && (out_y < 11 && out_y >= 0))
    {
        return true;
    }
    cout << "An object is outside the display" << endl;
    return false;
}

View::View()
{
    size = 11;
    scale = 2;
    origin.x = 0.0;
    origin.y = 0.0;
}

void View::Clear()
{
    for (int i = 0; i < view_maxsize; i++)
    {
        for (int j = 0; j < view_maxsize; j++)
        {
                grid[i][j][0] = '.';
                grid[i][j][1] = ' ';
        }
    }
}

void View::Plot(GameObject* ptr)
{
    int* out_x = new int();
    int* out_y = new int();
    char* ptr_self = new char();
    Point2D location = ptr->GetLocation();
    if (GetSubscripts(*out_x, *out_y, location))
    {
        ptr->DrawSelf(ptr_self);
        if (grid[*out_x][*out_y][0] == '.')
        {
            grid[*out_x][*out_y][0] = *(ptr_self + 0);
            grid[*out_x][*out_y][1] = *(ptr_self + 1);
        }
        else
        {
            grid[*out_x][*out_y][0] = '*';
            grid[*out_x][*out_y][1] = ' ';
        }
    }
}

void View::Draw()
{
    for (int j = size - 1; j >= -1; j--) 
    {
        for (int i = -1; i <= size - 1; i++) 
        {
            if (i == -1 && j % 2 == 0) 
            {
                cout << j*2;
                if (j / 5 == 0) 
                {
                    cout << " ";
                }
            }
            else if (i == -1 && j % 2 != 0) 
            {
                cout << "  ";
            }
            else if (j == -1 && i % 2 == 0) 
            {
                cout << i*2;
                if (i / 5 == 0) 
                {
                    cout << " ";
                }
                cout << "  ";
            }
            if (i >= 0 && j >= 0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}
