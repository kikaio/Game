#include "pch.h"
#include "Inventory.h"

void Inventory::Render()
{
	DUM_DEBUG_LOG("[inventory]=======");
	DUM_DEBUG_LOG("[items]");
	for(const auto& _pair : items) {
		const auto& _ele = _pair.second;
		DUM_DEBUG_LOG("item basis id[{}], cnt[{}], cntPrev[{}]", _ele.basisId, _ele.cnt, _ele.cntPrev);
	}
	DUM_DEBUG_LOG("[costumes]");
	for (const auto& _pair : costumes) {
		const auto& _ele = _pair.second;
		DUM_DEBUG_LOG("costume basis id[{}]", _ele.basisId);
	}
	DUM_DEBUG_LOG("[characters]");
	for (const auto& _pair : characters) {
		const auto& _ele = _pair.second;
		DUM_DEBUG_LOG("character basis id[{}]", _ele.basisId);
	}

}
