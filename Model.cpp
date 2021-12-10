#include "Model.h"

Model::Model()
{
	time = 0;	
	Student* S1 = new Student("Homer", 1, 'S', 2, Point2D(5, 1));
	Student* S2 = new Student("Marge", 2, 'S', 1, Point2D(10, 1));
	DoctorsOffice* D1 = new DoctorsOffice(1, 1, 100, Point2D(1, 20));
	DoctorsOffice* D2 = new DoctorsOffice(2, 2, 200, Point2D(10, 20));
	ClassRoom* C1 = new ClassRoom(10, 1, 2, 3, 1, Point2D(0, 0));
	ClassRoom* C2 = new ClassRoom(20, 5, 7.5, 4, 2, Point2D(5, 5));
	Virus* V1 = new Virus("cake_root_error.exe", 1, 2, 10, false, 2, 1, Point2D(12,12));
	Virus* V2 = new Virus("snake_root_error.exe", 2, 2, 10, false, 2, 2, Point2D(16, 8));
	object_ptrs.push_back(S1);
	object_ptrs.push_back(S2);
	object_ptrs.push_back(D1);
	object_ptrs.push_back(D2);
	object_ptrs.push_back(C1);
	object_ptrs.push_back(C2);
	object_ptrs.push_back(V1);
	object_ptrs.push_back(V2);
	student_ptrs.push_back(S1);
	student_ptrs.push_back(S2);
	office_ptrs.push_back(D1);
	office_ptrs.push_back(D2);
	class_ptrs.push_back(C1);
	class_ptrs.push_back(C2);
	virus_ptrs.push_back(V1);
	virus_ptrs.push_back(V2);
	active_ptrs = object_ptrs;

	cout << "Model default constructed" << endl;
}

Model::~Model()
{
	cout << "Model destructed" << endl;
	for(int i = 0; i < object_ptrs.size(); i++)
	{
		delete(object_ptrs[i]);
	}
}

Student* Model::GetStudentPtr(int id)
{
	for (int i = 0; i < student_ptrs.size(); i++)
	{ 
		if (student_ptrs[i]->GetId() == id)
			return student_ptrs[i];
	}
	return nullptr;
}

DoctorsOffice* Model::GetDoctorsOfficePtr(int id)
{
	for (int i = 0; i < office_ptrs.size(); i++)
	{
		if (office_ptrs[i]->GetId() == id)
			return office_ptrs[i];
	}
	return nullptr;
}

ClassRoom* Model::GetClassRoomPtr(int id)
{
	for (int i = 0; i < class_ptrs.size(); i++)
	{
		if (class_ptrs[i]->GetId() == id)
			return class_ptrs[i];
	}
	return nullptr;
}

Virus* Model::GetVirusPts(int id)
{
	for (int i = 0; i < virus_ptrs.size(); i++)
	{
		if (virus_ptrs[i]->GetId() == id)
			return virus_ptrs[i];
	}
	return nullptr;
}

void Model::NewCommand(char type, int id, double x_loc, double y_loc)
{
	if (((x_loc > 20 || x_loc < 0) && (y_loc > 20 || y_loc < 0)))
	{
		throw Invalid_Input("Out of bounds, cannot make object there");
	}
	if (type == 'd')
	{
		if (!(GetDoctorsOfficePtr(id) == nullptr))
			throw Invalid_Input("DoctorsOffice id already exists");
		else
		{
			DoctorsOffice* push_obj = new DoctorsOffice(id, 1, 100, Point2D(x_loc, y_loc));
			office_ptrs.push_back(push_obj);
			object_ptrs.push_back(push_obj);
			active_ptrs.push_back(push_obj);
		}
	}
	else if (type == 'c')
	{
		if (!(GetClassRoomPtr(id) == nullptr))
			throw Invalid_Input("ClassRoom id already exists");
		else
		{
			ClassRoom* push_obj = new ClassRoom(10, 1, 2, 3, id, Point2D(x_loc, y_loc));
			class_ptrs.push_back(push_obj);
			object_ptrs.push_back(push_obj);
			active_ptrs.push_back(push_obj);
		}
	}
	else if (type == 's')
	{
		if (!(GetStudentPtr(id) == nullptr))
			throw Invalid_Input("Student id already exists");
		else
		{
			Student* push_obj = new Student("Student", id, 'S', 2, Point2D(x_loc, y_loc));
			student_ptrs.push_back(push_obj);
			object_ptrs.push_back(push_obj);
			active_ptrs.push_back(push_obj);
		}
	}
	else if (type == 'v')
	{
		if (!(GetVirusPts(id) == nullptr))
			throw Invalid_Input("Student id already exists");
		else
		{
			Virus* push_obj = new Virus("virus.exe", 1, 2, 10, false, 2, id, Point2D(x_loc, y_loc));
			virus_ptrs.push_back(push_obj);
			object_ptrs.push_back(push_obj);
			active_ptrs.push_back(push_obj);
		}
	}
	else
		throw Invalid_Input("Invalid input entered");
}

void Model::CheckForVirus()
{
	bool flag = false;
	for (int i = 0; i < student_ptrs.size(); i++)
	{
		for (int j = 0; j < virus_ptrs.size(); j++)
		{
			flag = student_ptrs[i]->EncounteredVirus(virus_ptrs[j]);
		}		
	}
}

bool Model::Update()
{
	bool flag = false;
	time += 1;
	CheckForVirus();
	for (int i = 0; i < object_ptrs.size(); i++)
	{
		if (object_ptrs[i]->Update())
		{
			flag = true;
		}
	}
	unsigned int assign_check = 0;;
	for (int i = 0; i < class_ptrs.size(); i++)
	{
		assign_check += class_ptrs[i]->GetNumAssignmentsRemaining();
	}
	if (assign_check == 0)
	{
		cout << "GAME OVER: You win! All assignments done!" << endl;
		exit(EXIT_SUCCESS);
	}
	unsigned int infect_check = 0;
	for (int i = 0; i < student_ptrs.size(); i++)
	{
		if (student_ptrs[i]->IsInfected())
		{
			infect_check++;
		}
	}
	if (infect_check == student_ptrs.size())
	{
		cout << "GAME OVER: You lose! All your students are infected!" << endl;
		exit(EXIT_SUCCESS);
	}
	for (int i = 0; i < active_ptrs.size(); i++)
	{
		if (!active_ptrs[i]->ShouldBeVisible())
			active_ptrs.erase(active_ptrs.begin()+i);
	}
	return flag;
}

void Model::Display(View& view)
{
	cout << "Time: " << time << endl;
	view.Clear();
	for (int i = 0; i < active_ptrs.size(); i++)
	{
		view.Plot(this->active_ptrs[i]);
	}
	view.Draw();
}

void Model::ShowStatus()
{
	cout << "Game Time is: " << time << endl;
	for (int i = 0; i < object_ptrs.size(); i++)
	{
		object_ptrs[i]->ShowStatus();
	}
}
