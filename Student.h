#ifndef STUDENT_H
#define STUDENT_H

#include "GameObject.h"
#include "Virus.h"
#include "ClassRoom.h"
#include "DoctorsOffice.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iomanip>

enum StudentStates
{
	STOPPED = 0,
	MOVING = 1,
	INFECTED = 2,
	AT_DOCTORS = 3,
	IN_CLASS = 4,
	MOVING_TO_DOCTOR = 5,
	MOVING_TO_CLASS = 6,
	STUDYING_IN_CLASS = 7,
	RECOVERING_ANTIBODIES = 8
};

class Student : public GameObject
{
public:
	Student();
	virtual ~Student();
	Student(char in_code);
	Student(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
	string GetName();
	void StartMoving(Point2D dest);
	void StartMovingToClass(ClassRoom* classr);
	void StartMovingToDoctor(DoctorsOffice* office);
	bool EncounteredVirus(Virus* virus);
	void StartLearning(unsigned int num_assignments);
	void StartRecoveringAntibodies(unsigned int num_vaccines);
	void Stop();
	bool IsInfected();
	bool ShouldBeVisible();
	void ShowStatus();
	bool Update();
protected:
	bool UpdateLocation();
	void SetupDestination(Point2D dest);
private:
	double speed;
	double factor_decrease = 0;
	bool is_at_doctor = false;
	bool is_in_class = false;
	bool has_virus = false;
	unsigned int antibodies = 20;
	unsigned int credits = 0;
	double dollars = 0;
	unsigned int assignments_to_buy = 0;
	unsigned int vaccines_to_buy = 0;
	string name;
	DoctorsOffice* current_office = NULL;
	ClassRoom* current_class = NULL;
	Virus* infection = NULL;
	Point2D destination;
	Vector2D delta;
};

double GetRandomAmountOfDollars();

#endif

