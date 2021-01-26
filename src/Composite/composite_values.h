#pragma once

#include "composite_base.h"
#include <list>

class CCompositeValues : public std::enable_shared_from_this<CCompositeValues>, public CCompositeBase
{
	std::list<CompositePtr> children_;

public:
	CCompositeValues();
	CCompositeValues(std::wstring _value);

public:
	virtual CompositePtr addItem(CompositePtr item) override;
	virtual std::wstring out() override;
};

