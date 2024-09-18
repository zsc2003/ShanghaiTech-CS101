#include "dsa.h"
#include <cstdlib>
#include <functional>
#include <optional>

#define TODO()                                                                 \
  do {                                                                         \
    exit(1);                                                                   \
  } while (0)

namespace part_queue {
Queue::Queue()
{
	head = 0;
	tail = 0;
}
bool Queue::empty() const
{
	if (head >= tail)
		return true;
	return false;
}
std::optional<Value> Queue::pop()
{
	if (empty())
		return std::nullopt;
	++head;
	return std::optional(data[head-1]);
}
void Queue::push(Value value)
{
	data[tail] = value;
	++tail;
}
} // namespace part_queue



namespace part_stack {
Stack::Stack()
{
	stack_top = 0;
}
bool Stack::empty() const
{
	if (stack_top == 0)
		return true;
	return false;
}
std::optional<Value> Stack::pop()
{
	if(empty())
		return std::nullopt;
	--stack_top;
	return std::optional(data[stack_top+1]);
}
void Stack::push(Value value)
{
	++stack_top;
	data[stack_top] = value;
}
} // namespace part_stack

namespace part_hash_table {
using Status = Slot::Status;
HashTable::HashTable(std::function<size_t(Key)> hash_func)
{
	this->hash_func=hash_func;
	for(auto element : this->slots)
		element=Slot();
}
std::array<Slot, CAPACITY> HashTable::dump() const
{
	return this->slots;
}

bool HashTable::insert(Key key, Value value)
{
	if(lookup(key))
		return false;
	std::size_t pos=this->hash_func(key)%CAPACITY;
	while(this->slots[pos].status==Status::occupied)
		pos=(pos+1)%CAPACITY;
	slots[pos].status=Status::occupied;
	slots[pos].key=key;
	slots[pos].value=value;
	return true;
}

std::optional<Value> HashTable::lookup(Key key) const
{
	std::size_t pos=this->hash_func(key)%CAPACITY;
	while(this->slots[pos].status!=Status::empty)
	{
		if((slots[pos].status==Status::occupied)&&(slots[pos].key==key))
			return std::optional(slots[pos].value);
		pos=(pos+1)%CAPACITY;
	}		
	return std::nullopt;
}

bool HashTable::erase(Key key)
{
	if(!lookup(key))
		return false;
	std::size_t pos=this->hash_func(key)%CAPACITY;
	while(this->slots[pos].status!=Status::empty)
	{
		if((slots[pos].status==Status::occupied)&&(slots[pos].key==key))
			break;
		pos=(pos+1)%CAPACITY;
	}		
	slots[pos].status=Status::erased;
	return true;
}
} // namespace part_hash_table
