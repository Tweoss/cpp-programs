#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <iostream>

class SimpleEntry
{
private:
	std::string key;
	int value;

public:
	std::string getKey() const
	{
		return key;
	}
	int getValue() const
	{
		return value;
	}
	void setKey(std::string key)
	{
		this->key = key;
	}
	void setValue(int value)
	{
		this->value = value;
	}
};

class SimpleNode
{
private:
	std::vector<SimpleEntry> entries;

public:
	std::vector<SimpleEntry> getEntries() const
	{
		return entries;
	}
	void pushEntry(SimpleEntry e)
	{
		entries.push_back(e);
	}
	void updateEntry(size_t i, int value)
	{
		entries[i].setValue(value);
	}
	~SimpleNode()
	{
		entries.clear();
	}
};

class SimpleMap
{
private:
	std::vector<SimpleNode> memory;

public:
	SimpleMap();
	void put(std::string key, int value);
	int get(std::string key);
	size_t hash(std::string key);
};

SimpleMap::SimpleMap()
{
	memory.resize(200);
}

void SimpleMap::put(std::string key, int value)
{
	int index = hash(key) % memory.size();
	if (memory[index].getEntries().size() == 0)
	{
		SimpleEntry *entry = new SimpleEntry();
		entry->setKey(key);
		entry->setValue(value);
		memory[index].pushEntry(*entry);
		delete entry;
	}
	else
	{
		for (int i = 0; i < memory[index].getEntries().size(); i++)
		{
			if (memory[index].getEntries()[i].getKey() == key)
			{
				memory[index].updateEntry(i, value);
				return;
			}
		}
		SimpleEntry *entry = new SimpleEntry();
		entry->setKey(key);
		entry->setValue(value);
		memory[index].pushEntry(*entry);
		delete entry;
	}
}

int SimpleMap::get(std::string key)
{
	int index = hash(key) % memory.size();
	for (int i = 0; i < memory[index].getEntries().size(); i++)
	{
		if (memory[index].getEntries()[i].getKey() == key)
			return memory[index].getEntries()[i].getValue();
	}
	return -1;
}

size_t SimpleMap::hash(std::string key)
{
	std::hash<std::string> hasher;
	return hasher(key);
}

int main(int argc, char const *argv[])
{
	SimpleMap map;
	map.put("key1", 1);
	map.put("key2", 2);
	map.put("key3", 3);
	std::cout << "Key1 is now " << map.get("key1") << std::endl;
	std::cout << "Key2 is now " << map.get("key2") << std::endl;
	std::cout << "Key3 is now " << map.get("key3") << std::endl;
	map.put("key1", 9);
	std::cout << "Key1 is now " << map.get("key1") << std::endl;
	return 0;
}