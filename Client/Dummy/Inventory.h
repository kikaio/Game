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
	const Items& GetItems() const {
		return items;
	}
	const Costumes GetCostumes() const {
		return costumes;
	}
	const Characters GetCharacters() const {
		return characters;
	}
};