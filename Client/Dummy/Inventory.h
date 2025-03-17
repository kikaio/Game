#pragma once

using Items = map<int64_t, ItemData>;
using Costumes = map<int64_t, CostumeData>;
using Characters = map<int64_t, CharacterData>;

struct Inventory
{
public:
	int64_t gameUserId = 0;
	Items items;
	Costumes costumes;
	Characters characters;
public:
	void initInventory(
		const vector<ItemData>& _itemVect
		, const vector<CostumeData>& _costumeVect
		, const vector<CharacterData>& _characterVect
	);
public:
};