CC=g++ -g -std=c++11

OBJS=main.o Building.o Point2D.o Vector2D.o GameObject.o GameCommand.o DoctorsOffice.o Model.o Student.o ClassRoom.o View.o Virus.o

default: PA4

PA4: $(OBJS)
	$(CC) -o PA4 $(OBJS) 

Vector2D.o: Vector2D.cpp Vector2D.h
	$(CC) -c Vector2D.cpp -o Vector2D.o 
	
Point2D.o: Point2D.cpp Point2D.h Vector2D.h
	$(CC) -c Point2D.cpp -o Point2D.o 

Building.o: Building.cpp Building.h
	$(CC) -c Building.cpp -o Building.o

GameObject.o: GameObject.cpp GameObject.h Point2D.h Vector2D.h
	$(CC) -c GameObject.cpp -o GameObject.o 

DoctorsOffice.o: DoctorsOffice.cpp DoctorsOffice.h GameObject.h Point2D.h
	$(CC) -c DoctorsOffice.cpp -o DoctorsOffice.o

Model.o: Model.cpp Model.h GameObject.h Input_Handling.h Student.h ClassRoom.h DoctorsOffice.h View.h
	$(CC) -c Model.cpp -o Model.o 

ClassRoom.o: ClassRoom.cpp ClassRoom.h GameObject.h Point2D.h
	$(CC) -c ClassRoom.cpp -o ClassRoom.o

View.o: View.cpp View.h GameObject.h Point2D.h
	$(CC) -c View.cpp -o View.o 

Student.o: Student.cpp Student.h GameObject.h Point2D.h Vector2D.h DoctorsOffice.h ClassRoom.h
	$(CC) -c Student.cpp -o Student.o

GameCommand.o: GameCommand.cpp GameCommand.h Input_Handling.h Model.h GameObject.h Student.h ClassRoom.h DoctorsOffice.h
	$(CC) -c GameCommand.cpp -o GameCommand.o

Virus.o: Virus.cpp Virus.h GameObject.h Student.h Point2D.h Vector2D.h
	$(CC) -c Virus.cpp -o Virus.o

main.o: main.cpp Building.h Virus.h Point2D.h Input_Handling.h Vector2D.h GameCommand.h DoctorsOffice.h Model.h Student.h ClassRoom.h GameObject.h View.h
	$(CC) -c main.cpp -o main.o

#checkpoint commands below

PA4: main.o Point2D.o Vector2D.o GameObject.o Building.o DoctorsOffice.o ClassRoom.o Student.o View.o Model.o GameCommand.o Virus.o
	$(CC) -o PA4.exe main.o Point2D.o Vector2D.o GameObject.o Building.o DoctorsOffice.o ClassRoom.o Student.o View.o Model.o GameCommand.o Virus.o

#add your own tests for other checkpoints here
	
clean: 
	rm $(OBJS) PA4 *.exe

