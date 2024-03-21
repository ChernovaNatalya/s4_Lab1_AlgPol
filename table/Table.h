#pragma once
#include <iostream>
#include "..\polinom\TPolinom.h"
template <class Tn, class Tp>
struct  Polinom
{
	Tn name;
	Tp* polinom;
};

template <class T>
class Table
{
protected: unsigned int size=0;//������� ������
		 unsigned int max_data_count = 0;//������� ����� ����� ���� �������
public:
	int GetDataCount()   const; // ���������� �������
	bool IsEmpty() const;  // �����?
	bool IsFull() const = 0;                       // ���������?
	//��������� 
	virtual int Reset(void) = 0; // ���������� �� ������ ������
	virtual int IsTabEnded(void) const = 0; // ������� ���������?
	virtual int GoNext(void) = 0; // ������� � ��������� ������
	virtual std::string GetKey(void) const = 0;
	virtual T GetValuePtr(void) const = 0;
	//
	virtual bool Add(T obj)=0;
	virtual bool Delete(std::string key)=0;
	virtual T Find(std::string key)=0;
	virtual bool Exist(std::string key)=0;

	friend ostream& operator<<(ostream& os, Table& tab)
	{
		cout << "Table printing" << endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << endl;
		}
		return os;
	}
};
template <class T>
int Table<T>::GetDataCount() const {
	return size;
};
template <class T>
bool Table<T>::IsEmpty() const {
	return size == 0;
}
template<class T>
inline bool Table<T>::IsFull() const
{
	return max_data_count==size ;
}
