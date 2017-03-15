#include"TransactionManager.h"

void TransactionManager::Buy()
{
	for (;;)
	{
		char userInput[32];
		cout << "\nWhat would you like to buy?" << endl;
		cin >> userInput;

		Item acc_obj;
		Transaction object;

		if (theStore.Search(userInput, acc_obj))
		{
			object.theItem = acc_obj;
			theInventory.AddItem(acc_obj);
			object.bought = true;
			theHistory.addHead(object);
			if (theHistory.size() > 5)
			{

				SLLIter<Transaction> iter(theHistory);
				iter.begin();
				for (unsigned int i = 0; i < 6; ++i)
					++iter;

				theHistory.remove(iter);
			}
			break;

		}

		//system("cls");
		//theInventory.Display();
		cin.clear();
		cin.ignore(LLONG_MAX, '\n');
		continue;
	}
	
}


void TransactionManager::Sell()
{
	char user[32];
	cout << "\nWhat would you like to sell?" << endl;
	cin >> user;

	Item accs_obj;
	Transaction object;
	
	if (theStore.Search(user, accs_obj))
	{
		object.theItem = accs_obj;
		theInventory.RemoveItem(accs_obj);
		object.bought = false;
		theHistory.addHead(object);
		if (theHistory.size() > 5)
		{
			SLLIter<Transaction> iter(theHistory);
			iter.begin();
			for (unsigned int i = 0; i < 6; ++i)
				++iter;

			theHistory.remove(iter);
		}
		//theInventory.Display();
	}
}

void TransactionManager::Undo()
{
	if (theHistory.size() < 1)
		return;
	
		SLLIter<Transaction> iter(theHistory);
		iter.begin();
		int halfAmt = (iter.current().theItem.cost) / 2;
		if (iter.current().bought)
		{
			//theInventory.SetCoins(theInventory.GetCoins() + iter.current().theItem.cost);
			//theInventory.SetWeight(theInventory.GetWeight() - iter.current().theItem.weight);
			theInventory.RemoveItem(iter.current().theItem);
			theHistory.remove(iter);
			theInventory.Display();
		}

		else if (!iter.current().bought)
		{

			theInventory.SetCoins(theInventory.GetCoins() - halfAmt);
			theInventory.SetWeight(theInventory.GetWeight() + iter.current().theItem.weight);
			theInventory.RemoveItem(iter.current().theItem);
			theHistory.remove(iter);
			theInventory.Display();
		}

}