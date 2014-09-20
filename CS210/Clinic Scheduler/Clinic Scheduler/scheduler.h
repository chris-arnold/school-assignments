#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <iostream>
#include "structures.h"

using namespace std;

class scheduler
{
private:
	room clinic[numberOfRooms];
public:
	scheduler();
	int placeDoctor(doctor docname);		//Pre - Rooms initialized, doctor initialized. POST - Doctor is assigned to a room. returns if successful
	int placePatient(patient patname);		//Pre - Rooms initialized, patient initialized. At least one doctor checked in. POST - Patient is assigned to a room or queue. Return if successful

	bool fillRoom(int roomNumber);			//Pre - Rooms initialized. Has doctor & patient queue. POST - if room filling successfull. Decides who's next into the room(emerg queue or regular)
	bool doctorCheckout(int room);	//Pre - Rooms & doctor initialized. POST - doctor is checked out. His room is empty, any waiting patients re-allocoated to other waiting rooms.

	void patientCheckout(int room);	//PRE - Rooms and patient init. POST - patient is checked out of room

};


#endif