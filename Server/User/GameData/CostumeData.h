#pragma once


class CostumeData {
private:
	int64_t basisId = 0;
public:
	CostumeData(int64_t _basisId) : basisId(_basisId)
	{
	}

	CostumeData(const CostumeRow& _row) : basisId(_row.basisId){
	}
public:
	int64_t GetBasisId()  const {
		return basisId;
	}

	void SetBasisId(int64_t _id) {
		basisId = _id;
	}
public:
	void Render()  const {
		GS_DEBUG_LOG("basisId[{}]", basisId);
	}
};