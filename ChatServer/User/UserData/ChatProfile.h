#pragma once

class ChatProfile {
private:
	int64_t profileId = 0;
	string nickName = "";
	int64_t profileMainHeroId = 0;
	int64_t profileMainFrameId = 0;
public:
	void SetProfileId(int64_t _id);
	int64_t GetProfileId() const;
	void SetNickName(const string& _name);
	const string& GetNickName() const;
	void SetMainHeroId(int64_t _id);
	int64_t GetMainHeroId() const;
	void SetMainFrameId(int64_t _id);
	int64_t GetMainFrameId() const;
};