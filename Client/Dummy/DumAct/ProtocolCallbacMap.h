#pragma once

using DUM_PROTOCOL_CB = std::function<void()>;
using DUM_PROTOCOL_CB_VECT = std::vector<DUM_PROTOCOL_CB>;
using PROTO_TUPLE = std::tuple<int32_t, int32_t>;

class ProtocolCallbackMap {
private:
	std::map<PROTO_TUPLE, DUM_PROTOCOL_CB_VECT> cbMap;
public:
	template <typename MSG_TYPE, typename PROTOCOL_TYPE>
	void ReserveCallback(MSG_TYPE _msg, PROTOCOL_TYPE _protocol, DUM_PROTOCOL_CB&& _cb) {
		auto _tuple = std::make_tuple((int32_t)_msg, (int32_t)_protocol);
		auto _iter = cbMap.find(_tuple);
		if (_iter == cbMap.end()) {
			cbMap[_tuple] = DUM_PROTOCOL_CB_VECT();
		}
		DUM_PROTOCOL_CB_VECT& _vect = cbMap[_tuple];
		_vect.push_back(std::move(_cb));

	}

	template <typename MSG_TYPE, typename PROTOCOL_TYPE>
	void RecvProtocol(MSG_TYPE _msg, PROTOCOL_TYPE _protocol) {
		auto _tuple = std::make_tuple((int32_t)_msg, (int32_t)_protocol);
		auto _iter = cbMap.find(_tuple);
		if(_iter == cbMap.end()) {
			cbMap[_tuple] = DUM_PROTOCOL_CB_VECT();
		}
		//callback 목록 호출해 준 뒤 vector 비움.
		DUM_PROTOCOL_CB_VECT& _vect = cbMap[_tuple];
		for(auto& _ele : _vect) {
			_ele();
		}
		_vect.clear();
	}
};