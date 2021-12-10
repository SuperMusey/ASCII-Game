#include "Student.h"

Student::Student() : GameObject('S')
{
	speed = 5;
	cout << "Student Default constructed" << endl;
}

Student::~Student()
{
	cout << "Student destroyed" << endl;
}

Student::Student(char in_code) : GameObject(in_code)
{
	speed = 5;
	state = STOPPED;
	cout << "Student constructed" << endl;
}

Student::Student(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc, in_id, in_code)
{
	speed = in_speed;
	state = STOPPED;
	name = in_name;
	cout << "Student constructed" << endl;
}

string Student::GetName()
{
	return name;
}

void Student::StartMoving(Point2D dest)
{
	if (state == IN_CLASS && GetDistanceBetween(dest, this->destination) != 0)
	{
		current_class -> RemoveOneStudent();
	}
	if (state == AT_DOCTORS && GetDistanceBetween(dest, this->destination) != 0)
	{
		current_office -> RemoveOneStudent();
	}
	SetupDestination(dest);
	if (GetDistanceBetween(dest, location) == 0)
	{
		cout << display_code << " " << id_num << " :I'm already there. See?" << endl;
	}
	if (!IsInfected())	
	{
		if (GetDistanceBetween(dest, location) != 0)
		{
			cout << display_code << " " << id_num << " :On My Way." << endl;
		}
		state = MOVING;
	}
	else
	{
		cout << display_code << " " << id_num << " :I am infected so I can't move..." << endl;
	}
}

void Student::StartMovingToClass(ClassRoom* classr)
{
	if (state == IN_CLASS && GetDistanceBetween(classr->GetLocation(), this->destination) != 0)
	{
		current_class->RemoveOneStudent();
	}
	if (state == AT_DOCTORS && GetDistanceBetween(classr->GetLocation(), this->destination) != 0)
	{
		current_office->RemoveOneStudent();
	}
	SetupDestination(classr->GetLocation());
	current_class = classr;
	if (!IsInfected())
	{ 
		if (GetDistanceBetween(classr->GetLocation(), this->GetLocation()) == 0)
		{
			cout << display_code << id_num << " :I'm already at the ClassRoom" << endl;
		}
		else
		{
			cout << display_code << id_num << " :on my way to class" << id_num << endl;
			state = MOVING_TO_CLASS;
		}
	}
	else
	{
		cout << display_code << id_num << " :I am infected so I can't move..." << endl;
	}
}

void Student::StartMovingToDoctor(DoctorsOffice* office)
{
	if (state == IN_CLASS && GetDistanceBetween(office->GetLocation(), this->destination) != 0)
	{
		current_class->RemoveOneStudent();
	}
	if (state == AT_DOCTORS && GetDistanceBetween(office->GetLocation(), this->destination) != 0)
	{
		current_office->RemoveOneStudent();
	}
	SetupDestination(office->GetLocation());
	current_office = office;
	if (!IsInfected())
	{
		if (GetDistanceBetween(office->GetLocation(), this->GetLocation()) == 0)
		{
			cout << display_code << id_num << " :I'm already at the Doctor's" << endl;
		}
		else
		{
			state = MOVING_TO_DOCTOR;
			cout << display_code << id_num << " :On my way to doctor's " << current_office->GetId() << endl;
		}
	}
	else
	{
		cout << display_code << id_num << " :I am infected so I should have gone to the doctor's..." << endl;
	}	
}

bool Student::EncounteredVirus(Virus* virus)
{
	if (fabs((virus->GetLocation() - location).x) <= fabs(delta.x) && fabs((virus->GetLocation() - location).y) <= fabs(delta.y) && !has_virus  && !(virus->get_in_student()))
	{
		infection = virus;
		has_virus = true;
		virus->infect(this);
		virus->UpdateLocation(this->location);
		factor_decrease = virus->get_virulence();
		return true;
	}
	if (virus->get_energy() == 0 && has_virus)
	{
		has_virus = false;
		factor_decrease = 0;
	}
	return false;
}

void Student::StartLearning(unsigned int num_assignments)
{
	if (IsInfected())
	{
		cout << display_code << id_num << " :I'm infected so no more school for me..." << endl;
	}
	else if (current_class == nullptr || GetDistanceBetween(current_class->GetLocation(), this->GetLocation()) != 0)
	{
		cout << display_code << id_num << " :I can only learn in a ClassRoom" << endl;
	}
	else if (current_class->GetDollarCost(num_assignments) > dollars)
	{
		cout << name << " has " << dollars << " dollars" << endl;
		cout << num_assignments << " assignments costs " << current_class->GetDollarCost(num_assignments) << endl;
		cout << display_code << id_num << " :Not enough money for school." << endl;
	}
	else if (current_class->GetNumAssignmentsRemaining() == 0)
	{
		cout << display_code << id_num << " :Cannot learn! This class has no more assignments" << endl;
	}
	else
	{
		state = STUDYING_IN_CLASS;
		cout << id_num << " :Started to learn at the ClassRoom " << current_class->GetId() << " with " << num_assignments << " assignments." << endl;
		assignments_to_buy = num_assignments;
	}
}

