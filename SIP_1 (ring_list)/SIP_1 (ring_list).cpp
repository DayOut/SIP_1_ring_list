// sip_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "blist.h"
#include <iostream>
#include <cstdlib>
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
    TElem *tail, *elem; //указатель на хвост списка, elem - указатель на текущий элемент
    int k = 0;

public:

    List() {
        elem = tail = NULL;
    }

    //сортировка слиянием
    void sort()
    {
        if (tail) {
            TElem *head = tail->Next;
            tail->Next = NULL; // делаем из кольцевого - односвязный список
            mergeSort(head); // сортируем
                             // ищем конец, чтобы закольцевать
            TElem *tmp = head;
            do
            {
                tmp = tmp->Next;
            } while (tmp->Next);
            tail = tmp;
            tail->Next = head; // закольцевали список
            cout << "\n Количество рекурсивных вызовов: " << k << "\n";
            k = 0;
        }
    }

    //функция добавления элемента в конец списка
    void addToEnd(T value)
    {
        TElem *tmp = new TElem; // выделяем память на новый элемент
        tmp->Inf = value;	// записываем значение
        if (tail)
        {
            tmp->Next = tail->Next;
            tail = tail->Next = tmp;
        }
        else
        {
            tail = tmp;
            tmp->Next = tail;
        }
    }

    //Добавление в начало списка
    void addToBegin(T value)
    {
        TElem *tmp = new TElem; // выделяем память на новый элемент
        tmp->Inf = value;	// записываем значение
        if (tail)
            tmp->Next = tail->Next;
        else
            tail = tmp;
        tail->Next = tmp; //указатель с первого элемента на второй
    }

    //Поиск элемента
    bool found(T a) {
        if (tail)
        {
            TElem *element = tail;
            do
            {
                if (element->Inf == a) {
                    elem = element;
                    return true;
                }
                element = element->Next;
            } while (element != tail);
        }
        elem = NULL;
        return false;
    }

    //Удаление элемента с указанной инф. частью
    void del_Inf(T a) {
        if (tail)
        {
            TElem *prev = tail;
            TElem *cur = NULL;
            do {
                if (prev->Next->Inf == a) {
                    cur = prev->Next;
                    break;
                }
                prev = prev->Next;
            } while (prev != tail);

            if (cur != NULL) { //если элемент вообще найден
                if (prev != prev->Next) { //если элемент не один в списке
                    prev->Next = cur->Next; //вырезаем элемент
                    if (cur == tail) //если элемент был хвостом
                        tail = prev;
                }
                else  //если элемент один в списке
                    tail = NULL;
                delete cur; //удаляем элемент
            }
        }
    }

    //delete all
    void del_all() {
        if (tail) {
            TElem *current, *next;
            current = tail;
            next = current->Next;

            do {
                current = next;
                next = current->Next;
                delete current;
            } while (current != tail);

            delete tail;
            tail = NULL;
        }
    }

    //упорядочение нового элемента
    void sort_elem(T value) {
        if (tail) {
            TElem *newElement = new TElem;
            newElement->Inf = value; //создали новый элемент
            TElem *prev = tail; //поместили указатель в хвост
            TElem *cur = tail->Next;

            while (cur->Inf < value && prev != tail) { //ищем предыдущий
                prev = prev->Next;
                cur = cur->Next;
            }

            if (prev == tail && tail->Next->Inf < value) //если нужно изменить хвост
                tail = newElement;

            newElement->Next = prev->Next; //вставляем элемент
            prev->Next = newElement;
        }
        /*
        TElem *newElement = new TElem;
        newElement->Inf = value;
        TElem *current = tail;

        if (current->Inf < value){
        newElement->Next = current->Next;
        current->Next = newElement;
        tail = newElement;
        }
        else {
        do {
        current = current->Next;
        } while (current->Next->Inf < value); //?????

        newElement->Next = current->Next;
        current->Next = newElement;
        }
        */
    }
    //void sort_elem(T value) {
    //	if (tail) {
    //		TElem *newElement = new TElem;
    //		newElement->Inf = value; //создали новый элемент
    //		TElem *current = tail; //поместили указатель в хвост
    //		if (current->Next->Inf < value) { //если нужно вставить после головы
    //			do { //ищем предыдущий
    //				current = current->Next;
    //			} while (current->Next->Inf < value && current != tail);

    //			if (current == tail) //если нужно изменить хвост
    //				tail = newElement;
    //		}
    //		newElement->Next = current->Next; //вставляем элемент
    //		current->Next = newElement;
    //	}
    //}

    //упорядочение текущего элемента (выделяем его из списка и вставляем в нужное место)
    void sort_now_elem() {
        if (tail && elem->Inf > elem->Next->Inf) { //если элемент вообще возможно и нужно упорядочить
            TElem *prev = tail;
            do {
                prev = prev->Next;
            } while (prev->Next != elem); //находим предыдущий элемент
            prev->Next = elem->Next; //вырезаем элемент
            if (elem == tail) //если элемент был хвостом
                tail = prev;
            //теперь вставим элемент в нужное место
            TElem *current = tail; //поместили указатель в хвост
            if (current->Next->Inf < elem->Inf) { //если нужно вставить после головы
                do { //ищем предыдущий перед тем, куда вставлять
                    current = current->Next;
                } while (current->Next->Inf < elem->Inf && current != tail);

                if (current == tail) //если нужно изменить хвост
                    tail = elem;
            }
            elem->Next = current->Next; //вставляем элемент
            current->Next = elem;
        }
    }

    //Вывод списка
    void show()
    {
        if (tail) // если список отсутствует ()
        {
            elem = tail->Next;
            do
            {
                cout << elem->Inf << "   ";
                elem = elem->Next; //доходим до конца списка
            } while (elem != tail->Next); //в случае кольцевого списка проверяем есть ли данный элемент последним
        }
    }
    /*******************************************************************/

    T getCurrInf() // get current elem copy Inf - получение копии информационной части 
    {
        return elem->Inf;
    }

    //переводит указатель на текущий элемент в начало
    void setCurrToHead()
    {
        if (tail)
            elem = tail->Next;
    }

    //переводит указатель на текущий элемент в конец
    void setCurrToTail() {
        elem = tail;
    }

    //перегруженный оператор !, определяющий существование элементов в структуре данных
    bool operator! () {
        return tail != NULL;
    }

    //перегруженный оператор присваивания
    List<T>& operator=(const List<T>& right)
    {
        if (this != &right) //проверка на самоприсваивание 
        {
            TElem *leftHead = tail->Next;
            TElem *rightHead = right.tail->Next;
            if (right.tail != NULL) //если right не пуст
            {
                do //пока есть right and left
                {
                    leftHead->Inf = rightHead->Inf;
                    leftHead = leftHead->Next;
                    rightHead = rightHead->Next;
                } while (rightHead != right.tail->Next && leftHead != tail->Next);
                //правый закончился, удаляем оставшиеся элементы левого
                if (rightHead == right.tail->Next) {
                    TElem *del;
                    do
                    {
                        del = leftHead;
                        leftHead = leftHead->Next;
                        delete del;
                    } while (leftHead != tail->Next);
                }
                //левый закончился, добавляем элементы из правого в конец
                if (leftHead == tail->Next) {
                    do //пока есть right
                    {
                        addToEnd(rightHead->Inf);
                        rightHead = rightHead->Next;
                    } while (rightHead != right.tail->Next);
                }
            }
            else del_all(); //удаляем все элементы из left

        }
        return *this;
    }

    //конструктор копирования
    List<T>(const List<T>& right)
    {
        elem = tail = NULL;
        *this = right; // присваиваем с помощью перегруженного оператора присваивания
    }

    //перегруженный оператор - переход к следующему элементу
    List<T>& operator++()
    {
        elem = elem ? elem->Next : tail;
        return *this;
    }

    /*******************************************************************/
    /*Деструктор*/
    ~List()
    {
        del_all();
        elem = NULL;
    }

    //пузырек
    bool isSorted() {
        TElem *tmp = tail;
        if (tail)
        {
            do
            {
                tmp = tmp->Next;
                if (tmp->Inf > tmp->Next->Inf)
                    return false;
            } while (tmp->Next != tail);
            return true;
        }
        return false;
    }

    // Получение указателя на информационную часть текущего элемента
    T& GetCurrInfPtr()
    {
        return elem ? elem->Inf : tail->Next->Inf;
    }

