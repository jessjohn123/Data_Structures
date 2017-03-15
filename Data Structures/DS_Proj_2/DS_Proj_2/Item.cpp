#include "Item.h"
#include <string>
bool Item::operator==(const Item& rhs)
{
	return strcmp(this->name, rhs.name) == 0;
}