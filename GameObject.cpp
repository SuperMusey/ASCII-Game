#include "GameObject.h"

GameObject::GameObject(char in_code)
{
	display_code = in_code;
	id_num = 1;
	state = 0;
	cout << "GameObject Created" << endl;
}
GameObject::~GameObject()
{
	cout << "Game Object destroyed" << endl;
}
GameObject::GameObject(Point2D in_loc, int in_id, char in_code)
{
	location = in_loc;
	display_code = in_code;
	id_num = in_id;
	state = 0;
	cout << "GameObject Created" << endl;
}
Point2D GameObject::GetLocation()
{
	return location;
}
int GameObject::GetId()
{
	return id_num;
}
int GameObject::GetState()
{
	return state;
}
void GameObject::DrawSelf(char* ptr)
{
	*ptr = display_code;
	*(ptr + 1) = '0' + id_num;
}
void GameObject::ShowStatus()
{
	cout << display_code << id_num << " at " << location;
}