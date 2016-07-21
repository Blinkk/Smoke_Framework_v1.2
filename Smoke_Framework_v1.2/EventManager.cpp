/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

////////////////////////////////////////////////////////////////
// A variation of Jorge Morales' 
// DirectX 9 Framework Event System -
// https://ebnr.visualstudio.com/DefaultCollection/SG%20450
////////////////////////////////////////////////////////////////

namespace Smoke
{
	EventManager::EventManager()  
	{
		for (int i = 0; i <= Events::MAX; ++i)
		{
			Registrants[i] = Listeners();
		}
	}

	void EventManager::StoreListener(Delegate del, unsigned int eventCode)
	{
		Registrants[eventCode][del.ID] = del;
	}


	Delegate EventManager::PackageListener(IComponent* pIGO)
	{
		Delegate D = Delegate::makeDelegateFromFunction<IComponent, &IComponent::HandleEvent>(pIGO, pIGO->componentID);

		return D;
	}

	void EventManager::RegisterListener(IComponent* pIGO, unsigned int eventCode)
	{
		StoreListener(PackageListener(pIGO), eventCode);
	}

	void EventManager::DispatchEvent(IEvent* pEvent)
	{
		EventQueue.push(pEvent);
	}

	void EventManager::PurgeAllListeners()
	{
		// Erase listeners
		int size = Registrants.size();
		for (unsigned int i = 0; i < size; ++i)
		{
			Registrants[i].erase(Registrants[i].begin(), Registrants[i].end());
			Registrants.erase(i);
		}
	}

	void EventManager::PurgeListener(unsigned int ID_NUMBER, unsigned int eventCode)
	{
		// Remove the specified listener
		Registrants[eventCode].erase(ID_NUMBER);
	}

	void EventManager::Update()
	{
		// Dispatch all events
		while (EventQueue.empty() != true)
		{
			// More convienent reference to the Event
			IEvent* pEvent = EventQueue.front();

			if (pEvent == nullptr)
			{
				// TODO: Create proper error message because this should not happen
				return;
			}

			Listeners::iterator Iter = Registrants[pEvent->Event_Type].begin();

			// Iterate through the 
			while (pEvent->handledErase != true && Iter != Registrants[pEvent->Event_Type].end())
			{
				(*Iter).second(pEvent);

				++Iter;
			}

			delete pEvent;
			pEvent = nullptr;
			EventQueue.pop();
		}
	}

	void EventManager::Shutdown()
	{
		this->PurgeAllListeners();

		if (Registrants.empty())
			debug << "\tEvent manager shutdown" << std::endl;
		else
			debug << "\tError shutting down event manager" << std::endl;
	}
	

	EventManager::~EventManager()
	{
		// Shutdown function manages 
		// memory deallocation
	}
}