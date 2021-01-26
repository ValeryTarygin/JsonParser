#pragma once
#include <memory>
#include <string>
#include <iostream>

using CompositePtr = std::shared_ptr<class CCompositeBase>;

class CCompositeBase
{
	std::weak_ptr<CCompositeBase> parent_;

protected:
	std::wstring value_;

public:
	CCompositeBase() {};
	CCompositeBase(std::wstring value): value_(value) {};
	virtual ~CCompositeBase() {};

public:
	virtual CompositePtr addItem(CompositePtr item) = 0;
	virtual std::wstring out() = 0;

public:
	void setParent(const CompositePtr& parent) { parent_ = parent; };
	CompositePtr getParent() const { return parent_.lock(); };
};

