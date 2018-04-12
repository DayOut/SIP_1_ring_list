// sip_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "blist.h"
#include <iostream>
#include <ctime>

template <typename T > class Iterator;

template <class T>
class List
{
private:
    friend Iterator<T>;

    struct TElem
    {
        T Inf;
        TElem *Next;
    };
    TElem *head, *tail, *elem; //указатель на голову списка, elem - указатель на текущий элемент
    int k = 0;

public:

    
   
    List() 
    { 
        head = NULL; 
        //-------------------------------------------------------------------------------------------
        tail = NULL; // надо обнулять все переменные
        elem = NULL; // в том числе и хвост и текущий элемент
        //-------------------------------------------------------------------------------------------
    }

    //-------------------------------------------------------------------------------------------
    //Это вообще не надо, его надо удалить
    
    /*List(T value)
    {
        head->Inf = value;
        head->Next = head;
        tail = head;
    }*/
    //-------------------------------------------------------------------------------------------


    void sort()
    {
        //-------------------------------------------------------------------------------------------
        //тут нужна проверка на пустоту списка
        //-------------------------------------------------------------------------------------------
        if (!head) // если списка нет - то и сортировать нечего
            return;

        tail->Next = NULL; // делаем из кольцевого - односвязный список
        mergeSort(head); // сортируем
        findTail(); // ищем конец, чтобы закольцевать
        cout << "\n Количество рекурсивных вызовов: " << k << "\n";
        k = 0;
    }

    void findTail()
    {
        TElem *tmp = head;
        while (tmp->Next)
        {
            tmp = tmp->Next;
        }
        tail = tmp;
        tail->Next = head;
    }

    //-------------------------------------------------------------------------------------------
    // тут было mergeSort(struct TElem **root), за что он ко мне приколупался, мол зачем две звездочки
    // так что теперь берем просто элемент по адресу
    //-------------------------------------------------------------------------------------------
    void mergeSort(TElem **root)
    {
        // вылезла прикольная штука, иногда что-то в программе зацикливается, но я не могу пока понять 
        // алгоритм, который приводит к этой баге

        k++;
        TElem *list1, *list2;
        TElem *head = root;
        if ((head == NULL) || (head->Next == NULL))
        {
            return;
        }

        findMid(head, &list1, &list2);

        mergeSort(&list1);
        mergeSort(&list2);

        root = mergeList(list1, list2);

    }

    TElem* mergeList(TElem *list1, TElem *list2)
    {
        TElem temphead = { 0, NULL }, *tail = &temphead;

        while ((list1 != NULL) && (list2 != NULL))
        {
            TElem **min = (list1->Inf < list2->Inf) ? &list1 : &list2;
            TElem *Next = (*min)->Next;
            tail = tail->Next = *min;
            *min = Next;
        }
        tail->Next = list1 ? list1 : list2;
        return temphead.Next;
    }

