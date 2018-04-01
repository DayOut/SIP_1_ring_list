// sip_lab_1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

template <class T>
class List
{
private:
	struct TElem
	{
		T Inf;
		TElem *Next;
	};
	TElem *head, *tail, *elem; // ���������� ��������� �� ������ ������
							   //elem - ��� ��������� �� ������� �������, ���� ����� ���������� - ���������� ������ � ���� �������
public:
	List() { head = NULL; }

	List(T value)
	{
		head->Inf = value;
		head->Next = head;
		tail = head;
	}

	void sort()
	{
		//����� ������, ��� �������, ��... �� ���� ��������� ��� �������� �� ����������, � ��� ����� ��������� ������� (�������, ��� �� ����� ���������), ������� ��������� ����������� ����� ����������
		tail->Next = NULL; // ������ �� ���������� - ����������� ������
		mergeSort(&head); // ���������
		findTail(); // ���� �����, ����� ������������
	}

	void findTail()
	{
		while (elem->Next)
		{
			elem = elem->Next;
		}
		tail = elem;
		tail->Next = head;
	}


	void mergeSort(struct TElem **root)
	{
		struct TElem *list1, *list2;
		struct TElem *head = *root;
		if ((head == NULL) || (head->Next == NULL))
		{
			return;
		}

		findMid(head, &list1, &list2);

		mergeSort(&list1);
		mergeSort(&list2);

		*root = mergeList(list1, list2);

	}


	TElem* mergeList(struct TElem *list1, struct TElem *list2)
	{
		struct TElem temphead = { 0, NULL }, *tail = &temphead;

		while ((list1 != NULL) && (list2 != NULL))
		{
			struct TElem **min = (list1->Inf < list2->Inf) ? &list1 : &list2;
			struct TElem *next = (*min)->Next;
			tail = tail->Next = *min;
			*min = next;
		}
		tail->Next = list1 ? list1 : list2;
		return temphead.Next;
	}


	void findMid(struct TElem *root, struct TElem **list1, struct TElem **list2)
	{
		/**
		* ���������� ��������� �� ������� ��������� TElem<LISTTYPE> ����� � ��������� ������
		* � ����� �������� ������������ ������ ����� ���� ���������
		*/
		struct TElem *slow, *fast;

		//� ������ ������� ������ (��� ���� �������)
		if ((root == NULL) || (root->Next == NULL))
		{
			*list1 = root;
			*list2 = NULL;
			return;
		}
		else
		{
			/*
			��� �������, fast �������� � 2 ���� ������� slow, �� ���� �������� slow ���������� 2 �������� fast
			�� ���� ����� ��������� �������� ������ (����� fast == NULL, slow ����� ����� � ������ ������)
			*/
			slow = root;
			fast = root->Next;
			while (fast != NULL)
			{
				fast = fast->Next;
				if (fast != NULL)
				{
					slow = slow->Next;
					fast = fast->Next;
				}
			}

			*list1 = root;
			*list2 = slow->Next;
			slow->Next = NULL;
		}
	}

	//��� ���� ����������, � �� �� ���� �������
	/*
	void sort() {
	TElem *tmp = NULL, *prev = NULL;
	elem = head;
	bool flag = false;
	do
	{
	flag = false;
	elem = head;
	while (elem->Next != head)
	{
	if (elem->Inf > elem->Next->Inf)
	{
	if (elem == head)
	{
	tmp = elem;
	elem = tmp->Next;
	tmp->Next = elem->Next;
	elem->Next = tmp;
	head = elem;
	tail->Next = head;
	flag = true;
	}
	else
	{
	tmp = elem;
	elem = tmp->Next;
	tmp->Next = elem->Next;
	elem->Next = tmp;
	prev->Next = elem;
	flag = true;
	}
	}
	prev = elem;
	elem = elem->Next;
	}
	} while (flag);
	cout << "������ ������������." << endl;
	}

	//���������� ��������
	List *merge(List *a, List *b)
	{
	if (!a)
	return b;
	if (!b)
	return a;

	List* c = 0;
	if (a->Inf <= b->Inf)
	{
	c = a;
	c->Next = merge(a->Next, b);
	}
	else
	{
	c = b;
	c->Next = merge(a, b->Next);
	}
	return c;
	}

	List *mergesort(List *head)
	{
	if (head == 0 || head->Next == 0) return head;
	List *a = head, *b = head->Next;
	while ((b != 0) && (b->Next != 0))
	{
	head = head->Next;
	b = b->Next->Next;
	}
	b = head->Next;
	head->Next = NULL;
	return merge(mergesort(a), mergesort(b));
	}
	*/

