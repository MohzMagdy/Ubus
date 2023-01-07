#include "Company.h"

using namespace std;

Company::Company() {
	pUI = new UI();
	File_IO_Loading();
}; // Default Constructor

Company::~Company() // Destructor
{ // TEMPORARY: Should delete all pointers in lists
	delete& pEvents;
}

// Add functions
void Company::add_event(Event* pEvent)
{
	pEvents.Enqueue(pEvent);
}

void Company::add_ready(Passengers* pPass)
{
	Passenger_Type PT = pPass->get_passanger_type();
	switch (PT)
	{
	case VP:
		pWaitVIP.Enqueue(pPass);
		break;
	case SP:
		pWaitSp.Enqueue(pPass);
		break;
	case NP:
		pWaitNorm.insert_end(pPass);
		break;
	}
}

void Company::add_empty_bus(Buses* pBus)
{
	Bus_Type BT = pBus->get_bus_type();
	switch (BT)
	{
	case VB:
		pEmptyVIP.Enqueue(pBus);
		break;
	case SB:
		pEmptySp.Enqueue(pBus);
		break;
	case NB:
		pEmptyNorm.Enqueue(pBus);
		break;
	}
}

// Functions
Passengers* Company::pWaitNorm_find(int ID)
{
	Node<Passengers*>* pHelper = pWaitNorm.get_head();
	int passenger_count = pWaitNorm.getcounter();

	for (int i = 0; i < passenger_count; i++)
	{
		Passengers* pPass = pHelper->get_data();
		if (pPass->Get_ID() == ID)
			return pPass;
	}
}

void Company::pWaitNorm_delete(Passengers* pPass)
{
	// Deleting waiting normal passenger
	pWaitNorm.delete_node(pPass);

	// Removes hanging pointer for deleted passenger from all events
	Event* pEvent;
	for (int i = 0; i < pEvents.getcounter(); i++)
	{
		pEvent = pEvents.Dequeue();
		if (pEvent->get_pPass() == pPass)
		{
			pEvent->set_pPass(nullptr);
		}
		pEvents.Enqueue(pEvent);
	}
}

void Company::promoteNorm(Passengers* pPass)
{
	pWaitNorm.delete_node(pPass);
	pWaitVIP.Enqueue(pPass);
}


