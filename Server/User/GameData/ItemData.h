#pragma once


class ItemData {
private:
	int64_t basisId = 0;
	int64_t cnt = 0;
	int64_t cntPrev = 0;
public:
	ItemData(const ItemRow& _row) {
		basisId = _row.basisId;
		cnt = _row.itemCnt;
		cntPrev = _row.itemCntPrev;
	}
public:
	int64_t GetBasisId()  const {
		return basisId;
	}

	void SetBasisId(int64_t _id) {
		basisId = _id;
	}

	int64_t GetCnt() const {
		return cnt;
	}

	void SetCnt(int64_t _cnt) {
		cnt = _cnt;
	}

	int64_t GetCntPrev()  const {
		return cntPrev;
	}

	void SetCntPrev(int64_t _cntPrev) {
		cntPrev = _cntPrev;
	}
public:
	void Render()  const {
		GS_DEBUG_LOG("item Id[{}], Cnt[{}], CntPrev[{}]", basisId, cnt, cntPrev);
	}
public:
	bool IncreaseItemCnt(int64_t _cnt) {
		if(_cnt < 0) {
			GS_ERROR_LOG("item cnt must be positive. item id[{}], cur cnt[{}], input cnt[{}]"
				, basisId, cnt, _cnt
			);
			return false;
		}
		if(INT64_MAX - _cnt < cnt) {
			//todo : overflow
			GS_ERROR_LOG("item cnt overflow. item id[{}], cur cnt[{}], input cnt[{}]"
				, basisId, cnt, _cnt
			);
			return false;
		}
		cntPrev = cnt;
		cnt += _cnt;
		return true;
	}

	bool DecreaseItemCnt(int64_t _cnt) {
		if (_cnt < 0) {
			GS_ERROR_LOG("item cnt must be positive. item id[{}], cur cnt[{}], input cnt[{}]"
				, basisId, cnt, _cnt
			);
			return false;
		}
		if (INT64_MIN + _cnt > cnt) {
			GS_ERROR_LOG("item cnt underflow. item id[{}], cur cnt[{}], input cnt[{}]"
				, basisId, cnt, _cnt
			);
			return false;
		}
		cntPrev = cnt;
		cnt -= _cnt;
		return true;
	}

	bool CheckValidate() {
		// todo : 추후 item  기획 data에 따라 적합성 여부 확인용 함수.
		return true;
	}
};