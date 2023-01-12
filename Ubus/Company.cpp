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
	pEmptyVIP.isempty() &&
	pEmptySp.isempty() &&
	pEmptyNorm.isempty() &&
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
		// prioequation();
		Timestep = Timestep + 1;
		
		if (Isworkinghours()) {
			ExecuteAvailableEvent();
			boardPassengers(pUI->GetCurrentMode());
			CheckAutopromotion();
			/*Timestep = 0; */
			//maxqs();
		}
		maintinance_check();
		/*ExecuteDeliveryFailure();*/
		/*deliver_passengers();*/
		

		PrintInteractiveModeData();
		deliver_passengers();
		incheck();
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

	no_checkup = noCheckup;

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


void Company::deliver_passengers() {
	Buses*pBus = nullptr;
	Passengers*pPass = nullptr ;
	queue<Buses*> TempQ;
	
	while (!pMoving.isempty())
	{
		pBus = pMoving.Dequeue();
		pBus->passenger_peek(pPass); 
		if (pPass!=nullptr)
		{
			int readytime = pPass->Get_ready_Time().Gettotalhours();
			int nowtimestep = this->Timestep.Gettotalhours();
			if (nowtimestep - readytime > 0) {
				Time TimeFromStartTheJurnyUntillNow = (this->Timestep - pPass->Get_ready_Time());
				double deliverytime = ((pPass->Get_Delivery_distance() / pBus->get_bus_speed()) +  (pPass->Get_totalRideUnride_Time()));
				double TimeFromStartTheJurnyUntillNo = double (TimeFromStartTheJurnyUntillNow.Gettotalhours());

				if (TimeFromStartTheJurnyUntillNo >= deliverytime)
				{
					pBus->passenger_Deqeue(pPass);
					Passenger_Type PT = pPass->get_passanger_type();
					switch (PT)
					{
					case VP:
					pDeliveredVIP.Enqueue(pPass);
						break;
					case SP:
						pDeliveredSp.Enqueue(pPass);
						break;
					case NP:
						pDeliveredNorm.Enqueue(pPass);
						break;
					}
					if (pBus->get_onboardCount() == 0) {
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
					else {
						TempQ.Enqueue(pBus);
					}
				}
				else {
					TempQ.Enqueue(pBus);
				}
			}
			else {
				TempQ.Enqueue(pBus);
				break;
			}
		}

	}
	Buses* pMBus = nullptr;
	while (!TempQ.isempty())
	{
		pMBus = TempQ.Dequeue();
		pMBus->increase_journey();
		pMoving.Enqueue(pMBus);
	}
}





//// bouns Delivery failure

void Company::ExecuteDeliveryFailure() {
	double probability = 5; // probability of dropping a buses
	int numtodrop = 0;

	if (pMoving.getcounter() == 0) {
		return;
	}
	int smallpor = rand() % 100;
	if (smallpor < probability) {
		numtodrop = rand() % this->pMoving.getcounter() + 1;
		for (int i = 0; i < numtodrop; i++) {
			this->DropBus();
		}
	}

}
void Company::DropBus() {

	Buses* pBus;
	pBus = pMoving.Dequeue();

	Passengers* pPass = nullptr;
	Bus_Type BT = pBus->get_bus_type();
	switch (BT)
	{
	case VB:
		pBus->passenger_peek(pPass);
		this->pWaitVIP.Enqueue(pPass);
		pBus->passenger_Deqeue(pPass);
		break;
	case SB:
		pBus->passenger_peek(pPass);
		this->pWaitSp.Enqueue(pPass);
		pBus->passenger_Deqeue(pPass);
		break;
	case NB:
		pBus->passenger_peek(pPass);
		this->pWaitNorm.insert_end(pPass);
		pBus->passenger_Deqeue(pPass);
		break;
	}
}
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
				RidingBusData += "[" + to_string(TempBus->getID()) + "] ";
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
			EmptyBuses += "[" + to_string(IDsEmptyNormal[i] - 48) + "] ";
		}
		for (int i = 0; i < IDsEmptySp.size(); i++) {
			if (i == 0 && countRidingBusesSp != 0) { continue; }
			EmptyBuses += "(" + to_string(IDsEmptySp[i] - 48) + ") ";
		}

		for (int i = 0; i < IDsEmptyVIP.size(); i++) {
			if (i == 0 && countRidingBusesVIP != 0) { continue; }
			EmptyBuses += "{" + to_string(IDsEmptyVIP[i] - 48) + "} ";
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

		InteractiveModeData += to_string(pDeliveredVIP.getcounter() + pDeliveredSp.getcounter() + pDeliveredNorm.getcounter()) + " Delivered Passengers: ";
		if (pDeliveredNorm.getcounter() > 0)
			InteractiveModeData += "[" + pDeliveredNorm.getInsideIDs() + "] ";
		if (pDeliveredSp.getcounter() > 0)
			InteractiveModeData += "(" + pDeliveredSp.getInsideIDs() + ") ";
		if (pDeliveredVIP.getcounter() > 0)
			InteractiveModeData += "{" + pDeliveredVIP.getInsideIDs() + "}";
		InteractiveModeData += lineSeperator;



		pUI->printMessage(InteractiveModeData);
	}


