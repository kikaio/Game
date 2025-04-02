#pragma once


class DBWrapper {
public:
	static PacketError ChatProfileSelect(IN int64_t _accountId, OUT ChatProfileSptr& _profile);
};

