#ifndef VIRUS_H
#define VIRUS_H

class Student;

#include "GameObject.h"
#include <iostream>
using namespace std;

enum VirusStates
{
	IN_ENVIRONMENT = 0,
	IN_STUDENT = 1,
	DEAD = 3
};
class Virus: public GameObject
{
protected:
	double virulence;
	double resistance;
	bool variant;
	double energy;
	bool is_in_student;
	int speed;
	bool is_moving;
	Vector2D delta;
	Point2D destination;
	string name;
	Student* current_student;
public:
	Virus(string name, double virulence, double resistance, double energy, bool variant, int speed, int id, Point2D in_loc);
	void infect(Student* student);
	bool get_variant();
	bool UpdateLocation(Point2D loc);
	void SetupLocation();
	double get_virulence();
	double get_resistance();
	double get_energy();
	bool get_in_student();
	bool Update();
	void ShowStatus();
	bool IsAlive();
	~Virus();
	bool ShouldBeVisible();
};

#endif