void Company::boardPassengers(Mode CurrentMode)
{
	switch (CurrentMode)
	{
	case Interactive:
	case Step:
	case Silent:
		boardVIP();
		boardSp();
		boardNorm();
		break;
	case Immediate:
		immBoardVIP();
		immBoardSp();
		immBoardNorm();
		break;
	}
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

//ff

void Company::boardSp()
{
	Buses* pBus = nullptr;
	pEmptySp.Peek(pBus);
	if (pBus) {
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
void Company::maintinance_check()
{
	Node<Buses*>* pbusnor = pEmptyNorm.ReturnFront();
	Node<Buses*>* pbussp = pEmptySp.ReturnFront();
	Node<Buses*>* pbusvip = pEmptyVIP.ReturnFront();
	while (pbusnor != nullptr)
	{
		
		if (pbusnor->get_data()->get_journeys()%no_checkup==0)
		{
			Node<Buses*>* deleter = pbusnor;
			pCheckupNorm.Enqueue(pbusnor->get_data());
			pEmptyNorm.delete_data(deleter->get_data());
			cout << "Normal bus moved to checkup " << endl;
			pbusnor = pEmptyNorm.ReturnFront();
		}
		else
		{
			pbusnor = pbusnor->get_next();
		}
	}
	while (pbussp!=nullptr)
	{
		if (pbussp->get_data()->get_journeys() % no_checkup == 0)
		{
			Node<Buses*>* deleter = pbussp;
			pCheckupSp.Enqueue(pbussp->get_data());
			pEmptySp.delete_data(deleter->get_data());
			cout << "Special bus moved to checkup " << endl;
			pbussp = pEmptySp.ReturnFront();
		}
		else
		{
			pbussp = pbussp->get_next();
		}
	}
	while (pbusvip!=nullptr)
	{
		if (pbusvip->get_data()->get_journeys() % no_checkup == 0)
		{
			Node<Buses*>* deleter = pbusvip;
			pCheckupVIP.Enqueue(pbusvip->get_data());
			pEmptyVIP.delete_data(deleter->get_data());
			cout << "VIP bus moved to checkup " << endl;
			pbusvip = pEmptyVIP.ReturnFront();
		}
		else
		{
			pbusvip = pbusvip->get_next();
		}
	}
}

void Company::incheck()
{
	Node<Buses*>* pbusnor = pCheckupNorm.ReturnFront();
	Node<Buses*>* pbussp = pCheckupSp.ReturnFront();
	Node<Buses*>* pbusvip = pCheckupVIP.ReturnFront();
	while (pbusnor!=nullptr)
	{
		if (pbusnor->get_data()->get_maintitnance_time()%7==0)
		{
			Node<Buses*>* deleter = pbusnor;
			pEmptyNorm.Enqueue(pbusnor->get_data());
			pCheckupNorm.delete_data(deleter->get_data());
			cout << "Normal bus finished maintinance" << endl;
			pbusnor = pCheckupNorm.ReturnFront();
		}
		else
		{
			pbusnor->get_data()->increase_maintinancetime();
			pbusnor = pbusnor->get_next();
		}
		
	}
	while (pbussp != nullptr)
	{
		if (pbussp->get_data()->get_maintitnance_time() % 7 == 0)
		{
			Node<Buses*>* deleter = pbussp;
			pEmptySp.Enqueue(pbussp->get_data());
			pCheckupSp.delete_data(deleter->get_data());
			cout << "Special bus finished maintinance" << endl;
			pbussp = pCheckupSp.ReturnFront();
		}
		else
		{
			pbussp->get_data()->increase_maintinancetime();
			pbussp = pbussp->get_next();
		}
		
	}
	while (pbusvip != nullptr)
	{
		if (pbusvip->get_data()->get_maintitnance_time() % 7 == 0)
		{
			Node<Buses*>* deleter = pbusvip;
			pEmptyVIP.Enqueue(pbusvip->get_data());
			pCheckupVIP.delete_data(deleter->get_data());
			cout << "VIP bus finished maintinance" << endl;
			pbusvip = pCheckupVIP.ReturnFront();
		}
		else
		{
			pbusvip->get_data()->increase_maintinancetime();
			pbusvip = pbusvip->get_next();
		}
		
	}
}

void Company::immBoardVIP()
{
	Buses* pBus = nullptr;
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

	// Move passengers to bus of same type when available
	if (pBus->get_bus_type() == VB)
	{
		Buses* pHelper = nullptr;
		priority_queue<Passengers*> tempQueue;
		int onboardCount = 0;
		int EmptyCount = 0;
		int busCapacity = pBus->get_bus_capacity();

		for (int j = 0; j < 2; j++)
		{
			switch (j)
			{
			case 0:
				EmptyCount = pEmptyNorm.getcounter();
				pEmptyNorm.Peek(pHelper);
				break;
			case 1:
				EmptyCount = pEmptySp.getcounter();
				pEmptySp.Peek(pHelper);
				break;
			}

			if (EmptyCount != 0)
			{
				onboardCount = pHelper->get_onboardCount();
				for (int i = 0; i < onboardCount && pBus->get_onboardCount() < busCapacity; i++) // Check type of each boarded passenger
				{
					Passengers* pPass = pHelper->get_seats()->Dequeue();
					if (pPass->get_passanger_type() == VP)
					{
						pBus->get_seats()->Enqueue(pPass, 0); // CHANGE PRIORITY FUNCTION
					}
					else
					{
						tempQueue.Enqueue(pPass);
					}
				}
				onboardCount = tempQueue.getcounter();
				for (int i = 0; i < onboardCount; i++)
				{
					pHelper->get_seats()->Enqueue(tempQueue.Dequeue());
				}
			}
		}
	}

	// Board a passenger immediately
	if (pWaitVIP.getcounter() != 0)
	{
		Passengers* pPass = pWaitVIP.Dequeue();
		if (pPass == nullptr) return;
		pBus->board(pPass);

		// Move bus if full
		if (pBus->get_onboardCount() == pBus->get_bus_capacity())
		{
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
			pMoving.Enqueue(pBus, 0); // CHANGE PRIORITY FUNCTION
		}
	}
}

void Company::immBoardSp()
{
	Buses* pBus = nullptr;
	if (pEmptySp.getcounter() != 0)
		pEmptySp.Peek(pBus);
	else
		return;

	// Board a passenger immediately
	if (pWaitSp.getcounter() != 0)
	{
		Passengers* pPass = pWaitSp.Dequeue();
		if (pPass == nullptr) return;
		pBus->board(pPass);

		// Move bus if full
		if (pBus->get_onboardCount() == pBus->get_bus_capacity())
		{
			pEmptySp.Dequeue();
			pMoving.Enqueue(pBus, 0); // CHANGE PRIORITY FUNCTION
		}
	}
}

void Company::immBoardNorm()
{
	Buses* pBus = nullptr;
	int capacity = 0;

	// Finds an available bus according to criteria
	if (pEmptyNorm.getcounter() != 0)
		pEmptyNorm.Peek(pBus);
	else if (pEmptyVIP.getcounter() != 0)
		pEmptyVIP.Peek(pBus);
	else
		return;

	// Move passengers to bus of same type when available
	if (pBus->get_bus_type() == NB)
	{
		Buses* pHelper = nullptr;
		priority_queue<Passengers*> tempQueue;
		int onboardCount = 0;
		int EmptyCount = 0;
		int busCapacity = pBus->get_bus_capacity();

		
		EmptyCount = pEmptyNorm.getcounter();
		pEmptyNorm.Peek(pHelper);

		if (EmptyCount != 0)
		{
			onboardCount = pHelper->get_onboardCount();
			for (int i = 0; i < onboardCount && pBus->get_onboardCount() < busCapacity; i++) // Check type of each boarded passenger
			{
				Passengers* pPass = pHelper->get_seats()->Dequeue();
				if (pPass->get_passanger_type() == NP)
				{
					pBus->get_seats()->Enqueue(pPass, 0); // CHANGE PRIORITY FUNCTION
				}
				else
				{
					tempQueue.Enqueue(pPass);
				}
			}
			onboardCount = tempQueue.getcounter();
			for (int i = 0; i < onboardCount; i++)
			{
				pHelper->get_seats()->Enqueue(tempQueue.Dequeue());
			}
		}
		
	}

	// Board a passenger immediately
	if (pWaitNorm.getcounter() != 0)
	{
		Passengers* pPass = pWaitNorm.get_head()->get_data();
		pWaitNorm.delete_first();
		if (pPass == nullptr) return;
		pBus->board(pPass);

		// Move bus if full
		if (pBus->get_onboardCount() == pBus->get_bus_capacity())
		{
			switch (pBus->get_bus_type())
			{
			case VB:
				pEmptyVIP.Dequeue();
				break;
			case NB:
				pEmptyNorm.Dequeue();
				break;
			}
			pMoving.Enqueue(pBus, 0); // CHANGE PRIORITY FUNCTION
		}
	}
}