private:
    void mergeSort(TElem *&root)
    {
        k++; //количество рекурсивных вызовов
        TElem *list1, *list2;
        TElem *head = root;
        if ((head == NULL) || (head->Next == NULL))
        {
            return;
        }

        findMid(head, list1, list2);

        mergeSort(list1); //сортируем каждую часть
        mergeSort(list2);

        root = mergeList(list1, list2);

    }

    TElem* mergeList(TElem *list1, TElem *list2)
    {
        TElem temphead = { 0, NULL }, *tail = &temphead;
        k++;
        while ((list1 != NULL) && (list2 != NULL)) //пока в подсписке еще есть элементы
        {
            TElem **min = (list1->Inf < list2->Inf) ? &list1 : &list2; //выбираем меньший
            TElem *Next = (*min)->Next;
            tail = tail->Next = *min;
            *min = Next;
        }
        tail->Next = list1 ? list1 : list2; //если один из подсписков закончился
        return temphead.Next;
    }

    void findMid(TElem *root, TElem *&list1, TElem *&list2)
    {
        /**
        Возвращает указатель на элемент структуры TElem<T> рядом с серединой списка
        и после обрезаем оригинальный список перед этим элементом
        */
        TElem *slow, *fast;

        //в случае пустого списка (или один элемент)
        if ((root == NULL) || (root->Next == NULL))
        {
            list1 = root;
            list2 = NULL;
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
            list1 = root;
            list2 = slow->Next;
            slow->Next = NULL;
        }
    }


    //получить указатель на голову
    TElem* getHead()
    {
        if (tail)
            return tail->Next;
    }

};

