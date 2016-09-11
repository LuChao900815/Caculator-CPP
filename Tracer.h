#pragma once
#ifndef NDEBUG
#ifndef _TRACER_H_
#define _TRACER_H_
#include <map>




void* operator new(size_t size,const char* file, const long line);
void* operator new[](size_t size,const char* file, const long line);
void* operator new(size_t);

void operator delete(void* p);
void operator delete[](void* p);

class Tracer
{
private:
	class Entry
	{
	public:
		Entry(const char* file = 0
			, long line = 0) : file_(file),line_(line){}
		const char* File() const {return  file_;}
		long Line() const {return line_;}
	private:
		const char* file_;
		long  line_;
	};
private:
	class LockCount
	{
	public:
		LockCount(Tracer& t) : tracer_(t)
		{
			tracer_.Lock();
		}
		~LockCount()
		{
			tracer_.UnLock();
		}
	private:
		Tracer& tracer_;
	};

public:
	Tracer(void);
	~Tracer(void);

	void  Add(void* p,const char* file,long line);
	void Remove(void* p);
	void Dump();
private:
	void Lock() {++lockCount_;}
	void UnLock() {--lockCount_;}
public:
	friend class LockCount;
	static bool Ready;
private:
	std::map<void*,Entry> mapEntry_;
	int lockCount_;
};

extern Tracer NewTrace;
#endif // NDEBUG
#endif //_TRACER_H_ 