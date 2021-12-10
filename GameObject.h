#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point2D.h"

#include <iostream>
using namespace std;

class GameObject
{
protected:
	Point2D location;
	int id_num;
	char display_code;
	int state;
public:
	GameObject(char in_code);
	virtual ~GameObject();
	GameObject(Point2D in_loc, int in_id, char in_code);
	Point2D GetLocation();
	int GetId();
	int GetState();
	void DrawSelf(char* ptr);
	virtual void ShowStatus();
	virtual bool Update() = 0;
	virtual bool ShouldBeVisible() = 0;
};

#endif