void Student::StartRecoveringAntibodies(unsigned int num_vaccines)
{
	if (current_office == nullptr || GetDistanceBetween(current_office->GetLocation(), this->GetLocation()) != 0)
	{
		cout << display_code << id_num << " : I can only recover antibodies at a Doctor’s Office!" << endl;
	}
	else if (current_office->GetNumVaccineRemaining() == 0)
	{
		cout << display_code << id_num << " :Cannot recover! No vaccine remaining in this Doctor's Office" << endl;
	}
	else if (current_office->GetDollarCost(num_vaccines) > dollars)
	{
		cout << display_code << id_num << " :Not enough money to recover antibodies" << endl;
	}
	else
	{
		state = RECOVERING_ANTIBODIES;
		vaccines_to_buy = num_vaccines;
	}
}

void Student::Stop()
{
	state = STOPPED;
	cout << display_code << id_num << " :Stopping..." << endl;
}

bool Student::IsInfected()
{
	if (antibodies == 0)
	{
		return true;
	}
	else
		return false;
}

bool Student::ShouldBeVisible()
{
	if (this->IsInfected())
	{
		return false;
	}
	else
		return true;
}

void Student::ShowStatus()
{
	cout << name << " status:" << state << endl;
	GameObject::ShowStatus();
	if (state == STOPPED)
	{
		cout << "stopped" << endl;
	}
	else if (state == MOVING)
	{
		cout << "moving at a speed of " << speed << " to destination " << "<" << destination.x << "," << destination.y << ">" << " at each step of " << delta << endl;
	}
	else if (state == MOVING_TO_CLASS)
	{
		cout << "heading to classroom " << current_class->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
	}
	else if (state == MOVING_TO_DOCTOR)
	{
		cout << "heading to Doctor's Office " << current_office->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
	}
	else if (state == IN_CLASS)
	{
		cout << "inside classroom " << current_class->GetId() << endl;
	}
	else if (state == AT_DOCTORS)
	{
		cout << "inside Doctor's Office " << current_office->GetId() << endl;
	}
	else if (state == STUDYING_IN_CLASS)
	{
		cout << "studying in classroom " << current_class->GetId() << endl;
	}
	else if (state == INFECTED)
	{
		cout << "is infected " << endl;
	}
	else
	{
		cout << "recovering antibodies in Doctor's Office " << current_class->GetId() << endl;
	}
	if (has_virus)
	{
		cout << name << " has virus" << endl;
	}
}

bool Student::Update()
{ 
	if (infection != NULL)
		EncounteredVirus(infection);
	cout << name << " info" << endl;
	if (antibodies == 0)
	{
		state = INFECTED;
		cout << name << " is out of antibodies and can't move" << endl;
		return false;
	}
	else if (state == STOPPED)
	{
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		return false;
	}
	else if (state == MOVING)
	{
		dollars += GetRandomAmountOfDollars();
		if (has_virus && antibodies != 1)
		{
			antibodies -= 1 + (unsigned int)factor_decrease;
		}
		else
			antibodies -= 1;
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		if (UpdateLocation())
		{
			state = STOPPED;
			return true;
		}
	}
	else if (state == MOVING_TO_CLASS)
	{
		dollars += GetRandomAmountOfDollars();
		if (has_virus && antibodies != 1)
		{
			antibodies -= 1 + factor_decrease;
		}
		else
			antibodies -= 1;
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		if (UpdateLocation())
		{
			state = IN_CLASS;
			current_class->AddOneStudent();
			return true;
		}
	}
	else if (state == MOVING_TO_DOCTOR)
	{
		dollars += GetRandomAmountOfDollars();
		if (has_virus && antibodies != 1)
		{
			antibodies -= 1 + factor_decrease;
		}
		else
			antibodies -= 1;
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		if (UpdateLocation())
		{
			state = AT_DOCTORS;
			current_office->AddOneStudent();
			return true;
		}
	}
	else if (state == IN_CLASS)
	{
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		return false;
	}
	else if (state == AT_DOCTORS)
	{
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		return false;
	}
	else if (state == STUDYING_IN_CLASS)
	{
		antibodies -= current_class->GetAntibodyCost(assignments_to_buy);
		dollars -= current_class->GetDollarCost(assignments_to_buy);
		unsigned int credits_gained = current_class->TrainStudents(assignments_to_buy);
		credits += credits_gained;
		cout << "** " << name << " completed " << assignments_to_buy << " assignment(s)!**" << endl;
		cout << "** " << name << " gained " << credits_gained << " credit(s)!**" << endl;
		state = IN_CLASS;
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		return true;
	}
	else
	{
		unsigned int vaccines_gained = current_office->DistributeVaccine(vaccines_to_buy);
		dollars -= current_office->GetDollarCost(vaccines_gained);
		antibodies += vaccines_gained * 5;
		cout << "** " << name << " recovered " << vaccines_gained * 5 << " antibodies!**" << endl;
		cout << "** " << name << " bought " << vaccines_gained << " vaccine(s)!" << endl;
		state = AT_DOCTORS;
		cout << "	" << "Antibodies: " << antibodies << endl;
		cout << "	" << "Dollars: " << dollars << endl;
		cout << "	" << "Credits: " << credits << endl;
		return true;
	}
	return false;
}

bool Student::UpdateLocation()
{
	if (fabs((destination - location).x) <= fabs(delta.x) && fabs((destination - location).y) <= fabs(delta.y))
	{
		location = destination;
		cout << "arrived" << endl;
		return true;
	}
	else
	{
		location = location + delta;
		cout << "moved" << endl;
		return false;
	}
}

void Student::SetupDestination(Point2D dest)
{
	destination = dest;
	delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

double GetRandomAmountOfDollars()
{
	srand(time(NULL));
	return (double)(rand()) * 2.0/(double)RAND_MAX;
}