    void findMid(TElem *root, TElem **list1, TElem **list2)
    {
        /**
        Возвращает указатель на элемент структуры TElem<T> рядом с серединой списка
        и после обрезаем оригинальный список перед этим элементом
        */
        TElem *slow, *fast;

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

    //функция добавления элемента в конец списка
    bool addToEnd(T value) // add_end / ...
    {
        //-------------------------------------------------------------------------------------------
        //создаем элемент
        TElem *tmp = new TElem; // выделяем память на новый элемент
        tmp->Inf = value;	// записываем значение
        tmp->Next = head;	// указатель с первого элемента на второй

        if (!head) // если список отсутствует ()
        {
            //помещаем его в начало и закольцовываем
            head = tmp;
            tail = head;
            elem = head;
        }
        else
        {
            tail->Next = tmp;
            tail = tmp;
        }
        //-------------------------------------------------------------------------------------------
        /* //вроде выглядит попроще чем было
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
        }*/
        return true;
    }


    //Добавление в начало списка
    void addToBegin(T value) 
    {
        //-------------------------------------------------------------------------------------------
        TElem *tmp = new TElem; // выделяем память на новый элемент
        tmp->Inf = value;	// записываем значение
        tmp->Next = head;	// указатель с первого элемента на второй
        head = tmp;			// меняем голову на новый элемент

        if (!head) // если список отсутствует ()
        {
            head->Next = head;	// указатель на последний элемент
            tail = head;
        }
        else
        { 
            // у нас всегда будет хвост в этой части кода, поэтому проверять есть ли хвост не надо
            tail->Next = head;	// меняем указатель на начало списка
        }
        //-------------------------------------------------------------------------------------------
    }


    /* 
    //этот метод удаляем 
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
    }*/


    //-------------------------------------------------------------------------------------------
    //изменил тип функции на bool так если найден элемент получаем true или в противном случае - false
    //-------------------------------------------------------------------------------------------
    //Поиск элемента
    bool found(T a) {
        while (elem->Inf != a)
        {
            if (elem == tail && elem->Inf != a) {
                return false;
            }
            elem = elem->Next;
        }
        return true;
    }


    //-------------------------------------------------------------------------------------------
    // возможно не самое элегантное решение, но требование было использовать delete один раз, нежели дважды
    // вот, изменил, теперь delete только один раз в этой функции, независимо от варианта удаления 
    // ну и убрал все cout-ы
    //-------------------------------------------------------------------------------------------
    //удаление элемента с указанной инф. частью
    void del_Inf(T a) {
        elem = head;

        TElem *tmp;

        if (a == head->Inf) {
            tmp = head; // Убираем его
            tail->Next = head->Next;
            head = head->Next;
            elem = head;
        }
        else {
            while (elem->Next->Inf != a)
            {
                if (elem == tail && elem->Inf != a) {
                    return;
                }
                elem = elem->Next;
            }
            tmp = elem->Next; // Убираем его
            elem->Next = elem->Next->Next;
        }

        delete tmp;
    }


    //delete all
    void del_all() {
        if (!head) // если список отсутствует ()
        {
            return;
        }
        else {
            tail->Next = NULL;
            while (head != NULL)  //Пока по адресу не пусто
            {
                TElem *temp = head; //Временная переменная для хранения адреса следующего элемента
                head = head->Next;
                delete temp; //Освобождаем адрес обозначающий начало

            }
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
                elem = elem->Next; // доходим до конца списка
            }
            TElem *tmp = new TElem; // выделяем память на новый элемент
            tmp->Inf = value;	// записываем значение 
            tmp->Next = elem->Next;
            elem->Next = tmp;
        }
    }

    //изменение информационной части элемента
    void change_Inf() {
        cout << "\nЭлемент, который необходимо изменить:\n";
        int a, b;
        cin >> a;
        cout << "\nНовое значение элемента:\n";
        cin >> b;
        for (int i = 1; i < a; i++) {
            elem = elem->Next;
        }
        elem->Inf = b;
    }

