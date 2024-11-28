#pragma once

template<typename T>
class Ptr 
{
	T* mPtr;
public:
    Ptr() : mPtr(nullptr) {}
    Ptr(T* p) : mPtr(p) {}
    Ptr(const Ptr<T>& lp){
        mPtr = lp.mPtr;
        if (mPtr) mPtr->retain();
    }
    ~Ptr() {
		if(mPtr) mPtr->release();
	}
    bool isNull() const { return mPtr == nullptr; }
    bool isNotNull() const { return mPtr != nullptr; }
	void setNull() { if(mPtr) mPtr->release(); mPtr=nullptr; }
    void set(T* lp) {
        setNull();
        mPtr = lp;
        if (mPtr) mPtr->retain(); 
    }
    T* get() const { return mPtr; }
    T* operator->() const{ return mPtr; }
	T& operator*() { return *mPtr; }

    T* operator=(T* lp) { set(lp); return mPtr; }
    T* operator=(const Ptr<T>& lp) { set(lp.mPtr); return mPtr; }
	
};
