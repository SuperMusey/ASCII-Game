#include "ClassRoom.h"

ClassRoom::ClassRoom() : Building()
{
	display_code = 'C';
	state = NOT_PASSED;
	max_number_of_assignments = 10;
	num_assignments_remaining = max_number_of_assignments;
	antibody_cost_per_assignment = 1;
	dollar_cost_per_assignment = 1.0;
	credits_per_assignment = 2;
	cout << "ClassRoom default constructed" << endl;
}

ClassRoom::~ClassRoom()
{
	cout << "ClassRoom destructed" << endl;
}


ClassRoom::ClassRoom(unsigned int max_assign, unsigned int antibody_cost, double dollar_cost, unsigned int crd_per_assign, int in_id, Point2D in_loc) : Building('C', in_id, in_loc)
{
	state = NOT_PASSED;
	max_number_of_assignments = max_assign;
	num_assignments_remaining = max_number_of_assignments;
	antibody_cost_per_assignment = antibody_cost;
	credits_per_assignment = crd_per_assign;
	dollar_cost_per_assignment = dollar_cost;
	cout << "ClassRoom constructed" << endl;
}

double ClassRoom::GetDollarCost(unsigned int unit_qty)
{
	if (unit_qty < num_assignments_remaining)
	{
		return dollar_cost_per_assignment * unit_qty;
	}
	else
	{
		return dollar_cost_per_assignment * num_assignments_remaining;
	}
}
	

unsigned int ClassRoom::GetAntibodyCost(unsigned int unit_qty)
{
	if (unit_qty < num_assignments_remaining)
	{
		return antibody_cost_per_assignment * unit_qty;
	}
	else
	{
		return antibody_cost_per_assignment * num_assignments_remaining;
	}
}

unsigned int ClassRoom::GetNumAssignmentsRemaining()
{
	return num_assignments_remaining;
}

bool ClassRoom::IsAbleToLearn(unsigned int unit_qty, double budget, unsigned int antibodies)
{
	bool flag = false;
	if (budget / dollar_cost_per_assignment >= unit_qty)
	{
		if (unit_qty * antibody_cost_per_assignment <= antibodies)
			flag = true;
	}
	else
		flag = false;
	return flag;
}

unsigned int ClassRoom::TrainStudents(unsigned int assignment_units)
{
	if (assignment_units < num_assignments_remaining)
	{
		num_assignments_remaining -= assignment_units;
		return assignment_units * credits_per_assignment;
	}
	else
	{
		int temp_var = num_assignments_remaining;
		num_assignments_remaining = 0;
		return temp_var * credits_per_assignment;
	}	
}

bool ClassRoom::Update()
{
	if (num_assignments_remaining == 0 && state != PASSED)
	{
		state = PASSED;
		display_code = 'c';
		cout << display_code << id_num << " has been passed" << endl;
		return true;
	}
	else
		return false;
}

bool ClassRoom::ShouldBeVisible()
{
	if (this->GetNumAssignmentsRemaining() == 0)
		return false;
	else
		return true;
}

bool ClassRoom::passed()
{
	if (num_assignments_remaining == 0)
		return true;
	else
		return false;
}

void ClassRoom::ShowStatus()
{
	cout << "ClassRoomStatus:" << endl;
	Building::ShowStatus();
	cout << "	" << "Max number of assignments: " << max_number_of_assignments << endl;
	cout << "	" << "Antibody cost per assignment: " << antibody_cost_per_assignment << endl;
	cout << "	" << "Dollar cost per assignment: " << dollar_cost_per_assignment << endl;
	cout << "	" << "Credits per assignment: " << credits_per_assignment << endl;
	cout << num_assignments_remaining << " assignment(s) are remaining for this ClassRoom" << endl;
}
