#ifndef MODEL_H
#define MODEL_H

#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Student.h"
#include "Virus.h"
#include "View.h"
#include "Input_Handling.h"
#include <vector>

class Model
{
private:
	int time;
	vector <GameObject*> object_ptrs;
	vector <GameObject*> active_ptrs;
	vector <Student*> student_ptrs;
	vector <DoctorsOffice*> office_ptrs;
	vector <ClassRoom*> class_ptrs;
	vector <Virus*> virus_ptrs;
	
public:
	Model();
	~Model();
	Student* GetStudentPtr(int id);
	DoctorsOffice* GetDoctorsOfficePtr(int id);
	ClassRoom* GetClassRoomPtr(int id);
	Virus* GetVirusPts(int id);
	void NewCommand(char type, int id, double x_loc, double y_loc);
	void CheckForVirus();
	bool Update();
	void Display(View& view);
	void ShowStatus();
};

#endif

