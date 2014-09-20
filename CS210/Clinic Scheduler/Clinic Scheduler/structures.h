#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

const int numberOfRooms = 100;


bool isSpecialty(string request);		/*used to help with user input and matching specialtys
					PRE - none. POST - returns T/F depending on iff the request value is a valid specialty
	valid specialties are: PED, GP, INT, CAR, SUR, OBS, PSY, NEU, ORT, DET, OPT, ENT and for patients only NP(No preference)				
*/
class doctor
{
private:
	string name;
	string doctorSpecialty;
	int roomNumber;
public:
	doctor();
	void doctorCheckin();			//Pre - nothing. POST - doctor struct will have all information populated and ready for use. This function gathers all relevant information
	string getSpecialty();			//PRE - init class. POST - returns the doctors specialty	
	int getRoom();					//PRE - init class. POST - returns the doctors room
	void setRoom(int roomNumber);	//PRE - init class. POST - sets the doctors room to the room number passed into the function.
};

class patient
{
private:
	string name;
	int age;
	string requestedSpecialty;
	int roomNumber;
	bool isEmergency;
public:
	patient();
	void patientCheckin();				//Pre - nothing. POST - patient struct will have all relevant information populated
	string getRequestedSpecialty();		//PRE - nothing. POST - returns the patients requested specialty
	int getAge();						//PRE - nothing. POST - returns the patients age
	void setRoom(int number);			//PRE - nothing. POST - sets the patients room to the number passed into the function
	int getRoomNumber();				//PRE - nothing. POST - returns the patients room number.
	bool getEmergency();				//PRE - nothing. POST - returns if the patients case is an emergency or not
};


class room
{
private:
	doctor residingDoctor;
	patient residingPatient;
	bool isFull;							//if room currently has a doctor in it.
	bool hasPatient;						//if the room has a patient in it.
protected:
	void removePatient();					//PRE - nothing. POST - rooms hasPatient variable set to false
	void removeDoctor();					//PRE - nothing. POST - removes the doctor from the room. If there are any queue'd patients, they are re-allocated to other rooms
	queue<patient> patientQueue;		
	queue<patient> emergencyQueue;
public:
	room();
	void assignDoctor(doctor toAssign);		//Pre - none. POST - toAssign doctor is residing in the room. Room is marked as full
	void assignPatient(patient toAssign);	//PRE - none. POST - toAssign doctor is either in the exam room, or the queue, depending on if there is a patient in the exam room and if its an emergency or not(regular or emergency queue)
	void addToQueue(patient add);			//PRE - init queue. POST - adds patient add to the regular queue
	void addToEmergency(patient add);		//PRE - init queue. POST - adds patient add to the emergency queue
	doctor getDoctor();						//PRE - room has doctor. POST - doctor is returned
	bool getIsFull();						//PRE - none. POST - returns if room has a doctor in it
	bool getHasPatient();					//PRE - none. POST - returns if the room has a patient in it
	int getQueueSize();						//returns # of patients in the queue's combined.
	patient getNextPatient();				//returns patient at front of regular queue
	friend class scheduler;
};



#endif
