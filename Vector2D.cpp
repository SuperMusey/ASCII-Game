#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}
Vector2D::Vector2D(double in_x, double in_y)
{
	x = in_x;
	y = in_y;
}
Vector2D operator* (Vector2D v1, double d)
{
	return Vector2D(v1.x * d, v1.y * d);
}
Vector2D operator/ (Vector2D v1, double d)
{
	if (d == 0)
		return Vector2D(v1.x, v1.y);
	else
		return Vector2D(v1.x / d, v1.y / d);
}
ostream& operator<< (ostream& out, Vector2D obj)
{
	cout << "<" << obj.x << "," << obj.y << ">" << endl;
	return out;
}
