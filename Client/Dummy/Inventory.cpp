#include "pch.h"
#include "Inventory.h"

void Inventory::initInventory(
	const vector<ItemData>& _itemVect
	, const vector<CostumeData>& _costumeVect
	, const vector<CharacterData>& _characterVect
	)
{
	items.clear();
	for(const auto& _ele : _itemVect) {
		items.emplace(_ele.basisId, _ele);
	}

	costumes.clear();
	for (const auto& _ele : _costumeVect) {
		costumes.emplace(_ele.basisId, _ele);
	}

	characters.clear();
	for (const auto& _ele : _characterVect) {
		characters.emplace(_ele.basisId, _ele);
	}
}