    //упорядочение текущего элемента
    void sort_now_elem() {
        if (!elem || !head->Next)
            return;
        TElem *p, *t1, *t2;
        if (elem == tail) //если текущий - хвост
        {
            t2 = head;
            while (t2->Next != tail) t2 = t2->Next; //ищем новый хвост
            if (t2->Inf < elem->Inf) return; //если предыдущий элемент меньше хвоста, оставляем как есть
            t2->Next = head; //перенаправляем новый хвост на голову
            tail = t2; //определяем новый хвост
        }
        else {
            if (elem == head) //если текущий - голова
            {
                if (elem->Next->Inf >= elem->Inf) return; //если следующий элемент больше головы, оставляем как есть
                else {
                    head = head->Next; //новая голова
                    tail->Next = head; //новый хвост
                }
            }
            else //если текущий - не голова и не хвост
            {
                t2 = head; //с начала списка, ищем предыдущий элемент от текущего
                while (t2->Next != elem) t2 = t2->Next;
                if (elem->Next != head) //если следующий за текущим - не голова
                    t2->Next = t2->Next->Next; //исключаем текущий и списка
                else
                    t2->Next = head;
            }
        }
        p = head; //начиная с головы, ищем новое место для элемента
        if (p->Inf > elem->Inf) //вставить ли элемент перед головой
        {
            elem->Next = p;
            head = elem;
            tail->Next = head;
            return;
        }
        while (p->Next != head && p->Next->Inf < elem->Inf) //пока следующий не станет больше текущего
            p = p->Next;
        if (p->Next != head) //и, если следующий не голова, помещаем элемент перед следующим
        {
            t1 = p->Next;
            p->Next = elem;
            elem->Next = t1;
        }
        else
        {
            p->Next = elem;
            elem->Next = head;
            tail = elem; //новый хвост
        }
        /*cout << " Текущий элемент - " << elem->Inf << "\n";
        while (elem->Next != tmp) {
        elem = elem->Next;
        }
        if (elem->Inf < elem->Next->Inf) {
        cout << " Элемент упорядочен.\n";
        return;
        }
        else {
        TElem *tmp = new TElem;
        tmp = elem;
        if (tmp == head) {
        head = head->Next;
        tail->Next = head;
        }
        else {
        while (elem->Next != tmp) {
        elem = elem->Next;
        }
        elem->Next = tmp->Next;
        }

        while (tmp->Inf > elem->Next->Inf && elem->Next != tmp)
        {
        elem = elem->Next;
        }
        tmp->Next = elem->Next;
        elem->Next = tmp;
        }*/
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
    void toBeg() {
        elem = head;
    }

    // Получение указателя на информационную часть текущего элемента
    T& GetCurrInfPtr()
    {
        if (elem)
        {
            return elem->Inf;
        }
        return head->Inf;
    }

    T getCurrInf() // get current elem copy Inf - получение копии информационной части 
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
    //-------------------------------------------------------------------------------------------
    // изменил согласно требованиям, теперь деструктор вызывает функцию удаления всех элементов
    //-------------------------------------------------------------------------------------------
    /*Деструктор*/
    ~List()
    {
        del_all();
    }

    //пузырек
    void sort_bubble() {
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
};

template <class T>
class Iterator {
private:
    const List &list;

    typename List<T>::TElem *iterhead, *itertail, *iterelem, *iter;
public:

    Iterator(const List<T> &list)
    {
        iterhead = list.head;
        itertail = list.tail;
    }

    //Итератор на основе существующего
    Iterator(const Iterator<T> &iterator)
    {
        iter = iterator;
    }

    void toBeg() {
        iterelem = iterhead;
    }

    //Получение указателя на информационную часть текущего элемента
    T& GetCurrInfPtr()
    {
        if (iterelem)
        {
            return iterelem->Inf;
        }
        return iterhead->Inf;
    }

    //get current elem copy Inf - получение копии информационной части 
    T getCurrInf1()
    {
        if (iterelem)
        {
            return iterelem->Inf;
        }
        return iterhead->Inf;
    }

    //переводит указатель на текущий элемент в начало
    void setCurrToHead()
    {
        iterelem = iterhead;
    }

    //переводит указатель на текущий элемент в конец
    void setCurrToTail()
    {
        iterelem = itertail;
    }

    //проверка существования элементов в списке
    bool isEmpty() const
    {
        return iterhead == 0;
    }

    //перегруженный оператор !, определяющий существование элементов в структуре данных
    bool operator! () {
        return (iterhead != NULL); // если список отсутствует ()
    }

    //получить указатель на голову
    typename List<T>::TElem* getHead()
    {
        return iterhead;
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
            iterelem = iterelem->Next;
        }
        else
        {
            iterelem = iterhead;
        }
        return *this;
    }

    ~Iterator()
    {
        if (iterhead)
        {
            itertail->Next = NULL;
            do   //Пока по адресу не пусто
            {
                TElem *temp = iterhead; //Временная переменная для хранения адреса следующего элемента
                iterhead = iterhead->Next;
                delete temp; //Освобождаем адрес обозначающий начало
            } while (iterhead != NULL);
        }
    }

};

using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    int tmp;
    unsigned int start_time, end_time, search_time;
    List<int> student_test, student_testcopy;
    TBList<int> student_test1;

