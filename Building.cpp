#include "Building.h"

Building::Building() : GameObject('B')
{
	student_count = 0;
	cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_Id, Point2D in_loc) : GameObject(in_loc, in_Id, in_code)
{
	student_count = 0;
	cout << "Building constructed" << endl;
}

void Building::AddOneStudent()
{
	student_count++;
}

void Building::RemoveOneStudent()
{
	student_count--;
}

void Building::ShowStatus()
{
	GameObject::ShowStatus();
	if (student_count > 1)
		cout << student_count << " students are in this buiding" << endl;
	else
		cout << student_count << " student is in this buiding" << endl;
}

bool Building::ShouldBeVisible()
{
	return true;
}
