#pragma once

struct ChatProfileMng : public Singleton<ChatProfileMng > {
private:
	std::map<int64_t, ChatProfileSptr> profiles;
public:
	ChatProfileSptr GetProfile(int64_t _profileId);
	ChatProfileSptr CreateProfile(int64_t _id
		, const string& _nickName
		, int64_t _mainHeroId
		, int64_t _mainFrameId
	);
public:
	void Clear();
};