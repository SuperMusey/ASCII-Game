#include "GameCommand.h"

void DoMoveCommand(Model& model, int student_id, Point2D p1)
{
	if (model.GetStudentPtr(student_id) != nullptr)
	{
		Student* student = model.GetStudentPtr(student_id);
		cout << student->GetName() << " to " << p1 << endl;
		student->StartMoving(p1);
	}
	else
	{
		throw Invalid_Input("Enter a valid command");
	}
}

void DoMoveToDoctorCommand(Model& model, int student_id, int office_id)
{
	if (model.GetStudentPtr(student_id) != nullptr && model.GetDoctorsOfficePtr(office_id)!=nullptr)
	{
		Student* student = model.GetStudentPtr(student_id);
		cout << student->GetName() << " to doctors office " << office_id << endl;
		student->StartMovingToDoctor(model.GetDoctorsOfficePtr(office_id));
	}
	else
	{
		throw Invalid_Input("Enter a valid command");
	}
}

void DoMoveToClassCommand(Model& model, int student_id, int class_id)
{
	if (model.GetStudentPtr(student_id) != nullptr && model.GetClassRoomPtr(class_id) != nullptr)
	{
		Student* student = model.GetStudentPtr(student_id);
		cout << student->GetName() << " to classroom " << class_id << endl;
		student->StartMovingToClass(model.GetClassRoomPtr(class_id));
	}
	else
	{
		throw Invalid_Input("Enter a valid command");
	}
}

void DoStopCommand(Model& model, int student_id)
{
	if (model.GetStudentPtr(student_id) != nullptr)
	{
		Student* student = model.GetStudentPtr(student_id);
		cout << "Stopping " << student->GetName() << endl;
		student->Stop();
	}
	else
	{
		throw Invalid_Input("Enter a valid command");
	}
}

void DoLearningCommand(Model& model, int student_id, unsigned int assignments)
{
	if (model.GetStudentPtr(student_id) != nullptr)
	{
		Student* student = model.GetStudentPtr(student_id);
		cout << "Teaching " << student->GetName() << endl;
		student->StartLearning(assignments);
	}
	else
	{
		
		throw Invalid_Input("Enter a valid command");
	}
}

void DoRecoverInOfficeCommand(Model& model, int student_id, unsigned int vaccine_needs)
{
	if (model.GetStudentPtr(student_id) != nullptr)
	{
		Student* student = model.GetStudentPtr(student_id);
		cout << "Recovering " << student->GetName() << "'s antibodies" << endl;
		student->StartRecoveringAntibodies(vaccine_needs);
	}
	else
	{
		throw Invalid_Input("Enter a valid command");
	}
}

void DoGoCommand(Model& model, View& view)
{
	cout << "Advancing one tick" << endl;
	model.Update();
	model.ShowStatus();
	model.Display(view);
}

void DoRunCommand(Model& model, View& view)
{
	cout << "Advancing to next event" << endl;
	int time_count = 0;
	while (!model.Update())
	{
		time_count++;
		if (time_count == 5)
			break;
	}
	model.ShowStatus();
	model.Display(view);
}