	//������� ���������� �������� � ����� ������
	bool addToEnd(T value) // add_end / ...
	{
		if (!head) // ���� ������ ����������� ()
		{
			head = new TElem;	// �������� ������ ��� ����� �������
			head->Inf = value;	// ���������� �������� 
			head->Next = head;	// ��������� �� ��������� �������
			tail = head;
		}
		else
		{
			elem = head;
			while (elem != tail) // � ������ ���������� ������ ��������� ���� �� ������ ������� ���������
			{
				elem = elem->Next; // ������� �� ����� ������
			}
			TElem *tmp = new TElem; // �������� ������ �� ����� �������
			tmp->Inf = value;	// ���������� �������� 
			tmp->Next = head;	// ��� ���������� ������
			elem->Next = tmp;
			tail = tmp;
		}
		return true;
	}


	//���������� � ������ ������
	void addToBegin(T value) // add_to_begin / add_begin
	{
		if (!head) // ���� ������ ����������� ()
		{
			head = new TElem;	// �������� ������ ��� ����� �������
			head->Inf = value;	// ���������� ��������
			head->Next = head;	// ��������� �� ��������� �������
			tail = head;
		}
		else
		{
			TElem *tmp = new TElem; // �������� ������ �� ����� �������
			tmp->Inf = value;	// ���������� ��������
			tmp->Next = head;	// ��������� � ������� �������� �� ������
			head = tmp;			// ������ ������ �� ����� �������
			tail->Next = head;	// ������ ��������� �� ������ ������
		}
	}


	//������� ���������� �������� ����� ���������
	void addAfterNum(T value, T num) // add_end / ...
	{
		elem = head;
		int k = 1;
		while (elem != tail && k != num)
		{
			elem = elem->Next; // ������� �� ����� ������
			k = k + 1;
		}
		if (num > k) {
			cout << " ������� �� ����� ���� ��������.\n";
			return;
		}
		TElem *tmp = new TElem; // �������� ������ �� ����� �������
		tmp->Inf = value;	// ���������� �������� 
		tmp->Next = elem->Next;
		elem->Next = tmp;
	}

	//����� ��������
	void found(T a) {
		while (elem->Inf != a)
		{
			if (elem == tail && elem->Inf != a) {
				cout << "Element " << a << " is not exists.";
				return;
			}
			elem = elem->Next;
		}
		cout << " Element exists.\n";
	}

	//�������� �������� � ��������� ���. ������
	void del_inf(T a) {
		if (elem->Inf == a) {
			TElem * tmp = head; // ������� ���
			tail->Next = head->Next;
			head = head->Next;
			elem = head;
			delete tmp;
			cout << "\nElement = " << a << " has been deleted" << endl;
		}
		else {
			while (elem->Next->Inf != a)
			{
				if (elem == tail && elem->Inf != a) {
					cout << "Element " << a << " is not exists.\n";
					return;
				}
				elem = elem->Next;
			}
			TElem * tmp = elem->Next; // ������� ���
			elem->Next = elem->Next->Next;
			delete tmp;
			cout << "\nElement = " << a << " has been deleted" << endl;
		}
	}


	//delete all
	void del_all() {
		if (!head) // ���� ������ ����������� ()
		{
			cout << "\n ������ ����.\n";
		}
		else {
			tail->Next = NULL;
			while (head != NULL)  //���� �� ������ �� �����
			{
				TElem *temp = head; //��������� ���������� ��� �������� ������ ���������� ��������
				head = head->Next;
				delete temp; //����������� ����� ������������ ������

			}
			//cout << "\n Spisok udalen\n";
			head = NULL; //�������� ������
		}
	}

