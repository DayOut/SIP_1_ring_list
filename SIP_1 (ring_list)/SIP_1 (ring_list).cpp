// sip_lab_1.cpp: определяет точку входа для консольного приложения.
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
	TElem *head, *tail, *elem; // переменная указатель на голову списка
							   //elem - это указатель на текущий элемент, пока класс существует - существует список и этот элемент
public:
	List() { head = NULL; }

	List(T value)
	{
		head->Inf = value;
		head->Next = head;
		tail = head;
	}


	//функция добавления элемента в конец списка
	bool addToEnd(T value) // add_end / ...
	{
		if (!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->Inf = value;	// записываем значение 
			head->Next = head;	// указатель на последний элемент
			tail = head;
		}
		else
		{
			elem = head;
			while (elem != tail) // в случае кольцевого списка проверяем есть ли данный элемент последним
			{
				elem = elem->Next; // доходим до конца списка
			}
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->Inf = value;	// записываем значение 
			tmp->Next = head;	// для кольцевого списка
			elem->Next = tmp;
			tail = tmp;
		}
		return true;
	}


	//Добавление в начало списка
	void addToBegin(T value) // add_to_begin / add_begin
	{
		if (!head) // если список отсутствует ()
		{
			head = new TElem;	// Выделяем память под новый элемент
			head->Inf = value;	// записываем значение
			head->Next = head;	// указатель на последний элемент
			tail = head;
		}
		else
		{
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->Inf = value;	// записываем значение
			tmp->Next = head;	// указатель с первого элемента на второй
			head = tmp;			// меняем голову на новый элемент
			tail->Next = head;	// меняем указатель на начало списка
		}
	}


	//функция добавления элемента после заданного
	void addAfterNum(T value, T num) // add_end / ...
	{
		elem = head;
		int k = 1;
		while (elem != tail && k != num)
		{
			elem = elem->Next; // доходим до конца списка
			k = k + 1;
		}
		if (num > k) {
			cout << " Элемент не может быть вставлен.\n";
			return;
		}
		TElem *tmp = new TElem; // выделяем память на новый элемент
		tmp->Inf = value;	// записываем значение 
		tmp->Next = elem->Next;
		elem->Next = tmp;
	}

	//Поиск элемента
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

	//удаление элемента с указанной инф. частью
	void del_inf(T a) {
		if (elem->Inf == a) {
			TElem * tmp = head; // Убираем его
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
			TElem * tmp = elem->Next; // Убираем его
			elem->Next = elem->Next->Next;
			delete tmp;
			cout << "\nElement = " << a << " has been deleted" << endl;
		}
	}


	//delete all
	void del_all() {
		if (!head) // если список отсутствует ()
		{
			cout << "\n Spisok pust\n";
		}
		else {
			tail->Next = NULL;
			while (head != NULL)  //Пока по адресу не пусто
			{
				TElem *temp = head; //Временная переменная для хранения адреса следующего элемента
				head = head->Next;
				delete temp; //Освобождаем адрес обозначающий начало

			}
			cout << "\n Spisok udalen\n";
			head = NULL; //Обнуляем голову
		}
	}

	//упорядочение нового элемента
	void sort_elem(T value) {
		elem = head;
		if (head->Inf >= value) {
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->Inf = value;	// записываем значение
			tmp->Next = head;	// указатель с первого элемента на второй
			head = tmp;			// меняем голову на новый элемент
			tail->Next = head;	// меняем указатель на начало списка
		}
		else {
			while (elem != tail && value > elem->Next->Inf)
			{
				cout << elem->Inf << "   \n";
				elem = elem->Next; // доходим до конца списка
			}
			TElem *tmp = new TElem; // выделяем память на новый элемент
			tmp->Inf = value;	// записываем значение 
			tmp->Next = elem->Next;
			elem->Next = tmp;
		}
	}

	//изменение информационной части эдемента
	void change_inf() {
		cout << "\nEnter elem->Inf you want to change\n";
		int a, b;
		cin >> a;
		cout << "\nEnter New Inf you want\n";
		cin >> b;

	}

	//упорядочение текущего элемента
	void sort_now_elem() {
		cout << "\n Текущий элемент - " << elem->Inf << "\n";
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

	//Вывод списка
	void show()
	{
		if (!head) // если список отсутствует ()
		{
			cout << "\n Spisok pust\n";
		}
		else {
			elem = head;
			do
			{
				cout << elem->Inf << "   ";
				elem = elem->Next; //доходим до конца списка
			} while (elem != head); //в случае кольцевого списка проверяем есть ли данный элемент последним
		}
	}
	/*******************************************************************/
	//метод, переводящий указатель на текущий элемент в начало(конец, при необходимости) списка.
	/*void toBeg() {
	elem = head;
	}*/

	// Получение указателя на информационную часть текущего элемента
	/*int GetCurInf(T *&Inf)
	{
	if (elem != tail)
	{
	Inf = &elem->Inf;
	return SUCCESS_OPER;
	}
	return NOT_SUCCESS_OPER;
	}

	// Получение копии информационной части текущего элемента
	int GetCurInf(T &Inf)
	{
	if (elem != NULL)
	{
	Inf = elem->Inf;
	return SUCCESS_OPER;
	}
	return NOT_SUCCESS_OPER;
	}

	// Переход к следующему элементу
	TElem& operator++()
	{
	if (elem != NULL) elem = elem->Next;
	return *this;
	}
	*/
	//перегруженный оператор !, определяющий существование элементов в структуре данных
	bool operator! () {
		return (head != NULL); // если список отсутствует ()
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
			do   //Пока по адресу не пусто
			{
				TElem *temp = head; //Временная переменная для хранения адреса следующего элемента
				head = head->Next;
				delete temp; //Освобождаем адрес обозначающий начало
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
	cout << "\n\n Введите номер элемента, после которого нужна вставка: ";
	cin >> num;
	cout << " Введите значение элемента: ";
	cin >> value;
	student_test.addAfterNum(value, num);
	student_test.show();

	//del elementa s inf
	cout << "\n\n Enter your Elem->Inf for delete\n";
	cin >> a;
	student_test.del_inf(a);
	student_test.show();


	//упорядочение текущего элемента
	cout << "\n\n Enter your Elem->Inf for insert\n";
	cin >> a;
	student_test.sort_elem(a);
	student_test.show();
	
	//delete all
	cout << "\n\n Udalit' spisok\n";
	student_test.del_all();
	*/
	//перегруженный оператор !, определяющий существование элементов в структуре данных

	//List<int> student_test3;
	//student_test1 = student_test;
	//student_test1.show();

	/*if (!student_test) cout << "\n Список не пуст\n";
	else cout << "\n Список пуст\n";
	*/


	cout << endl << endl;

	return 0;
}

