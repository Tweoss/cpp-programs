This week you learned about pointers.  For this discussion thread we will focus on pointers.  

Please create and post a small tutorial on pointers.  Your audience for this tutorial are your fellow students (first year CS students, with little prior knowledge on pointers).  This tutorial should all come from YOUR understanding of pointers.  Be sure to support the information in your simple tutorial with working examples.  Also included within your simple tutorial should be links to at least 3 resources that can be used by your audience to learn more about pointers.

Once you have made your post, please respond to at least one other student post.


Hello World and its many inhabitants,

Many posts have been made about demonstrating how to utilize pointers with individual variables, classes, and their destructors. Pointers, however, have many more uses than as a reference to singular values. 

Pointers are inherently related to memory; they quite literally point to locations in memory. This allows for interesting and varied applications. Arrays, matrices, and linked lists are all structures that depend on pointers. 

A very common and useful structure is hashmaps, which uses pointers in a fashion unlike other posts demonstrate. Here is an extremely pared-down implementation of a basic hash map

```cpp

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
```

Here, pointers are used (via arrays) to interact directly with memory. A key (of type string) becomes a pointer to a location in memory thereby making lookup functions independent of the number of records in the map. In this way, doing a lookup on even millions of records, say of student grades, could take almost constant time. 