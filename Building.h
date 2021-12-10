#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"

class Building : public GameObject
{
private:
	unsigned int student_count;
public:
	Building();
	Building(char in_code, int in_Id, Point2D in_loc);
	void AddOneStudent();
	void RemoveOneStudent();
	void ShowStatus();
	bool ShouldBeVisible();
};

#endif