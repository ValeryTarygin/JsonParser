#pragma once

#include "composite_base.h"

class CCompositeLeaf : public CCompositeBase
{
public:
	CCompositeLeaf() {};
	CCompositeLeaf(std::wstring _value): CCompositeBase(_value) {};
	
public:
	virtual CompositePtr addItem(CompositePtr item) override { return {}; };
	virtual std::wstring out() override {
		std::wstring result(value_);
		return result.append(L";\n");	
	};
};
