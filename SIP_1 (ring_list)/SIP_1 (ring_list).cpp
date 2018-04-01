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

	void sort()
	{
		//Скажу честно, это костыль, но... Ни одна программа без костылей не существует, а это самый грамотный костыль (надеюсь, что он самый грамотный), который позволяет реализовать такую сортировку
		tail->Next = NULL; // делаем из кольцевого - односвязный список
		mergeSort(&head); // сортируем
		findTail(); // ищем конец, чтобы закольцевать
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
		* Возвращает указатель на элемент структуры TElem<LISTTYPE> рядом с серединой списка
		* и после обрезаем оригинальный списко перед этим элементом
		*/
		struct TElem *slow, *fast;

		//в случае пустого списка (или один элемент)
		if ((root == NULL) || (root->Next == NULL))
		{
			*list1 = root;
			*list2 = NULL;
			return;
		}
		else
		{
			/*
			два курсора, fast движется в 2 раза быстрее slow, на одну итерацию slow происходит 2 итерации fast
			за счет этого находится середина списка (когда fast == NULL, slow будет ровно в центре списка)
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

	//это твоя сортировка, я ее не стал трогать
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
	cout << "Список отсортирован." << endl;
	}

	//Сортировка слиянием
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
			cout << "\n Список пуст.\n";
		}
		else {
			tail->Next = NULL;
			while (head != NULL)  //Пока по адресу не пусто
			{
				TElem *temp = head; //Временная переменная для хранения адреса следующего элемента
				head = head->Next;
				delete temp; //Освобождаем адрес обозначающий начало

			}
			//cout << "\n Spisok udalen\n";
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
		cout << endl;
	}
	/*******************************************************************/
	//метод, переводящий указатель на текущий элемент в начало(конец, при необходимости) списка.
	/*void toBeg() {
	elem = head;
	}*/

	// Получение указателя на информационную часть текущего элемента
	T& GetCurrInfPtr()
	{
		if (elem)
		{
			return elem->Inf;
		}
		return head->Inf;
	}

	T getCurrInf() // get current elem copyInf - получение копии информационной части 
	{
		if (elem)
		{
			return elem->Inf;
		}
		return head->Inf;
	}

	//переводит указатель на текущий элемент в начало
	void setCurrToHead()
	{
		elem = head;
	}

	//переводит указатель на текущий элемент в конец
	void setCurrToTail()
	{
		elem = tail;
	}


	//проверка существования элементов в списке
	bool isEmpty() const
	{
		return head == 0;
	}

	//перегруженный оператор !, определяющий существование элементов в структуре данных
	bool operator! () {
		return (head != NULL); // если список отсутствует ()
	}

	//получить указатель на голову
	TElem* getHead()
	{
		return head;
	}

	//перегруженный оператор присваивания
	List<T>& operator=(List<T>& right)
	{
		if (!right.isEmpty()) //если есть, что копировать
		{
			// правый список это тот, из которого нужно присвоить значения
			TElem *rightHead = right.getHead(); // получение головы списка из правого
			TElem *rightCurrElem = rightHead; // текущий элемент из этого же списка

			if (this == &right) {
				return *this; // проверка на самоприсваивание
			}

			if (!isEmpty()) //если левый список был не пустым 
			{
				del_all(); //Очищаем его
			}
			do
			{
				addToEnd(rightCurrElem->Inf); //просто добавляем в конец левого списка элементы из правого
				rightCurrElem = rightCurrElem->Next;
			} while (rightCurrElem != rightHead);
		}
		return *this;
	}

	//перегруженный оператор - переход к следующему элементу
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
	/*Деструктор*/
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


	/*	start_time = clock(); // начальное время
	student_test.sort();
	student_test.show();
	end_time = clock(); // конечное время
	search_time = end_time - start_time; // искомое время
	cout << "\n Время работы сортировки: " << ((float)search_time)/CLOCKS_PER_SEC << " с.\n";
	*/


	//student_test.show();


	/*******************************************************/
	/*//копирование списка
	cout << "\n Новый список - копия старого\n";
	List<int> student_test1;
	student_test1 = student_test;
	student_test1.show();

	/************************************************************************/
	/*Текущий элемент*/
	/************************************************************************/

	/*// Получение указателя на информационную часть текущего элемента
	int *a = &student_test1.GetCurrInfPtr();
	cout << "\n Текущий элемент " << *a << endl;

	//проверка того, что выше мы получили действительно указатель на информационную часть элемента списка
	*a = 20;
	student_test1.show();*/
	/*
	//получение копии информационной части
	int b = student_test1.getCurrInf();
	cout << "\n Копия информационной части текущего элемента\n " << b << endl;

	//следующий элемент
	++student_test1;
	b = student_test1.getCurrInf();
	cout << "\n Переходим к следующему элементу\n " << b << endl;

	//переход к голове списка
	student_test1.setCurrToHead();
	b = student_test1.getCurrInf();
	cout << "\n Голова списка - текущий элемент\n " << b << endl;
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
	cout << "\n\n Введите номер элемента, после которого нужна вставка: ";
	cin >> num;
	cout << " Введите значение элемента: ";
	cin >> value;
	student_test.addAfterNum(value, num);
	student_test.show();

	//del elementa s Inf
	cout << "\n\n Enter your Elem->Inf for delete\n";
	cin >> a;
	student_test.del_Inf(a);
	student_test.show();


	//упорядочение текущего элемента
	cout << "\n\n Enter your Elem->Inf for insert\n";
	cin >> a;
	student_test.sort_elem(a);
	student_test.show();

	//delete all
	cout << "\n\n Udalit' spisok\n";
	student_test.del_all();

	//можно вывести список после его удаления, я подправил и теперь есть проверки на пустоту списка

	*/
	//перегруженный оператор !, определяющий существование элементов в структуре данных

	/*if (!student_test) cout << "\n Список не пуст\n";
	else cout << "\n Список пуст\n";
	*/


	cout << endl << endl;

	return 0;
}

