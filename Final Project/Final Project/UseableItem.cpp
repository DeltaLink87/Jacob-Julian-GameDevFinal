#pragma once

#include "UseableItem.h"

UseableItem::UseableItem(std::string n, int index) : Item(n,3) {

}

UseableItem::~UseableItem() { }

Item* UseableItem::getCopy() {
	return new UseableItem(*this);
}