template <class T>
class Iterator {
private:
    typename List<T>::TElem *cur; //указатель на список

public:
    Iterator()
    {
        cur = NULL;
    }

    Iterator(List<T>& list)
    {
        cur = list.tail;
    }

    //Итератор на основе существующего
    Iterator(Iterator<T>& iterator)
    {
        cur = iterator.cur;
    }

    Iterator<T>& operator++()
    {
        if (cur != 0)
        {
            cur = cur->Next;
        }
        return *this;
    }

    Iterator<T>& operator=(Iterator<T>& right)
    {
        cur = right.cur;
        return *this;
    }

    Iterator<T>& operator=(List<T>& list)
    {
        cur = list.tail;
        return *this;
    }

    bool operator!()
    {
        return cur;
    }

    bool getCurrInf(T& tmp)
    {
        if (cur)
        {
            tmp = cur->Inf;
            return true;
        }
        else
            return false;


    }

    T& getCurrInfRef() // Ссылка на информационную часть элемента
    {

        return cur->Inf;
    }

};

using namespace std;
int menu()
{
    // Выбранный вариант менюж
    int variant;
    cout << "Выберите вариант\n" << endl;
    cout << "1.  Сортировка\n";
    cout << "2.  Добавление в начало и в конец\n";
    cout << "3.  Поиск элемента с указанной инф. частью\n";
    cout << "4.  Удаление элемента с указанной инф. частью\n";
    cout << "5.  Упорядочение нового элемента\n";
    cout << "6.  Упорядочение текущего элемента\n";
    cout << "7.  Перегруженный !, определяющий существование эл-в в структуре\n";
    cout << "8.  Копирование списка\n";
    cout << "9.  Копия инф. части, переход к след., переход голове\n";
    cout << "10. Конструктор копирования\n";
    cout << "11. Выход\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    int tmp, b;
    unsigned int start_time, end_time, search_time;
    List<int> student_test, student_testcopy, student_sort;
    TBList<int> student_test1;
    //заполним список
    for (int i = 1; i <= 10; i = i + 2)
    {
        tmp = rand() % 25;
        student_test.addToBegin(tmp);
        //student_testcopy.addToBegin(tmp);
    }
    cout << "\n Список:" << endl;
    student_test.show();

    //List<int> st(student_test); //исп. конструктор копирования

    while (true) {

        int variant = menu();

        switch (variant) {
        case 1:
            //проверка сортировки
            for (int i = 1; i <= 1000000; i = i + 1)
            {
                tmp = rand() % 1000000;
                student_sort.addToBegin(tmp);
                student_test1.AddBeforeHead(tmp);
            }
            cout << " Список из 1000000 элементов. Сортировка.\n" << endl;
            start_time = clock(); // начальное время
            student_sort.sort();
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            cout << " Время работы сортировки слиянием: " << ((float)search_time) / CLOCKS_PER_SEC << " с.";

            start_time = clock(); // начальное время
            student_test1.SortListBiDir();
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            cout << "\n Время работы сортировки в примере: " << ((float)search_time) / CLOCKS_PER_SEC << " с.\n";

            //проверка сортировки
            if (student_sort.isSorted())
                cout << " Перестановок в сорт. пузырьком нет - список отсортирован верно.\n\n";
            break;

        case 2:
            //add to beg
            tmp = rand() % 100;
            cout << endl << "\n Добавление элемента в начало: " << tmp << endl;
            student_test.addToBegin(tmp);
            student_test.show();

            //add to end
            tmp = rand() % 100;
            cout << endl << "\n Добавление элемента в конец: " << tmp << endl;
            student_test.addToEnd(tmp);
            student_test.show();
            cout << endl;
            break;

        case 3:
            //поиск элемента с указанной инф. частью
            cout << "\n\n Введите значение элемента для поиска\n";
            int val;
            cin >> val;
            if (student_test.found(val))
                cout << " Элемент сущестует.\n";
            else
                cout << " Элемент не сущестует.\n";
            break;

        case 4: //удаление элемента с указанной инф. частью
            cout << "\n\n Введите значение элемента, который необходимо удалить:\n";
            cin >> val;
            student_test.del_Inf(val);
            student_test.show();
            break;

        case 5: //упорядочение нового элемента
            cout << "\n\n Введите значение элемента, который необходимо вставить\n";
            cin >> val;
            student_test.sort_elem(val);
            student_test.show();
            break;

        case 6: //упорядочение текущего элемента
            cout << "\n\n Упорядочение текущего элемента:\n";
            student_test.sort_now_elem();
            student_test.show();
            break;

        case 7:
            //перегруженный оператор !, определяющий существование элементов в структуре данных
            cout << "\n Определение существования элементов в структуре данных:\n";
            if (!student_test) cout << "\n Список не пуст\n";
            else cout << "\n Список пуст\n";
            break;

        case 8: //копирование списка
            cout << "\n Новый список - копия старого\n";
            student_testcopy = student_test;
            student_testcopy.show();
            break;

        case 9: //получение копии информационной части 
            b = student_test.getCurrInf();
            cout << "\n Копия информационной части текущего элемента\n " << b << endl;

            //следующий элемент
            ++student_test;
            b = student_test.getCurrInf();
            cout << "\n Переходим к следующему элементу\n " << b << endl;

            //переход к голове списка
            student_test.setCurrToHead();
            b = student_test.getCurrInf();
            cout << "\n Голова списка - текущий элемент\n " << b << endl;
            break;

        case 10:
            cout << " Новый список - копия старого\n";
            //st.show();
            break;

        case 11:
            exit(EXIT_SUCCESS);
            break;

        default:
            cout << " Вы выбрали неверный вариант.\n";
            exit(EXIT_FAILURE);
            break;
        }
    }
    cout << endl << endl;

    return 0;
}

