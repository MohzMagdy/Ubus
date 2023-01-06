#pragma once
#include "LinkedList.h"
#include "queue.h"
#include "Passengers.h"
#include "Buses.h"
#include "Event.h"
#include "Defs.h"
#include "ReadyEvent.h"
#include "PromoteEvent.h"
#include "CancelEvent.h"
#include "UI.h"
#include <sstream>
#include <string>
#include <fstream>


class Company {
private:
	queue<Event*> pEvents;
	queue<Passengers*> pPassengers;
	queue<Buses*> pBuses;
	UI* pUI;
	int event_count = 0;
	int passenger_count = 0;
	int bus_count = 0;

public:
	Company() {
		pUI = new UI();
		File_IO_Loading();
	}; // Default Constructor
	~Company() // Destructor
	{ // TEMPORARY: Should delete all pointers in lists
		delete &pEvents;
		delete &pPassengers;
		delete &pBuses;
	}

	// Getters
	int get_passenger_count()
	{
		return passenger_count;
	}

	// Add functions
	void add_event(Event* pEvent)
	{
		pEvents.Enqueue(pEvent);
		event_count++;
	}

	void add_passenger(Passengers* pPass)
	{
		pPassengers.Enqueue(pPass);
		passenger_count++;
	}

	void add_bus(Buses* pBus)
	{
		pBuses.Enqueue(pBus);
		bus_count++;
	}

	// Functions
	Passengers* find_passenger(int ID) // Returns pointer of passenger with given ID
	{
		bool found = false;
		Passengers* pPass = nullptr;
		Passengers* pHelper;
		for (int i = 0; i < passenger_count; i++) // Loop goes over whole queue to keep the order unchanged
		{
			pHelper = pPassengers.Dequeue();
			if (!found && pHelper->Get_ID() == ID)
			{
				pPass = pHelper;
				found = true;
				
			}
			pPassengers.Enqueue(pHelper);
		}

		return pPass;
	}

	void delete_passenger(Passengers* pPass) 	
	{
		// Deleting passenger from passengers queue by dequeuing it
		bool found = false;
		Passengers* pHelper;

		for (int i = 0; i < passenger_count; i++) // Loop goes over whole queue to keep the order unchanged
		{
			pHelper = pPassengers.Dequeue();
			if (!found && pHelper == pPass)
			{
				delete pHelper;
				found = true;
			}
			else
			{
				pPassengers.Enqueue(pHelper);
			}
		}
		if(found) passenger_count--;

		// Removes hanging pointer for deleted passenger from all events
		Event* pEvent;
		for (int i = 0; i < event_count; i++) 
		{
			pEvent = pEvents.Dequeue();
			if (pEvent->get_pPass() == pPass) 
			{
				pEvent->set_pPass(nullptr); 
			}
			pEvents.Enqueue(pEvent);
		}
	}

	void Enqueue_passenger(Passengers* pPass)
	{
		pPassengers.Enqueue(pPass);
	}

	Passengers* Dequeue_passenger()
	{
		return pPassengers.Dequeue();
	}
	void File_IO_Loading() {
		ifstream File;
		string dataline;
		int dataElementsCount = 0;
		File.open("input.txt");
		while (getline(File, dataline)) {
			stringstream streamData(dataline);
			string dataelement;
			while (getline(streamData, dataelement, ' ')) {
				dataElementsCount += 1;
			}
		}
		string* loadedData;
		loadedData	= new string[dataElementsCount];
		File.close();
		ifstream FileLoader;
		FileLoader.open("input.txt");
		int index = 0;
		while (getline(FileLoader, dataline)) {
			stringstream streamData(dataline);
			string dataelement;
			while (getline(streamData, dataelement, ' ')) {
				loadedData[index] = dataelement;
				index += 1;
			}
		}

		Buses** nBuses = new Buses*[stoi(loadedData[0])];
		Buses** sBuses = new Buses*[stoi(loadedData[1])];
		Buses** vBuses = new Buses*[stoi(loadedData[2])];
		for (int i = 0; i <= stoi(loadedData[0]); i++) {
			nBuses[i] = new Buses(NB, stoi(loadedData[6]), stod(loadedData[12]), stod(loadedData[3]), 4);
			add_bus(nBuses[i]);
		}
		for (int i = 0; i <= stoi(loadedData[1]); i++) {
			sBuses[i] = new Buses(SB, stoi(loadedData[7]), stod(loadedData[13]), stod(loadedData[4]), 4);
			add_bus(sBuses[i]);
		}
		for (int i = 0; i <= stoi(loadedData[2]); i++) {
			vBuses[i] = new Buses(VB, stoi(loadedData[8]), stod(loadedData[14]), stod(loadedData[5]), 4);
			add_bus(vBuses[i]);
		}
		int numEvents = stoi(loadedData[15]);
		int i = 15;
		while (i<dataElementsCount-1) {
			if (loadedData[i+1] == "R") {
				Passenger_Type pType;
				if (loadedData[i + 2] == "N") {
					pType = Passenger_Type::NP;
				}
				else if (loadedData[i + 2] == "S") {
					pType = Passenger_Type::SP;
				}
				else {
					pType = Passenger_Type::VP;
				}
				int colonidx=0;
				for (int j = 0; j < loadedData[i + 3].size(); j++) {
					if (loadedData[i + 3][j] == ':') {
						colonidx = j;
					}
				}
				int pDay = stoi(loadedData[i+3].substr(0,colonidx));
				int pHour = stoi(loadedData[i + 3].substr(colonidx+1, loadedData[i+3].size()-colonidx));
				int id = stoi(loadedData[i + 4]);
				double distance = stod(loadedData[i + 5]);
				double LT = stod(loadedData[i + 6]);
				double cost = stod(loadedData[i + 7]);
				ReadyEvent* e = new ReadyEvent(this, pType, pDay,pHour, id, LT, distance, cost);
				add_event(e);
				cout << "Current Time: " << pDay << ":" << pHour << endl;
				cout << "Added a Ready Event" << endl;
				i += 7;
			}
			else if (loadedData[i+1] == "X") {
				int colonidx = 0;
				for (int j = 0; j < loadedData[i + 2].size(); j++) {
					if (loadedData[i + 2][j] == ':') {
						colonidx = j;
					}
				}
				int pDay = stoi(loadedData[i + 2].substr(0, colonidx));
				int pHour = stoi(loadedData[i + 2].substr(colonidx + 1, loadedData[i + 2].size() - colonidx));
				int id = stoi(loadedData[i + 3]);
				cout << "Current Time: " << pDay << ":" << pHour << endl;
				CancelEvent* c = new CancelEvent(this, id);
				add_event(c);
				i += 3;
			}
			else {
				int colonidx = 0;
				for (int j = 0; j < loadedData[i + 2].size(); j++) {
					if (loadedData[i + 2][j] == ':') {
						colonidx = j;
					}
				}
				int pDay = stoi(loadedData[i + 2].substr(0, colonidx));
				int pHour = stoi(loadedData[i + 2].substr(colonidx + 1, loadedData[i + 2].size() - colonidx));
				int id = stoi(loadedData[i + 3]);
				double extraMoney = stod(loadedData[i + 4]);
				cout << "Current Time: " << pDay << ":" << pHour << endl;
				PromoteEvent* p = new PromoteEvent(this, id);
				add_event(p);
				i += 4;
			}
		}
	}
};