// Loading File
void Company::File_IO_Loading() {
	/*ifstream File;
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
	loadedData = new string[dataElementsCount];
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
	Autopromotionlimit.Setdays(stoi(loadedData[13])); Autopromotionlimit.Sethours(0);
	Buses** nBuses = new Buses * [stoi(loadedData[0])];
	Buses** sBuses = new Buses * [stoi(loadedData[1])];
	Buses** vBuses = new Buses * [stoi(loadedData[2])];
	for (int i = 0; i <= stoi(loadedData[0]); i++) {
		nBuses[i] = new Buses(NB, stoi(loadedData[6]), stod(loadedData[12]), stod(loadedData[3]), 4);
		add_empty_bus(nBuses[i]);
	}
	for (int i = 0; i <= stoi(loadedData[1]); i++) {
		sBuses[i] = new Buses(SB, stoi(loadedData[7]), stod(loadedData[13]), stod(loadedData[4]), 4);
		add_empty_bus(sBuses[i]);
	}
	for (int i = 0; i <= stoi(loadedData[2]); i++) {
		vBuses[i] = new Buses(VB, stoi(loadedData[8]), stod(loadedData[14]), stod(loadedData[5]), 4);
		add_empty_bus(vBuses[i]);
	}
	int numEvents = stoi(loadedData[15]);
	int i = 15;
	while (i < dataElementsCount - 1) {
		if (loadedData[i + 1] == "R") {
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
			int colonidx = 0;
			for (int j = 0; j < loadedData[i + 3].size(); j++) {
				if (loadedData[i + 3][j] == ':') {
					colonidx = j;
				}
			}
			int pDay = stoi(loadedData[i + 3].substr(0, colonidx));
			int pHour = stoi(loadedData[i + 3].substr(colonidx + 1, loadedData[i + 3].size() - colonidx));
			int id = stoi(loadedData[i + 4]);
			double distance = stod(loadedData[i + 5]);
			double LT = stod(loadedData[i + 6]);
			double cost = stod(loadedData[i + 7]);
			ReadyEvent* e = new ReadyEvent(this, pType, pDay, pHour, id, LT, distance, cost);
			add_event(e);
			cout << "Current Time: " << pDay << ":" << pHour << endl;
			cout << "Added a Ready Event" << endl;
			i += 7;
		}
		else if (loadedData[i + 1] == "X") {
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
	}*/
	ifstream File;
	File.open("input.txt");
	int noNbus, noSbus, noVbus;
	File >> noNbus >> noSbus >> noVbus;
	int sNBus, sSBus, sVBus;
	File >> sNBus >> sSBus >> sVBus;
	int cNBus, cSBus, cVBus;
	File >> cNBus >> cSBus >> cVBus;

	int noCheckup, cdNBus, cdSBus, cdVBus;

	File >> noCheckup >> cdNBus >> cdSBus >> cdVBus;
	
	int autoprom, maxW;

	File >> autoprom >> maxW;

	

	for (int i = 0; i < noNbus; i++) {
		Buses* n = new Buses(Bus_Type::NB, cNBus, Time(cdNBus), sNBus, i);
		add_empty_bus(n);
	}
	for (int i = 0; i < noSbus; i++) {
		Buses* n = new Buses(Bus_Type::SB, cSBus, Time(cdSBus), sSBus, i);
		add_empty_bus(n);
	}
	for (int i = 0; i < noVbus; i++) {
		Buses* n = new Buses(Bus_Type::VB, cVBus, Time(cdVBus), sVBus, i);
		add_empty_bus(n);
	}
	autoPromotion = Time();
	autoPromotion.Setdays(autoprom);
	autoPromotion.Sethours(0);

	MaxW = Time(maxW);
	int numEvents;

	File >> numEvents;

	for (int i = 0; i < numEvents; i++) {
		char EventType;
		File >> EventType;
		if (EventType == 'R') {
			ReadyEvent* R = new ReadyEvent(this);
			R->Load(File);
		}
		else if(EventType == 'P') {
			PromoteEvent* P = new PromoteEvent(this);
			P->Load(File);
		}
		else {
			CancelEvent* C = new CancelEvent(this);
			C->Load(File);
		}
	}
}

void Company::simulate()
{
	while (true)
	{
		Timestep = Timestep + 1;

	}
}

void Company::maxqs()
{
	priority_queue<Passengers*> tempvip = pWaitVIP;
	queue<Passengers*> tempsp = pWaitSp;
	LinkedList<Passengers*> tempnorm = pWaitNorm;
	while (tempvip.isempty()!=true)
	{
		Passengers* helpertoday=tempvip.Dequeue();
		if (helpertoday->Get_MaxW()==Timestep)
		{
			helpertoday;
		}
	}
}

void Company::CheckAutopromotion() {
	Node<Passengers*>* pHelper = pWaitNorm.get_head();
	int passenger_count = pWaitNorm.getcounter();
	while (pHelper!=NULL)
	{
		Passengers* pPass = pHelper->get_data();
		Time limt = (this->Timestep.operator-(pPass->Get_ready_Time()));
		if (Autopromotionlimit <= limt) {
			promoteNorm(pPass);
			AutopromotionNumber++;
		}
	}
}

bool Company::Isworkinghours()
{
	if (this->Timestep.operator>=(Time(Timestep.Getdays(), 4)) &&
		this->Timestep.operator<=(Time(Timestep.Getdays(), 22)))
	{
		return true;
	}
	else { return false; }
}