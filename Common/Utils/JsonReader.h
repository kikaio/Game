#pragma once

using namespace rapidjson;

class JsonReader : public JsonParser
{
public:
	JsonReader();
	~JsonReader();
private:
	Document doc;
};