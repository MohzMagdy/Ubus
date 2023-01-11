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
	pCheckupNorm.isempty());
}


void Company::simulate()
{
	
	while (true)
	{
		// prioequation();
		Timestep = Timestep + 1;
		
		if (Isworkinghours()) {
			boardPassengers(pUI->GetCurrentMode());
			CheckAutopromotion();
			/*Timestep = 0; */
			//maxqs();
		}
		maintinance_check();
		/*ExecuteDeliveryFailure();*/
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
		Buses* n = new Buses(Bus_Type::NB, cNBus, Time(cdNBus), sNBus, i,5); ///MUST BE CHANGED TO BUS SIZE
		add_empty_bus(n);
	}
	for (int i = 0; i < noSbus; i++) {
		Buses* n = new Buses(Bus_Type::SB, cSBus, Time(cdSBus), sSBus, i,5); ///MUST BE CHANGED TO BUS SIZE
		add_empty_bus(n);
	}
	for (int i = 0; i < noVbus; i++) {
		Buses* n = new Buses(Bus_Type::VB, cVBus, Time(cdVBus), sVBus, i,5); ///MUST BE CHANGED TO BUS SIZE
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
//	this->MoveToCheckUp(pBus);
}



void Company::boardPassengers(Mode CurrentMode)
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
	capacity = pBus->get_bus_capacity();
	if (passCount >= capacity)
	{
		for (int i = 0; i < capacity; i++)
		{
			Passengers* pPass = pWaitVIP.Dequeue();
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
		pMoving.Enqueue(pBus); // CHANGE PRIORITY FUNCTION
	}
}

void Company::boardSp()
{
	Buses* pBus = nullptr;
	pEmptySp.Peek(pBus);
	if (pBus) {
		int passCount = pWaitSp.getcounter();
		int capacity = pBus->get_bus_capacity();

		if (passCount >= capacity)
		{
			for (int i = 0; i < capacity; i++)
			{
				Passengers* pPass = pWaitSp.Dequeue();
				pBus->board(pPass);
			}
			pEmptySp.Dequeue();
			pMoving.Enqueue(pBus); // CHANGE PRIORITY FUNCTION
		}
	}
}

void Company::boardNorm()
{
	Buses* pBus = nullptr;
	int passCount = pWaitNorm.getcounter();
	int capacity = 0;

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
		pMoving.Enqueue(pBus); // CHANGE PRIORITY FUNCTION
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

