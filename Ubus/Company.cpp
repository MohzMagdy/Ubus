#include "Company.h"

using namespace std;

Company::Company() {
	pUI = new UI();
	File_IO_Loading();
	AutopromotionNumber = 0;
	simulate();
}; // Default Constructor

Company::~Company() // Destructor
{ // TEMPORARY: Should delete all pointers in lists
	delete& pEvents;
}
bool Company::checkexitstatus() {
	return(
	pWaitVIP.isempty() &&
	pWaitSp.isempty() &&
	pWaitNorm.isempty() &&
	pDelivered.isempty() &&
	//pEmptyVIP.isempty() &&
	//pEmptySp.isempty() &&
	//pEmptyNorm.isempty() &&
	pMoving.isempty() &&
	pCheckupVIP.isempty() &&
	pCheckupSp.isempty() &&
	pCheckupNorm.isempty());
}


void Company::simulate()
{
	while (true)
	{
		Timestep = Timestep + 1;

		if (Isworkinghours()) {
			CheckAutopromotion();
		}

		/*ExecuteDeliveryFailure();*/
		/*deliver_passengers();*/
		


		if (checkexitstatus())
		{
			break;
		}
	}

	
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
	Autopromotionlimit = Time();
	Autopromotionlimit.Setdays(autoprom);
	Autopromotionlimit.Sethours(0);

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


void Company::maxqs()
{
	/*queue<Passengers*> tempsp = pWaitSp;
	LinkedList<Passengers*> tempnorm = pWaitNorm;
	Node<Passengers*>* sphead = tempsp.ReturnFront();
	while (sphead != NULL)
	{
		if (sphead->get_data()->Get_MaxW() == Timestep)
		{
			Passengers* helper = pWaitsp_find(sphead->get_data()->Get_ID());
			pWaitNorm_delete(helper);
			break;
		}
		sphead = sphead->get_next();
	}*/
}

void Company::CheckAutopromotion() {
	Node<Passengers*>* pHelper = pWaitNorm.get_head();
	while (pHelper!=NULL)
	{
		Passengers* pPass = pHelper->get_data();
		int totaltime = Timestep.Gettotalhours();
		int totalreadytime= pPass->Get_ready_Time().Gettotalhours();
		pHelper = pHelper->get_next();
		if ((totaltime - totalreadytime) > 0) {
			Time limt = (this->Timestep - pPass->Get_ready_Time());
			if (Autopromotionlimit < limt) {
				promoteNorm(pPass);
				cout << "the normal passanger with " << pPass->Get_ID() << " is auto promoted to vip"<<endl;
			}
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



//// delevier passengers not completed yet

//void Company::deliver_passengers() {
//	Buses*pBus = nullptr;
//	Passengers*pPass = nullptr ;
//
//	while (!pMoving.isempty())
//	{
//		pBus = pMoving.Dequeue();
//		pBus->passenger_peek(pPass); 
//		while (pPass!=nullptr)
//		{
//			int readytime = pPass->Get_ready_Time().Gettotalhours();
//			int nowtimestep = this->Timestep.Gettotalhours();
//			if (nowtimestep - readytime > 0) {
//				Time TimeFromStartTheJurnyUntillNow = (this->Timestep - pPass->Get_ready_Time());
//				double deliverytime = ((pPass->Get_Delivery_distance() / pBus->get_bus_speed()) +  (pPass->Get_totalRideUnride_Time()));
//				double TimeFromStartTheJurnyUntillNo = double (TimeFromStartTheJurnyUntillNow.Gettotalhours());
//
//				if (TimeFromStartTheJurnyUntillNo >= deliverytime)
//				{
//					pBus->passenger_Deqeue(pPass);
//					Passenger_Type PT = pPass->get_passanger_type();
//					switch (PT)
//					{
//					case VP:
//					pDeliveredVIP.Enqueue(pPass);
//						break;
//					case SP:
//						pDeliveredSp.Enqueue(pPass);
//						break;
//					case NP:
//						pDeliveredNorm.Enqueue(pPass);
//						break;
//					}
//				}
//			}
//			
//		}
//
//	}
//}




////////////////////  منيكة كود 
// 
//void Company::LoadVIP() {
//	Passengers* pPass = nullptr;
//	Buses* pBus = nullptr;
//	while (!pWaitVIP.isempty())
//	{
//		pPass = pWaitVIP.Dequeue();
//		pEmptyVIP.Peek(pBus);
//		pBus->passenger_aboard(pPass);
//	}
//}

//void Company::Setbustomovinglist() {
//
//pMoving.Enqueue(pEmptyVIP.Dequeue());
//pMoving.Enqueue(pEmptyVIP.Dequeue());
//
//;}



//// bouns Delivery failure

//void Company::ExecuteDeliveryFailure() {
//	double probability = 0; // probability of dropping a buses
//	int numtodrop = 0;
//
//	if (pMoving.getcounter() == 0) {
//		return;
//	}
//
//	if ((rand() % 100) < probability) {
//		numtodrop = rand() % this->pMoving.getcounter() + 1;
//		for (int i = 0; i < numtodrop; i++) {
//			this->DropBus();
//		}
//	}
//
//}
//void Company::DropBus() {
//
//	Buses* pBus;
//	pBus = pMoving.Dequeue();
//
//	Passengers* pPass = nullptr;
//	Bus_Type BT = pBus->get_bus_type();
//	switch (BT)
//	{
//	case VB:
//		pBus->passenger_Deqeue(pPass);
//		while (pPass!=nullptr) {this->pWaitVIP.Enqueue(pPass);}
//		break;
//	case SB:
//		pBus->passenger_Deqeue(pPass);
//		while (pPass != nullptr) {this->pWaitSp.Enqueue(pPass);}
//		break;
//	case NB:
//		pBus->passenger_Deqeue(pPass);
//		while (pPass != nullptr) {this->pWaitNorm.insert_end(pPass);}
//		break;
//	}
//	this->MoveToCheckUp(pBus);
//}
