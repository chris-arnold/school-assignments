#include <iostream>
#include "scheduler.h"

using namespace std;

scheduler::scheduler()
{
};

int scheduler::placeDoctor(doctor docname)
{
	int requestedRoom = docname.getRoom();
	int givenRoom = requestedRoom;
	if(clinic[requestedRoom].getIsFull())		//if requested room is full, alert user..
	{
		cout << "Requested room is full. " << endl;
		int i = 0;
		while(clinic[i].getIsFull())			//find first available room
		{
			i++;
			if(i == 100)		//if this evaluated to true, every room has come back as full, doctor cannot be placed.
			{
				cout << "All exam rooms are full. Doctor could not be placed. " << endl;
				return -1;
			}
		}
		givenRoom = i;
	}
	else			//otherwise the doctors requested room was empty, assign to that room
	{
		givenRoom = requestedRoom;
	}
	docname.setRoom(givenRoom);						//set doctor to his room.
	clinic[givenRoom].assignDoctor(docname);		//assign doctor to his room
	cout << "The doctor has been assigned to room " << givenRoom << ". " << endl;		//let user know where the doctor was assigned.
	return givenRoom;
};

int scheduler::placePatient(patient patname)
{
	queue<int> possibleMatches;
	string type;
	int smallestroom = 0;
	int smallestqueue = 10000;
	if(patname.getAge() < 16)			//if patient is under 16, search for a PED first.
		type = "PED";
	else								//otherwise search for desired type first.
		type = patname.getRequestedSpecialty();
	for(int i = 0; i < numberOfRooms; i++)
	{
		if(clinic[i].getDoctor().getSpecialty() == type && clinic[i].getIsFull())
		{
			possibleMatches.enqueue(i);
		}
	}
	if(possibleMatches.empty())		//no PED found. Search for GP
	{
		type = "GP";
		for(int i = 0; i < numberOfRooms; i++)
		{
			if(clinic[i].getDoctor().getSpecialty() == type && clinic[i].getIsFull())
			{
				possibleMatches.enqueue(i);
			}
		}
		if(possibleMatches.empty())		//No GP's found find shortest queue and add to.
		{
			for(int i = 0; i < numberOfRooms; i++)
			{
				if(clinic[i].getIsFull())		//if room is occupied, its a possible match
				{
					possibleMatches.enqueue(i);
				}
			}
			if(possibleMatches.empty())			//if there are no matches here, there are no doctors.
			{
				cout << "There are no doctors currently checked in. " << endl;
				return -1;
			}
			else{}	//drop down to final else
		}
		else{}
	}
	else	//matches found, need to find possible match with the smallest queue
	{}
	while(!possibleMatches.empty())			//cycles through possible matches, finding the one with the smallest queue.
	{
		int frontValue = possibleMatches.getFrontData();
		if(clinic[frontValue].getQueueSize() < smallestqueue)
			smallestroom = frontValue;
		possibleMatches.dequeue();
	}
	if(patname.getEmergency())			//if its an emergency, place in the emergency queue of the smallest wait time room.
	{
		patname.setRoom(smallestroom);
		clinic[smallestroom].addToEmergency(patname);
	}
	else								//else add to the queue of the smallest length
	{
		patname.setRoom(smallestroom);
		clinic[smallestroom].addToQueue(patname);
	}
	cout << "Patient was successfully assigned to room " << smallestroom << endl;
	return smallestroom;		//if here patient was successfully matched to a room.
};

bool scheduler::fillRoom(int roomNumber)		//takes patient from appropriate queue and places into room
{
	if(clinic[roomNumber].getHasPatient())		//if room has patient
	{
		cout << "Room is full. Could not place patient in room from queue. " << endl;
		return false;
	}
	else			//room does not have a patient in it.
	{
		if(!clinic[roomNumber].emergencyQueue.empty())		//someone in emergency queue
		{
			clinic[roomNumber].assignPatient(clinic[roomNumber].emergencyQueue.getFrontData());		//get person from queue and place into the room
			clinic[roomNumber].emergencyQueue.dequeue();		//remove that person from the queue
			return true;										//room has been filled, return true
		}
		else if(!clinic[roomNumber].patientQueue.empty())	//someone in regular queue
		{
			clinic[roomNumber].assignPatient(clinic[roomNumber].patientQueue.getFrontData());		//assign person from queue to room
			clinic[roomNumber].patientQueue.dequeue();			//remove person from queue
			return true;										//room has been filled, return true
		}
		else				//no patient in room and no patients in queue
		{
			cout << "Room is empty, queue is empty! " << endl;
			return false;
		}
	}
};

void scheduler::patientCheckout(int room)			//simply removes the patient from the exam room, making it available for use.
{
	clinic[room].removePatient();	//removes patient from his/her room	
};

bool scheduler::doctorCheckout(int room)
{
	//bool success = false;
	if(clinic[room].getQueueSize() == 0)		//no one in queue. Just free the room.
	{
		clinic[room].removeDoctor();
		return true;
	}
	else		//people in queue. Find them new queue's
	{
		clinic[room].removeDoctor();			//remove doctor from room so to not interfere with replacement
		int assignedRoom = -1;
		while(clinic[room].getQueueSize() != 0)		//will loop until queue's are empty. First emptying regular queue, then emergency.
		{
			if(!clinic[room].patientQueue.empty())
			{
				assignedRoom = placePatient(clinic[room].patientQueue.getFrontData());		//find patient a new queue (regular queue)
				if(assignedRoom <= 0 || assignedRoom > numberOfRooms)		//if placing patient is unsuccessful, this loop needs to exit as there are no available rooms and the patients will never get a new room
				{
					cout << "Warning, patients could not be re-assigned as no waiting rooms could be found. " << endl;
					return false;
				}
				clinic[room].patientQueue.dequeue();							//remove from initial queue
			}
			else
			{
				assignedRoom = placePatient(clinic[room].emergencyQueue.getFrontData());		//find patient a new queue (emergency queue)
				if(assignedRoom <= 0 || assignedRoom > numberOfRooms)
				{
					cout << "Warning, patients could not be re-assigned as no waiting rooms could be found. " << endl;
					return false;
				}
				clinic[room].emergencyQueue.dequeue();							//remove from initial queue
			}
		}
		return true;
	}
};

