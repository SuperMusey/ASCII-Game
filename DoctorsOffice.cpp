#include "DoctorsOffice.h"

DoctorsOffice::DoctorsOffice()
{
	display_code = 'D';
	vaccine_capacity = 100;
	num_vaccine_remaining = vaccine_capacity;
	dollar_cost_per_vaccine = 5;
	state = VACCINE_AVAILABLE;
	cout << "DoctorsOffice default constructed" << endl;
}

DoctorsOffice::~DoctorsOffice()
{
	cout << "Doctor's Office destructed" << endl;
}


DoctorsOffice::DoctorsOffice(int in_id, double vaccine_cost, unsigned int vaccine_cap, Point2D in_loc) : Building('D', in_id, in_loc)
{
	dollar_cost_per_vaccine = vaccine_cost;
	vaccine_capacity = vaccine_cap;
	num_vaccine_remaining = vaccine_capacity;
	state = VACCINE_AVAILABLE;
	cout << "DoctorsOfffice constructed" << endl;
}

bool DoctorsOffice::HasVaccine()
{
	if (this->num_vaccine_remaining == 0)
		return false;
	else
		return true;
}

unsigned int DoctorsOffice::GetNumVaccineRemaining()
{
	return num_vaccine_remaining;
}

bool DoctorsOffice::CanAffordVaccine(unsigned int vaccine, double budget)
{
	if (vaccine * dollar_cost_per_vaccine - budget >= 0)
		return true;
	else
		return false;
}

double DoctorsOffice::GetDollarCost(unsigned int vaccine)
{
	return dollar_cost_per_vaccine * vaccine;
}

unsigned int DoctorsOffice::DistributeVaccine(unsigned int vaccine_needed)
{
	if (num_vaccine_remaining >= vaccine_needed)
	{
		this->num_vaccine_remaining = this->num_vaccine_remaining - vaccine_needed;
		return vaccine_needed;
	}
	else
	{
		int returnVal_vaccine = this->num_vaccine_remaining;
		this->num_vaccine_remaining = 0;
		return returnVal_vaccine;
	}
}

bool DoctorsOffice::Update()
{
	if (this->num_vaccine_remaining == 0)
	{
			state = NO_VACCINE_AVAILABLE;
			display_code = 'd';
			cout << "DoctorsOffice " << id_num << "has ran out of vaccine." << endl;
			return true;
	}
	else
		return false;
}

bool DoctorsOffice::ShouldBeVisible()
{
	if (this->GetNumVaccineRemaining() == 0)
		return false;
	else
		return true;
}

void DoctorsOffice::ShowStatus()
{
	cout << "Doctors Office Status: " << endl;
	Building::ShowStatus();
	cout << "	" << "Dollars per vaccine: " << dollar_cost_per_vaccine << endl;
	if(num_vaccine_remaining!=1)
		cout << "	has " << num_vaccine_remaining << " vaccines remaining" << endl;
	else
		cout << "	has " << num_vaccine_remaining << " vaccine remaining" << endl;	
}
