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
			cout << "\n Spisok pust\n";
		}
		else {
			tail->Next = NULL;
			while (head != NULL)  //���� �� ������ �� �����
			{
				TElem *temp = head; //��������� ���������� ��� �������� ������ ���������� ��������
				head = head->Next;
				delete temp; //����������� ����� ������������ ������

			}
			cout << "\n Spisok udalen\n";
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
	}
	/*******************************************************************/
	//�����, ����������� ��������� �� ������� ������� � ������(�����, ��� �������������) ������.
	/*void toBeg() {
	elem = head;
	}*/

	// ��������� ��������� �� �������������� ����� �������� ��������
	/*int GetCurInf(T *&Inf)
	{
	if (elem != tail)
	{
	Inf = &elem->Inf;
	return SUCCESS_OPER;
	}
	return NOT_SUCCESS_OPER;
	}

	// ��������� ����� �������������� ����� �������� ��������
	int GetCurInf(T &Inf)
	{
	if (elem != NULL)
	{
	Inf = elem->Inf;
	return SUCCESS_OPER;
	}
	return NOT_SUCCESS_OPER;
	}

	// ������� � ���������� ��������
	TElem& operator++()
	{
	if (elem != NULL) elem = elem->Next;
	return *this;
	}
	*/
	//������������� �������� !, ������������ ������������� ��������� � ��������� ������
	bool operator! () {
		return (head != NULL); // ���� ������ ����������� ()
	}

	const List<T>& operator=(const List<T>& rList)
	{
		if (rList )
		{
			cout << "as";
		}
	}


	/*bool operator= (T& student_test) {
	TElem *elemVal = student_test.head, *elem = head, *Next;

	}*/
	/*******************************************************************/
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

	List<int> student_test;
	int tmp = 0;
	for (int i = 1; i <= 10; i = i + 2)
	{
		student_test.addToEnd(rand() % 50);
	}
	cout << " My list " << endl;
	student_test.show();

	cout << "Test1\n";
	List<int> student_test1;
	student_test1 = student_test;
	student_test1.show();

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

	//del elementa s inf
	cout << "\n\n Enter your Elem->Inf for delete\n";
	cin >> a;
	student_test.del_inf(a);
	student_test.show();


	//������������ �������� ��������
	cout << "\n\n Enter your Elem->Inf for insert\n";
	cin >> a;
	student_test.sort_elem(a);
	student_test.show();
	
	//delete all
	cout << "\n\n Udalit' spisok\n";
	student_test.del_all();
	*/
	//������������� �������� !, ������������ ������������� ��������� � ��������� ������

	//List<int> student_test3;
	//student_test1 = student_test;
	//student_test1.show();

	/*if (!student_test) cout << "\n ������ �� ����\n";
	else cout << "\n ������ ����\n";
	*/


	cout << endl << endl;

	return 0;
}

