#pragma once


using ItemMap = map<int64_t, ItemData>;
using CostumeMap = map<int64_t, CostumeData>;
using CharacterMap = map<int64_t, CharacterData>;

class Inventory {
private: 
	int64_t gameUserId = 0;
	ItemMap items;
	CostumeMap costumes;
	CharacterMap characters;
public:
	void Render() const ;
public:
	void SetGameUserId(int64_t _gameUserId);
	void InitInventoryDatas(
		const vector<ItemRow>& _items
		, const vector<CostumeRow>& _costumes
		, const vector<CharacterRow>& _characters
	);
public:
	const ItemData* GetItem(int64_t _basisId);
	const CostumeData* GetCostume(int64_t _basisId);
	const CharacterData* GetCharacter(int64_t _basisId);

public :
	const ItemMap& GetItems() const{
		return items;
	}

	const CostumeMap& GetCostumes() const {
		return costumes;
	}
	
	const CharacterMap& GetCharacters() const{
		return characters;
	}
};