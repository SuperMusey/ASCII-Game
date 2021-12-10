#include "Virus.h"

Virus::Virus(string name, double virulence, double resistance, double energy, bool variant, int speed, int id, Point2D in_loc): GameObject(in_loc, id,'V')
{
	this->name = name;
	this->virulence = virulence;	
	this->resistance = resistance;
	this->energy = energy;
	this->variant = variant;
	this->speed = speed;
	is_moving = false;
	is_in_student = false;
	state = IN_ENVIRONMENT;
}

void Virus::infect(Student* student)
{
	current_student = student;
	state = IN_STUDENT;
	is_in_student = true;
}

bool Virus::get_variant()
{
	return false;
}

bool Virus::UpdateLocation(Point2D loc)
{
	if (current_student != NULL && state == IN_STUDENT)
	{
		location = loc;
		return true;
	}
	else if (fabs((loc - location).x) <= fabs(delta.x) && fabs((loc - location).y) <= fabs(delta.y))
	{
		location = loc;
		is_moving = false;
		return true;
	}
	else
	{
		location = location + delta;
		is_moving = true;
		return false;
	}
}

void Virus::SetupLocation()
{
	srand(time(NULL));
	Point2D dest;
	int x_val = rand() % 21;
	int y_val = rand() % 21;
	dest.x = x_val;
	dest.y = y_val;
	delta = (dest - location) * (speed / GetDistanceBetween(dest, location));
	destination = dest;
}

bool Virus::Update()
{
	if (state == IN_ENVIRONMENT)
	{
		if (!is_moving)
			SetupLocation();
		UpdateLocation(destination);
		cout << name << " is moving in an environment" << endl;
		return true;
	}
	else if (state == DEAD)
	{
		cout << name << " is dead." << endl;
		return false;
	}
	else
	{
		energy -= 1;
		if (IsAlive())
			cout << name << " has infected student" << endl;
		else
			cout << name << " is dead and not in a student" << endl;
		return true;
	}
}

double Virus::get_virulence()
{
	return virulence;
}

double Virus::get_resistance()
{
	return resistance;
}

double Virus::get_energy()
{
	return energy;
}

bool Virus::get_in_student()
{
	return is_in_student;
}


void Virus::ShowStatus()
{
	if (state == IN_ENVIRONMENT)
	{
		cout << name << " is in the environment" << endl;
	}
	else if (state == IN_STUDENT)
	{
		cout << name << " is in a student" << endl;
	}
	else if (state == DEAD)
	{
		cout << name << " is dead" << endl;
	}
	else
	{
		cout << "No state set" << endl;
	}
}

bool Virus::IsAlive()
{
	if (energy == 0)
	{
		state = DEAD;
		is_in_student = false;
		current_student = NULL;
		return false;
	}	
	else
	{
		return true;
	}
}

bool Virus::ShouldBeVisible()
{
	if (state == IN_ENVIRONMENT)
		return true;
	else
		return false;
}

Virus::~Virus()
{
	cout << "Virus Object destructed" << endl;
}