	//������������ ������ ��������
	void sort_elem(T value) {
		elem = head;
		if (head->Inf >= value) {
			TElem *tmp = new TElem; // �������� ������ �� ����� �������
			tmp->Inf = value;	// ���������� ��������
			tmp->Next = head;	// ��������� � ������� �������� �� ������
			head = tmp;			// ������ ������ �� ����� �������
			tail->Next = head;	// ������ ��������� �� ������ ������
		}
		else {
			while (elem != tail && value > elem->Next->Inf)
			{
				cout << elem->Inf << "   \n";
				elem = elem->Next; // ������� �� ����� ������
			}
			TElem *tmp = new TElem; // �������� ������ �� ����� �������
			tmp->Inf = value;	// ���������� �������� 
			tmp->Next = elem->Next;
			elem->Next = tmp;
		}
	}

	//��������� �������������� ����� ��������
	void change_inf() {
		cout << "\nEnter elem->Inf you want to change\n";
		int a, b;
		cin >> a;
		cout << "\nEnter New Inf you want\n";
		cin >> b;

	}

	//������������ �������� ��������
	void sort_now_elem() {
		cout << "\n ������� ������� - " << elem->Inf << "\n";
		TElem *tmp = new TElem;
		tmp = elem;
		if (tmp == head) {
			head = head->Next;
			tail->Next = head;
		}
		while (elem->Next != tmp) {
			elem = elem->Next;

		}
		elem->Next = tmp->Next;
		while (tmp->Inf > elem->Next->Inf && elem->Next != tmp)
		{
			elem = elem->Next;
		}
		tmp->Next = elem->Next;
		elem->Next = tmp;
	}

	//����� ������
	void show()
	{
		if (!head) // ���� ������ ����������� ()
		{
			cout << "\n Spisok pust\n";
		}
		else {
			elem = head;
			do
			{
				cout << elem->Inf << "   ";
				elem = elem->Next; //������� �� ����� ������
			} while (elem != head); //� ������ ���������� ������ ��������� ���� �� ������ ������� ���������
		}
		cout << endl;
	}
	/*******************************************************************/
	//�����, ����������� ��������� �� ������� ������� � ������(�����, ��� �������������) ������.
	/*void toBeg() {
	elem = head;
	}*/

	// ��������� ��������� �� �������������� ����� �������� ��������
	T& GetCurrInfPtr()
	{
		if (elem)
		{
			return elem->Inf;
		}
		return head->Inf;
	}

	T getCurrInf() // get current elem copyInf - ��������� ����� �������������� ����� 
	{
		if (elem)
		{
			return elem->Inf;
		}
		return head->Inf;
	}

	//��������� ��������� �� ������� ������� � ������
	void setCurrToHead()
	{
		elem = head;
	}

	//��������� ��������� �� ������� ������� � �����
	void setCurrToTail()
	{
		elem = tail;
	}


	//�������� ������������� ��������� � ������
	bool isEmpty() const
	{
		return head == 0;
	}

	//������������� �������� !, ������������ ������������� ��������� � ��������� ������
	bool operator! () {
		return (head != NULL); // ���� ������ ����������� ()
	}

	//�������� ��������� �� ������
	TElem* getHead()
	{
		return head;
	}

	//������������� �������� ������������
	List<T>& operator=(List<T>& right)
	{
		if (!right.isEmpty()) //���� ����, ��� ����������
		{
			// ������ ������ ��� ���, �� �������� ����� ��������� ��������
			TElem *rightHead = right.getHead(); // ��������� ������ ������ �� �������
			TElem *rightCurrElem = rightHead; // ������� ������� �� ����� �� ������

			if (this == &right) {
				return *this; // �������� �� ����������������
			}

			if (!isEmpty()) //���� ����� ������ ��� �� ������ 
			{
				del_all(); //������� ���
			}
			do
			{
				addToEnd(rightCurrElem->Inf); //������ ��������� � ����� ������ ������ �������� �� �������
				rightCurrElem = rightCurrElem->Next;
			} while (rightCurrElem != rightHead);
		}
		return *this;
	}

