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
	pCheckupNorm.isempty()) &&
	pEvents.isempty();
}


void Company::simulate()
{
	while (true)
	{
		prioequation();
		Timestep = Timestep + 1;

		if (Isworkinghours()) {
			ExecuteAvailableEvent();
			boardPassengers();
			CheckAutopromotion();
			/*Timestep = 0; */
			//maxqs();
		}
		
		/*ExecuteDeliveryFailure();*/
		/*deliver_passengers();*/
		

		PrintInteractiveModeData();
		if (checkexitstatus())
		{
			break;
		}
		/*increaseMaxWforall();*/ /// Tifa IDK how your code works tbh :D
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
		pWaitVIP.Enqueue(pPass, pPass->calcPriority());
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
	pWaitVIP.Enqueue(pPass, pPass->calcPriority());
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
		Buses* n = new Buses(Bus_Type::NB, cNBus, Time(cdNBus), sNBus, i,5,i+1); ///MUST BE CHANGED TO BUS SIZE
		add_empty_bus(n);
	}
	for (int i = 0; i < noSbus; i++) {
		Buses* n = new Buses(Bus_Type::SB, cSBus, Time(cdSBus), sSBus, i,5,i+1); ///MUST BE CHANGED TO BUS SIZE
		add_empty_bus(n);
	}
	for (int i = 0; i < noVbus; i++) {
		Buses* n = new Buses(Bus_Type::VB, cVBus, Time(cdVBus), sVBus, i,5,i+1); ///MUST BE CHANGED TO BUS SIZE
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
			add_event(R);
		}
		else if(EventType == 'P') {
			PromoteEvent* P = new PromoteEvent(this);
			P->Load(File);
			add_event(P);
		}
		else {
			CancelEvent* C = new CancelEvent(this);
			C->Load(File);
			add_event(C);
		}
	}
}


void Company::maxqs()
{
	queue<Passengers*> tempsp = pWaitSp;
	LinkedList<Passengers*> tempnorm = pWaitNorm;
	Node<Passengers*>* sphead = tempsp.ReturnFront();
	Node<Passengers*>* norhead = tempnorm.get_head();
	while (sphead != nullptr)
	{
		if (sphead->get_data()->Get_MaxW() == Timestep)
		{
			Node<Buses*>* assistant=pEmptySp.ReturnFront();
			if (assistant->get_data()->isfull() == false)
			{
				assistant->get_data()->passenger_aboard(sphead->get_data());
				cout << "Passenger with ID " << sphead->get_data()->Get_ID() << " Aboarded the bus " << endl;
				break;
			}
			else
			{
				while (assistant->get_data()->isfull()==true && assistant->get_next()!=nullptr)
				{
					assistant = assistant->get_next();
				}
				if (assistant->get_data()->isfull()==true)
				{
					cout << "No bus is available" << endl;
				}
				else
				{
					assistant->get_data()->passenger_aboard(sphead->get_data());
					cout << "Passenger with ID " << sphead->get_data()->Get_ID() << " Aboarded the bus " << endl;
					break;
				}
				
			}
		}
		sphead = sphead->get_next();
	}
	while (norhead != nullptr)
	{
		if (norhead->get_data()->Get_MaxW() == Timestep)
		{
			Node<Buses*>* assistant = pEmptyNorm.ReturnFront();
			if (assistant->get_data()->isfull() == false)
			{
				assistant->get_data()->passenger_aboard(norhead->get_data());
				cout << "Passenger with ID " << norhead->get_data()->Get_ID() << " Aboarded the bus " << endl;
				break;
			}
			else
			{
				while (assistant->get_data()->isfull() == true && assistant->get_next() != nullptr)
				{
					assistant = assistant->get_next();
				}
				if (assistant->get_data()->isfull() == true)
				{
					cout << "No bus is available" << endl;
				}
				else
				{
					assistant->get_data()->passenger_aboard(norhead->get_data());
					cout << "Passenger with ID " << norhead->get_data()->Get_ID() << " Aboarded the bus " << endl;
					break;
				}

			}
		}
		norhead = norhead->get_next();
	}
}


