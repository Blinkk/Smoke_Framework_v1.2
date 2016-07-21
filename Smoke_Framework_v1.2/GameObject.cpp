#include "Engine.h"
#include "GameObject.h"

namespace Smoke
{
	GameObject::GameObject()
	{

	}


	GameObject::~GameObject()
	{
		// Remove all existing components
	}


	void GameObject::AddComponent(Handle component)
	{

		/*IComponent* pTemp = nullptr;
		for (_handleIt = _components.begin(); _handleIt != _components.end(); ++_handleIt)
		{
			if (g_Engine->GetHandleManager()->GetAs((*_handleIt), pTemp))
			{
				IComponent* pTemp2 = nullptr;
				if (g_Engine->GetHandleManager()->GetAs(component, pTemp2))
				{
					if (pTemp->componentType == pTemp2->componentType)
					{
						debug << "Failed to add component to GameObject because a component of that type already exists" << std::endl;
						return;
					}
				}	
				pTemp2 = nullptr;
			}
			pTemp = nullptr;
		}*/

		// If no component of that type exists, add it
		_components.push_back(component);
	}


	void GameObject::RemoveComponent(unsigned int componentType)
	{
		IComponent* pTemp = nullptr;
		for (_handleIt = _components.begin(); _handleIt != _components.end(); ++_handleIt)
		{
			// Get the handle as an IComponent*
			if (g_Engine->GetHandleManager()->GetAs((*_handleIt), pTemp))
			{
				if (pTemp->componentType == componentType)
				{
					// REMOVE THE HANDLE
					g_Engine->GetHandleManager()->Remove((*_handleIt));
					_components.erase(_handleIt);
					return;
				}
			}
			else
			{
				debug << "Failed to get handle as IComponent*, could not remove component" << std::endl;
				return;
			}

			pTemp = nullptr;
		}
	}
}