	//������������� �������� - ������� � ���������� ��������
	List<T>& operator++()
	{
		if (elem)
		{
			elem = elem->Next;
		}
		else
		{
			elem = head;
		}
		return *this;
	}

	/*******************************************************************/
	/*����������*/
	~List()
	{
		if (head)
		{
			tail->Next = NULL;
			do   //���� �� ������ �� �����
			{
				TElem *temp = head; //��������� ���������� ��� �������� ������ ���������� ��������
				head = head->Next;
				delete temp; //����������� ����� ������������ ������
			} while (head != NULL);
		}
	}


};

using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	unsigned int start_time, end_time, search_time;

	List<int> student_test;
	for (int i = 1; i <= 10; i = i + 1)
	{
		student_test.addToEnd(rand() % 50);
		//student_test.addToEnd(i);
	}
	cout << " My list " << endl;
	student_test.show();

	cout << " Sort " << endl;
	student_test.sort();

	student_test.show();


	/*	start_time = clock(); // ��������� �����
	student_test.sort();
	student_test.show();
	end_time = clock(); // �������� �����
	search_time = end_time - start_time; // ������� �����
	cout << "\n ����� ������ ����������: " << ((float)search_time)/CLOCKS_PER_SEC << " �.\n";
	*/


	//student_test.show();


	/*******************************************************/
	/*//����������� ������
	cout << "\n ����� ������ - ����� �������\n";
	List<int> student_test1;
	student_test1 = student_test;
	student_test1.show();

	/************************************************************************/
	/*������� �������*/
	/************************************************************************/

	/*// ��������� ��������� �� �������������� ����� �������� ��������
	int *a = &student_test1.GetCurrInfPtr();
	cout << "\n ������� ������� " << *a << endl;

	//�������� ����, ��� ���� �� �������� ������������� ��������� �� �������������� ����� �������� ������
	*a = 20;
	student_test1.show();*/
	/*
	//��������� ����� �������������� �����
	int b = student_test1.getCurrInf();
	cout << "\n ����� �������������� ����� �������� ��������\n " << b << endl;

	//��������� �������
	++student_test1;
	b = student_test1.getCurrInf();
	cout << "\n ��������� � ���������� ��������\n " << b << endl;

	//������� � ������ ������
	student_test1.setCurrToHead();
	b = student_test1.getCurrInf();
	cout << "\n ������ ������ - ������� �������\n " << b << endl;
	*/
	/************************************************************************/
	/**/
	/************************************************************************/
	/*
	//add to end
	tmp = rand() % 100;
	cout << endl << "\n Add to end " << tmp << endl;
	student_test.addToEnd(tmp);
	student_test.show();
	cout << endl;

	//add to beg
	tmp = rand() % 100;
	cout << endl << "\n Add to beg " << tmp << endl;
	student_test.addToBegin(tmp);
	student_test.show();


	//poisk elementa
	cout << "\n\n Enter your Elem->Inf\n";
	int a;
	cin >> a;
	student_test.found(a);

	student_test.sort_now_elem();
	student_test.show();
	/*


	//add after num
	int num, value;
	cout << "\n\n ������� ����� ��������, ����� �������� ����� �������: ";
	cin >> num;
	cout << " ������� �������� ��������: ";
	cin >> value;
	student_test.addAfterNum(value, num);
	student_test.show();

	//del elementa s Inf
	cout << "\n\n Enter your Elem->Inf for delete\n";
	cin >> a;
	student_test.del_Inf(a);
	student_test.show();


	//������������ �������� ��������
	cout << "\n\n Enter your Elem->Inf for insert\n";
	cin >> a;
	student_test.sort_elem(a);
	student_test.show();

	//delete all
	cout << "\n\n Udalit' spisok\n";
	student_test.del_all();

	//����� ������� ������ ����� ��� ��������, � ��������� � ������ ���� �������� �� ������� ������

	*/
	//������������� �������� !, ������������ ������������� ��������� � ��������� ������

	/*if (!student_test) cout << "\n ������ �� ����\n";
	else cout << "\n ������ ����\n";
	*/


	cout << endl << endl;

	return 0;
}