void Company::CheckAutopromotion() {
	Node<Passengers*>* pHelper = pWaitNorm.get_head();
	while (pHelper != NULL)
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

void Company::increaseMaxWforall()
{
	Node<Passengers*>* pHelperNor = pWaitNorm.get_head();
	Node<Passengers*>* pHelpersp = pWaitSp.ReturnFront();
	while (pHelperNor!=nullptr)
	{
		pHelperNor->get_data()->increaseMaxwhr();
		pHelperNor = pHelperNor->get_next();
	}
	while (pHelpersp!=nullptr)
	{
		pHelpersp->get_data()->increaseMaxwhr();
		pHelpersp = pHelpersp->get_next();
	}
}

void Company::prioequation()
{
	Node<Passengers*>* Helper = pWaitVIP.ReturnFront();
	priority_queue<Passengers*> clone;
	while (Helper!=nullptr)
	{
		Helper->set_priority((1 / Helper->get_data()->Get_Delivery_distance())+(1/Helper->get_data()->Get_ready_Time().Gettotalhours())+Helper->get_data()->Get_Cost());
		clone.Enqueue(Helper);
		Helper = Helper->get_next();
	}
	pWaitVIP = clone;
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
//
//void Company::MoveBuses() {
//	Buses* possibleBus = nullptr;
//
//	pEmptyNorm.Peek(possibleBus);
//	if (possibleBus != nullptr) {
//		if (possibleBus->isfull()) {
//			possibleBus = pEmptyNorm.Dequeue();
//			possibleBus->Set_Start_Moving_Time(Timestep);
//			pMoving.Enqueue(possibleBus, possibleBus->GetTruckPriority());
//		}
//	}
//
//	this->SpecialTrucksList->peek(checkingTruck);
//	if (checkingTruck != nullptr) {
//		if (checkingTruck->IsLoaded()) {
//			SpecialTrucksList->dequeue(checkingTruck);
//			checkingTruck->SetLoading(false);
//			checkingTruck->SetMovingStartTime(TimestepNum);
//			checkingTruck->UpdateTruckPriority();
//			MovingTrucks->enqueue(checkingTruck, checkingTruck->GetTruckPriority());
//		}
//	}
//
//	this->VIPTrucksList->peek(checkingTruck);
//	if (checkingTruck != nullptr) {
//		if (checkingTruck->IsLoaded()) {
//			VIPTrucksList->dequeue(checkingTruck);
//			checkingTruck->SetLoading(false);
//			checkingTruck->SetMovingStartTime(TimestepNum);
//			checkingTruck->UpdateTruckPriority();
//			MovingTrucks->enqueue(checkingTruck, checkingTruck->GetTruckPriority());
//		}
//	}
//}

bool Company::ExecuteAvailableEvent() {
	bool EventExists = false;
	Event* tempEvent;
	pEvents.Peek(tempEvent);
	if (tempEvent != nullptr) {
		if (tempEvent->getEventTime() <= Timestep) {
			tempEvent = pEvents.Dequeue();
			tempEvent->Execute();
			delete tempEvent;
			return true;
		}
	}
	else {
		return false;
	}
}

void Company::PrintInteractiveModeData() {
	string InteractiveModeData = "";
	InteractiveModeData += "Current Time(Day:Hour) : " + to_string(Timestep.Getdays()) + ":" + to_string(Timestep.Gethours()) + "\n";
	string lineSeperator = "\n-----------------------------------------\n";
	int WaitingPassengers, RidingBuses, EmptyBususCount, MovingPassengers, InCheckUpBuses, DeliveredPassengers;
	WaitingPassengers = pWaitNorm.getcounter() + pWaitSp.getcounter() + pWaitVIP.getcounter();
	InteractiveModeData += to_string(WaitingPassengers) + " Waiting passengers: [ " + pWaitNorm.getInsideIDs() + " ] (" + pWaitSp.getInsideIDs() + ") {" + pWaitVIP.getInsideIDs() + "}" + lineSeperator;
	string RidingBusData = "";
	int countRidingBuses = 0;
	int countRidingBusesNormal = 0;
	int countRidingBusesSp = 0;
	int countRidingBusesVIP = 0;
	//countRidingBuses = checkQueueFront(pEmptyVIP) + checkQueueFront(pEmptySp) + checkQueueFront(pEmptyNorm);
	//RidingBusData += to_string(countRidingBuses) + " Riding Buses: ";
	//RidingBusData += checkBusFrontID(pEmptyNorm) + " " + checkBusFrontID(pEmptySp);
	Buses* TempBus;
	//string RidingBusData = "";
	
	pEmptyNorm.Peek(TempBus);
	if (TempBus) {
		if (pWaitNorm.getcounter() != 0) {
			RidingBusData += "[" +  to_string(TempBus->getID()) + "] ";
			countRidingBusesNormal += 1;
		}
	}

	pEmptySp.Peek(TempBus);
	if (TempBus) {
		if (pWaitSp.getcounter() != 0) {
			RidingBusData += "(" + to_string(TempBus->getID()) + ") ";
			countRidingBusesSp += 1;
		}
	}

	pEmptyVIP.Peek(TempBus);
	if (TempBus) {
		if (pWaitVIP.getcounter() != 0) {
			RidingBusData += "{ " + to_string(TempBus->getID()) + "} ";
			countRidingBusesVIP += 1;
		}
	}
	countRidingBuses = countRidingBusesNormal + countRidingBusesSp + countRidingBusesVIP;
	InteractiveModeData += to_string(countRidingBuses) + " Loading Trucks: " + RidingBusData + lineSeperator;

	string EmptyBuses = "";
	EmptyBususCount = pEmptyNorm.getcounter() + pEmptySp.getcounter() + pEmptyVIP.getcounter() - countRidingBuses;
	string IDsEmptyNormal = pEmptyNorm.getInsideIDsExceptFirst();
	string IDsEmptySp = pEmptySp.getInsideIDsExceptFirst();
	string IDsEmptyVIP = pEmptyVIP.getInsideIDsExceptFirst();

	for (int i = 0; i < IDsEmptyNormal.size(); i++) {
		if (i == 0 && countRidingBusesNormal != 0) { continue; }
		EmptyBuses += "[" + to_string(IDsEmptyNormal[i]-48) + "] ";
	}
	for (int i = 0; i < IDsEmptySp.size(); i++) {
		if (i == 0 && countRidingBusesSp != 0) { continue; }
		EmptyBuses += "(" + to_string(IDsEmptySp[i]-48) + ") ";
	}

	for (int i = 0; i < IDsEmptyVIP.size(); i++) {
		if (i == 0 && countRidingBusesVIP != 0) { continue; }
		EmptyBuses += "{" + to_string(IDsEmptyVIP[i]-48) + "} ";
	}
	InteractiveModeData += to_string(EmptyBususCount) + " Empty Buses: " + EmptyBuses + lineSeperator;

	string MovingPassengersString;

	int MovingPassengersCount = 0;
	Buses** MovingBussesPointers = pMoving.getInsidePointers();
	for (int i = 0; i < pMoving.getcounter(); i++) {
		MovingPassengersCount += MovingBussesPointers[i]->getSeats().getcounter();
		if (MovingBussesPointers[i]->get_bus_type() == Bus_Type::NB) {
			MovingPassengersString += to_string(MovingBussesPointers[i]->getID());
			MovingPassengersString += "[ " + MovingBussesPointers[i]->getSeats().getInsideIDs() + "] ";
		}
		if (MovingBussesPointers[i]->get_bus_type() == Bus_Type::SB) {
			MovingPassengersString += to_string(MovingBussesPointers[i]->getID());
			MovingPassengersString += "( " + MovingBussesPointers[i]->getSeats().getInsideIDs() + ") ";
		}
		if (MovingBussesPointers[i]->get_bus_type() == Bus_Type::VB) {
			MovingPassengersString += to_string(MovingBussesPointers[i]->getID());
			MovingPassengersString += "{ " + MovingBussesPointers[i]->getSeats().getInsideIDs() + "} ";
		}
	}
	string FinalMovingPassengers;
	FinalMovingPassengers += to_string(MovingPassengersCount) + " Moving Passengers: " + MovingPassengersString;
	InteractiveModeData += FinalMovingPassengers + lineSeperator;

	string InCheckupBusses = "";
	int InCheckUpCount;
	InCheckUpCount = pCheckupNorm.getcounter() +
					pCheckupSp.getcounter() +
						pCheckupVIP.getcounter();
	queue<Buses*>* TempBusses = new queue<Buses*>;
	//Buses* TempBus;
	while (pCheckupNorm.Dequeue(TempBus)) {
		InCheckupBusses += "[" + to_string(TempBus->getID()) + "]";
		TempBusses->Enqueue(TempBus);
	}
	while (TempBusses->Dequeue(TempBus)) {
		pCheckupNorm.Enqueue(TempBus);
	}

	while (pCheckupSp.Dequeue(TempBus)) {
		InCheckupBusses += "(" + to_string(TempBus->getID()) + ")";
		TempBusses->Enqueue(TempBus);
	}
	while (TempBusses->Dequeue(TempBus)) {
		pCheckupSp.Enqueue(TempBus);
	}


	while (pCheckupVIP.Dequeue(TempBus)) {
		InCheckupBusses += "{" + to_string(TempBus->getID()) + "}";
		TempBusses->Enqueue(TempBus);
	}
	while (TempBusses->Dequeue(TempBus)) {
		pCheckupVIP.Enqueue(TempBus);
	}


	InteractiveModeData += to_string(InCheckUpCount) + " In-Checkup Trucks: " + InCheckupBusses + lineSeperator;

	InteractiveModeData += to_string(pDeliveredVIP.getcounter()+ pDeliveredSp.getcounter()+ pDeliveredNorm.getcounter()) + " Delivered Passengers: ";
	if (pDeliveredNorm.getcounter() > 0)
		InteractiveModeData += "[" + pDeliveredNorm.getInsideIDs() + "] ";
	if (pDeliveredSp.getcounter() > 0)
		InteractiveModeData += "(" + pDeliveredSp.getInsideIDs() + ") ";
	if (pDeliveredVIP.getcounter() > 0)
		InteractiveModeData += "{" + pDeliveredVIP.getInsideIDs() + "}";
	InteractiveModeData += lineSeperator;

	

	pUI->printMessage(InteractiveModeData);
}

void Company::boardPassengers()
{
	boardVIP();
	boardSp();
	boardNorm();
}

void Company::boardVIP()
{
	Buses* pBus = nullptr;
	int passCount = pWaitVIP.getcounter();
	int capacity = 0;
	
	// Finds an available bus according to criteria
	if (pEmptyVIP.getcounter() != 0)
		pEmptyVIP.Peek(pBus);
	else if (pEmptyNorm.getcounter() != 0)
		pEmptyNorm.Peek(pBus);
	else if (pEmptySp.getcounter() != 0)
		pEmptySp.Peek(pBus);
	else
		return;

	// Checks the boarding condition
	int FarthestPassDist = 0;
	int SumOfUnrideTimes = 0;
	capacity = pBus->get_bus_capacity();
	if (passCount >= capacity)
	{
		for (int i = 0; i < capacity; i++)
		{
			Passengers* pPass = pWaitVIP.Dequeue();
			int DeliveryDistance = pPass->Get_Delivery_distance();
			int Unridetime = pPass->Get_totalRideUnride_Time();
			if (FarthestPassDist < DeliveryDistance) {
				FarthestPassDist = DeliveryDistance;
			}
			SumOfUnrideTimes += Unridetime;
			pBus->board(pPass);
		}
		switch (pBus->get_bus_type())
		{
		case VB:
			pEmptyVIP.Dequeue();
			break;
		case NB:
			pEmptyNorm.Dequeue();
			break;
		case SB:
			pEmptySp.Dequeue();
			break;
		}
		int Priority = (FarthestPassDist / pBus->get_bus_speed()) + SumOfUnrideTimes;
		pMoving.Enqueue(pBus,-Priority); // CHANGE PRIORITY FUNCTION
	}
}

void Company::boardSp()
{
	Buses* pBus = nullptr;
	pEmptySp.Peek(pBus);

	int passCount = pWaitSp.getcounter();
	int capacity = pBus->get_bus_capacity();
	int FarthestPassDist = 0;
	int SumOfUnrideTimes = 0;
	if (passCount >= capacity)
	{
		for (int i = 0; i < capacity; i++)
		{
			Passengers* pPass = pWaitSp.Dequeue();
			int DeliveryDistance = pPass->Get_Delivery_distance();
			int Unridetime = pPass->Get_totalRideUnride_Time();
			if (FarthestPassDist < DeliveryDistance) {
				FarthestPassDist = DeliveryDistance;
			}
			SumOfUnrideTimes += Unridetime;
			pBus->board(pPass);
		}
		pEmptySp.Dequeue();
		int Priority = (FarthestPassDist / pBus->get_bus_speed()) + SumOfUnrideTimes;
		pMoving.Enqueue(pBus, -Priority); // CHANGE PRIORITY FUNCTION
	}
}



void Company::boardNorm()
{
	Buses* pBus = nullptr;
	int passCount = pWaitNorm.getcounter();
	int capacity = 0;
	int FarthestPassDist = 0;
	int SumOfUnrideTimes = 0;
	// Finds an available bus according to criteria
	if (pEmptyNorm.getcounter() != 0)
		pEmptyNorm.Peek(pBus);
	else if (pEmptyVIP.getcounter() != 0)
		pEmptyVIP.Peek(pBus);
	else
		return;

	// Checks the boarding condition
	capacity = pBus->get_bus_capacity();
	if (passCount >= capacity)
	{
		for (int i = 0; i < capacity; i++)
		{

			Passengers* pPass = pWaitNorm.get_head()->get_data();
			int DeliveryDistance = pPass->Get_Delivery_distance();
			int Unridetime = pPass->Get_totalRideUnride_Time();
			if (FarthestPassDist < DeliveryDistance) {
				FarthestPassDist = DeliveryDistance;
			}
			SumOfUnrideTimes += Unridetime;
			pWaitNorm.delete_first();
			pBus->board(pPass);
		}

		switch (pBus->get_bus_type())
		{
		case NB:
			pEmptyNorm.Dequeue();
			break;
		case VB:
			pEmptyVIP.Dequeue();
			break;
		}
		int Priority = (FarthestPassDist / pBus->get_bus_speed()) + SumOfUnrideTimes;
		pMoving.Enqueue(pBus, -Priority); // CHANGE PRIORITY FUNCTION
	}
}

/*
int Company::GetFarthestDeliveryDistance(queue<Passengers*> q) {
	Passengers* pTemp;
	
	for (int i = 0; i < q.getcounter(); i++) {
		pTemp = q.Dequeue();
		int DeliveryDistance = pTemp->Get_Delivery_distance();
		if (DeliveryDistance > FarthestPassDist) {
			FarthestPassDist = DeliveryDistance;
		}
		q.Enqueue(pTemp);
	}
	return FarthestPassDist;
}

int Company::GetSumOfUnrideTime(queue<Passengers*> q) {
	Passengers* pTemp;
	int SumOfUnrideTimes = 0;
	for (int i = 0; i < q.getcounter(); i++) {
		pTemp = q.Dequeue();
		int rideUnride = pTemp->Get_totalRideUnride_Time();
		SumOfUnrideTimes += rideUnride;
		q.Enqueue(pTemp);
	}

}*/






int Company::checkQueueFront(queue<Buses*> q) {
	if (q.ReturnFront()) {
		return 1;
	}
	else {
		return 0;
	}
}


int Company::checkBusFrontID(queue<Buses*> q) {
	if (q.ReturnFront()->get_data()->getID()) {
		return q.ReturnFront()->get_data()->getID();
	}
	else {
		return 0;
	}
}
