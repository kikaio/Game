#pragma once

template<typename T>
class STLAllocator
{
public : 
	using value_type = T;
	STLAllocator() { }

public:
	template<typename Other>
	STLAllocator(const STLAllocator<Other>& ) {}

	T* allocate(size_t count) {
		T* ptr = nullptr;

		const UInt32 memSize = static_cast<UInt32>(count * sizeof(T));
		ptr = static_cast<T*>(XALLOC(memSize));
		return ptr;
	}

	void deallocate(T* ptr, size_t count) {
		XRELEASE(ptr);
		return ;
	}

	template<typename U>
	bool operator==(const STLAllocator<U>&) { return true; }

	template<typename U>
	bool operator!=(const STLAllocator<U>&) { return false; }

};

template<typename T, uint32_t Size>
using Array = array<T, Size>;

template<typename T>
using Vector = vector<T, STLAllocator<T>>;

template<typename T>
using List = list<T, STLAllocator<T>>;

template<typename K, typename V, typename Pred = less<K>>
using Map = map<K, V, Pred, STLAllocator<std::pair<const K, V>>>;


template<typename K, typename Pred = less<K>>
using Set = set<K, Pred, STLAllocator<K>>;

template<typename T>
using Deque = deque<T, STLAllocator<T>>;
template<typename T, typename Container = Deque<T>>
using Stack = stack<T, Container>;

template<typename T, typename Container = Vector<T>, typename Pred = less<typename Container::value_type>>
using priorityQueue = priority_queue<T, Container, Pred>;

using String = basic_string<char, char_traits<char>, STLAllocator<char>>; 

template <typename K, typename T, typename Hasher = hash<K>, typename KeyEq = std::equal_to<K>>
using HashMap = unordered_map<K, T, Hasher, KeyEq, STLAllocator<std::pair<const K, T>>>;

template <typename K, typename Hasher = hash<K>, typename KeyEq = std::equal_to<K>>
using HashSet = unordered_map<K, Hasher, KeyEq, STLAllocator<K>>;

