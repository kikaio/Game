#pragma once

class CharacterData {
private:
	int64_t basisId;
public:
	CharacterData(const CharacterRow& _row) : basisId(_row.basisId) {
	
	}
public:
	void Render()  const {
		GS_DEBUG_LOG("character id[{}]", basisId);
	}
public: 
	int64_t GetBasisId()  const {
		return basisId;
	}

	void SetBasisId(int64_t _id) {
		basisId = _id;
	}
};