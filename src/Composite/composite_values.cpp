#include "composite_values.h"
#include "composite_leaf.h"

CCompositeValues::CCompositeValues()
{
}

CCompositeValues::CCompositeValues(std::wstring _value)
	: CCompositeBase(_value)
{	
}

CompositePtr CCompositeValues::addItem(CompositePtr item)
{
	if(item)
	{
		children_.emplace_back(item);
		item->setParent(shared_from_this());

		if(std::dynamic_pointer_cast<CCompositeLeaf>(item))
			return shared_from_this();
	}

	return item;
}

std::wstring CCompositeValues::out()
{
	std::wstring result;

	for(auto& it : children_)
	{
		if(getParent())
		{
			result.append(value_);
			result.append(L": ");
		}

		result.append(it->out());
	}

	return result;
}
