#include "pch.h"
#include "Inventory.h"


void Inventory::Render() const
{
    GS_DEBUG_LOG("gameuser id[{}]'s inventory info=================", gameUserId);
    GS_DEBUG_LOG("-----------[items]-----------------");
    for(const auto& pair: items) {
        pair.second.Render();
    }
    GS_DEBUG_LOG("-----------[costumes]--------------");
    for (const auto& pair : costumes) {
        pair.second.Render();
    }
    GS_DEBUG_LOG("-----------[characters]------------");
    for (const auto& pair : characters) {
        pair.second.Render();
    }

    GS_DEBUG_LOG("==================================================", gameUserId);

}

void Inventory::SetGameUserId(int64_t _gameUserId)
{
    gameUserId = _gameUserId;
}

void Inventory::InitInventoryDatas(
    const vector<ItemRow>& _items
    , const vector<CostumeRow>& _costumes
    , const vector<CharacterRow>& _characters
)
{
    for (const auto& _ele : _items) {
        items.emplace(_ele.basisId, _ele);
    }

    for (const auto& _ele : _costumes) {
        costumes.emplace(_ele.basisId, _ele);
    }

    for (const auto& _ele : _characters) {
        characters.emplace(_ele.basisId, _ele);
    }
}

const ItemData* Inventory::GetItem(int64_t _basisId)
{
    auto pair = items.find(_basisId);
    if(pair == items.end())
        return nullptr;
    else {
        return &pair->second;
    }
}

const CostumeData* Inventory::GetCostume(int64_t _basisId)
{
    auto pair = costumes.find(_basisId);
    if (pair == costumes.end())
        return nullptr;
    else {
        return &pair->second;
    }
}

const CharacterData* Inventory::GetCharacter(int64_t _basisId)
{
    auto pair = characters.find(_basisId);
    if (pair == characters.end())
        return nullptr;
    else {
        return &pair->second;
    }
}