    //проверка сортировки
    for (int i = 1; i <= 10; i = i + 1)
    {
        tmp = rand() % 1000000;
        student_test.addToBegin(tmp);
        student_test1.AddBeforeHead(tmp);
        //student_test.addToEnd(i);
    }
    //cout << " My list " << endl;
    cout << " Список из 1000000 элементов. Сортировка." << endl;
    //student_test.show();

    start_time = clock(); // начальное время
    student_test.sort();
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    cout << " Время работы сортировки слиянием: " << ((float)search_time) / CLOCKS_PER_SEC << " с.";

    start_time = clock(); // начальное время
    student_test1.SortListBiDir();
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    cout << "\n Время работы сортировки в примере: " << ((float)search_time) / CLOCKS_PER_SEC << " с.\n";

    ///************************************************************************/
    ///**/
    ///************************************************************************/

    //проверка остальных методов класса
    student_test.del_all();
    for (int i = 1; i <= 10; i = i + 2)
    {
        tmp = rand() % 25;
        student_test.addToBegin(tmp);
        student_testcopy.addToBegin(tmp);
    }
    cout << "\n Список:" << endl;
    student_test.show();
    student_testcopy.show();

    //add to end
    tmp = rand() % 100;
    cout << endl << "\n Добавление элемента в конец: " << tmp << endl;
    student_test.addToEnd(tmp);
    student_test.show();
    cout << endl;

    //add to beg
    tmp = rand() % 100;
    cout << endl << "\n Добавление элемента в начало: " << tmp << endl;
    student_test.addToBegin(tmp);
    student_test.show();


    //поиск элемента с указанной инф. частью
    cout << "\n\n Введите значение элемента для поиска\n";
    int val;
    cin >> val;
    student_test.found(val);

    /*//add after num
    int num, value;
    cout << "\n\n Введите номер элемента, после которого нужна вставка: ";
    cin >> num;
    cout << " Введите значение элемента: ";
    cin >> val;
    student_test.addAfterNum(val, num);
    student_test.show();*/

    //del elementa s Inf
    cout << "\n\n Введите значение элемента, который необходимо удалить:\n";
    cin >> val;
    student_test.del_Inf(val);
    student_test.show();


    //упорядочение текущего элемента
    cout << "\n\n Введите значение элемента, который необходимо вставить\n";
    cin >> val;
    student_test.sort_elem(val);
    student_test.show();

    //упорядочивание текущего элемента
    cout << "\n\n Добавление элемента в начало:\n";
    student_test.addToBegin(28);
    student_test.show();
    cout << "\n\n Упорядочивание текущего элемента:\n";
    student_test.sort_now_elem();
    student_test.show();

    /*******************************************************/
    //перегруженный оператор !, определяющий существование элементов в структуре данных
    cout << "\n Определение существования элементов в структуре данных:\n";
    if (!student_test) cout << "\n Список не пуст\n";
    else cout << "\n Список пуст\n";

    /*******************************************************/
    //копирование списка
    cout << "\n Новый список - копия старого\n";
    student_testcopy = student_test;
    student_testcopy.show();

    /************************************************************************/
    /*Текущий элемент*/
    /************************************************************************/

    // Получение указателя на информационную часть текущего 
    int *a = &student_test.GetCurrInfPtr();
    cout << "\n Текущий элемент " << *a << endl;

    /*//проверка того, что выше мы получили действительно указатель на информационную часть элемента списка
    *a = 20;
    student_test.show();*/
    /**/
    //получение копии информационной части 
    int b = student_test.getCurrInf();
    cout << "\n Копия информационной части текущего элемента\n " << b << endl;

    //следующий элемент
    ++student_test;
    b = student_test.getCurrInf();
    cout << "\n Переходим к следующему элементу\n " << b << endl;

    //переход к голове списка
    student_test.setCurrToHead();
    b = student_test.getCurrInf();
    cout << "\n Голова списка - текущий элемент\n " << b << endl;

    //проверка сортировки
    cout << "\n Сортировка слиянием, сортировка пузырьком:\n" << b << endl;
    student_testcopy = student_test;
    student_test.sort();
    student_testcopy.sort_bubble();
    student_test.show();
    student_testcopy.show();

    cout << endl << endl;

    return 0;
}

