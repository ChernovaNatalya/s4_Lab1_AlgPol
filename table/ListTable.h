#pragma once
#include <iostream>
#include "..\polinom\TPolinom.h"
#include "..\table\Table.h"
using namespace std;

template <class T>
struct Item {
	T info; //������� 
	Item* next=nullptr; // ������ �� ���������
};

template <class T>
class ListTable : public Table<T> {
protected:
	unsigned int size = 0;//������� ������
	unsigned int max_data_count = 0;//������� ����� ����� ���� �������

	Item* first = nullptr;
	Item* current = nullptr;
	Item* prev = nullptr;

public:
	int GetDataCount() const { return size }// ���������� �������
	bool IsFull() const {
			return true; // ��� ����������
	}  // ���������?
	
	   //��������� 
	int Reset(void) {
		current = first;
		prev = nullptr;
		return 0;
	}// ���������� �� ������ ������
	int IsTabEnded(void) { return current->next == nullptr } // ������� ���������?
	int GoNext(void) {
		if (size == 0) throw "size =0 ";
		prev = current;
		if (!IsTabEnded()) {
			current = current->next;
		}
		else Reset();
		return 1;
	} // ������� � ��������� ������
	string GetKey(void) {
		if (current != nullptr) {
			return current->info.name;
		}
		else {
			throw "Empty";
		}
	}
	T GetValuePtr(void) {
		if (current != nullptr) {
			return current->info;
		}
		else {
			throw "Empty";
		}
	}
	//

	bool Add(T obj) {//  T = Polinom     ��������� ������ Current
		Item<T>* newItem = new Item<T>;
		newItem->info = obj;
		newItem->next = first;
		if (size == 0) { first = newItem; current = newItem; }
		else {
			bool b = Exist(obj.name);
			if (b) { delete newItem; return false; }
			else { 
				newItem->next = current;
				if (Current != first) {
					prev->next = newItem;
				}
				else {
					first = newItem;
				}
				prev = newItem;
			}
		}
		size++;
		return true;
	}
	bool Delete(std::string key) {
		if (size == 0) return true;
		Item<T>* tmp = first;
		Item<T>* tmp_w = nullptr;
		while (tmp != nullptr && tmp->info->name != key) {
			tmp_w = tmp;
			tmp = tmp->next;
		}
		if (tmp->info->name == key) {
			if ((tmp == current)|| (tmp == prev))  Reset();
			if (tmp == first) { 
				if (first == current) { GoNext(); prev = nullptr; }
			first = tmp->next; }
			tmp_w->next = tmp->next;
			delete tmp;
			size--;
		}
	}
	T Find(std::string key) {
		if (size == 0) throw "size=0";
		Item<T>* tmp = first;
		Item<T>* tmp_w = nullptr;
		while (tmp != nullptr && tmp->info->name != key) {
			tmp_w = tmp;
			tmp = tmp->next;
		}
		if (tmp->info->name == key) return tmp->info;
		throw "cant find";
	}
	bool Exist(std::string key) {
		if (size == 0) return false;
		Item<T>* tmp = first;
		Item<T>* tmp_w = nullptr;
		while (tmp != nullptr && tmp->info->name != key) {
			tmp_w = tmp;
			tmp = tmp->next;
		}
		return (tmp->info->name == key);
	}

};
///*
//template <class T>
//int Table<T>::GetDataCount() const {
//	return size;
//};
//template <class T>
//bool Table<T>::IsEmpty() const {
//	return size == 0;
//}
//template<class T>
//bool Table<T>::IsFull() const
//{
//	return max_data_count == size;
//}
///*
//
//
//
//class ListTable : Table {
//	virtual void AddPolinom(Polinom<Tn, Tp> pol) {
//		Item* cur, * prev;
//		cur = ptab;
//		if (!cur) {
//			cur.info = pol;
//		}
//		while (cur->next) { /* ���� ������ �������� */
//			prev = cur;
//			cur = cur->next;
//		}
//		cur.info = pol;
//	}
//	virtual void DelPolinom(std::string polinom_name) {
//		Item* cur, * prev;
//		cur = ptab;
//		/* ���������, ���� �� � ������� �������� */
//		if (!cur)
//			return -1; /* ������� ����� � ����� */
//		/* ��������, ��������� ������� ������ ������� ������� */
//		if (cur.info.name == polinom_name) {
//			/* ������� ������ ������� */
//			ptab = cur->next;
//			delete cur;
//			return 0;
//		}
//		/* ���� ��������� ������� ����� ������ ��������� ������� */
//		while (cur->next) { /* ���� ������ �������� */
//			prev = cur;
//			cur = cur->next;
//			if (cur.info.name == polinom_name) {
//				/* ����� �������, ������� ���� ������� */
//				prev->next = cur->next;
//				delete cur;
//				return 0;
//			}
//		}
//		/* ������������ ����� �� ����� � � ������� ��� �������� � ������ k */
//		return -1;
//	}
//	virtual Polinom<Tn, Tp> FindPolinom(std::string polinom_name) {
//		Item* cur, * prev;
//		cur = ptab;
//		/* ���������, ���� �� � ������� �������� */
//		if (!cur)
//			return -1; /* ������� ����� � ����� */
//		/* ��������, ��������� ������� ������ ������� ������� */
//		if (cur.info.name == polinom_name) {
//			/* ������� ������ ������� */
//			ptab = cur->next;
//			delete cur;
//			return 0;
//		}
//		/* ���� ��������� ������� ����� ������ ��������� ������� */
//		while (cur->next) { /* ���� ������ �������� */
//			prev = cur;
//			cur = cur->next;
//			if (cur->key == k) {
//				/* ����� �������, ������� ���� ������� */
//				prev->next = cur->next;
//				delete cur;
//				return 0;
//			}
//		}
//		/* ������������ ����� �� ����� � � ������� ��� �������� � ������k */
//		return -1;
//	}
//};
//
//int del1(int k) {
//	Item* cur, * prev;
//	cur = ptab;
//	/* ���������, ���� �� � ������� �������� */
//	if (!cur)
//		return -1; /* ������� ����� � ����� */
//	/* ��������, ��������� ������� ������ ������� ������� */
//	if (cur->key == k) {
//		/* ������� ������ ������� */
//		ptab = cur->next;
//		delete cur;
//		return 0;
//	}
//	/* ���� ��������� ������� ����� ������ ��������� ������� */
//	while (cur->next) { /* ���� ������ �������� */
//		prev = cur;
//		cur = cur->next;
//		if (cur->key == k) {
//			/* ����� �������, ������� ���� ������� */
//			prev->next = cur->next;
//			delete cur;
//			return 0;
//		}
//	}
//	/* ������������ ����� �� ����� � � ������� ��� �������� � ������k */
//	return -1;
//}
//
//
//int del2(int k) {
//	Item* cur, ** pptr;
//	pptr = &ptab; /* ��������� �� ��������� �� ������ ������� ������� */
//	/* ���� ��������� ������� ����� ���� ��������� ������� */
//	while (*pptr) { /* ��� ���� �������� */
//		if ((*pptr)->key == k) {
//			/* ����� �������, ������� ���� ������� */
//			cur = *pptr; /* ��������� �� ��������� ������� */
//			*pptr = cur->next;
//			Delete cur;
//			return 0;
//		}
//		/* ������������ � ���������� �������� ������� */
//		pptr = &(*pptr)->next;
//	}
//	/* ������������ ����� �� ����� � � ������� ��� �������� � ������k */
//	return-1;
//}
//
//*/