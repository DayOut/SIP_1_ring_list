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
        mergeSort(&head); // сортируем
        findTail(); // ищем конец, чтобы закольцевать
        show();
        //cout << "\n Количество рекурсивных вызовов: " << k << "\n";
        k = 0;
    }

    void findTail()
    {
        if (!head)
        {
            return;
        }
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
        TElem *head = *root;
        if ((head == NULL) || (head->Next == NULL))
        {
            return;
        }

        findMid(head, &list1, &list2);

        mergeSort(&list1);
        mergeSort(&list2);

        *root = mergeList(list1, list2);

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

        if (!head->Next) // если список отсутствует ()
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
        if (!elem)
        {
            if (!head)
                return false;

            elem = head;
        }

        while (elem->Inf != a)
        {
            if (elem == tail && elem->Inf != a)
                return false;

            elem = elem->Next;
        }
        return true;
    }


    //-------------------------------------------------------------------------------------------
    // возможно не самое элегантное решение, но требование было использовать delete один раз
    // вот, изменил, теперь delete только один раз в этой функции, независимо от варианта удаления 
    // ну и убрал все cout-ы
    // И дописал обработку случая удаления хвоста 
    //-------------------------------------------------------------------------------------------
    //удаление элемента с указанной инф. частью
    void del_Inf(T a) {

        if (!head)
        {
            return;
        }

        elem = head;

        TElem *tmp;

        if (a == head->Inf) {
            tmp = head; // Убираем его
            tail->Next = head->Next;
            head = head->Next;
            elem = head;
        }
        //-------------------------------------------------------------------------------------------
        else if(a == tail->Inf)
        {
            //придется обходить весь список, чтобы найти элемент перед хвостом =(
            tmp = head;
            TElem *tmpTail = tail; // пришлось, я не хотел ее вводить. Из-за того, что delete дожен быть один в функции, 
                                // а удалять будет только элемент tail...

            while (tmp->Next != tail)
            {
                tmp = tmp->Next;
            }
            tmp->Next = head; // вырезали из списка конечный элемент для удаления
            tail = tmp; // указали снова наш конечный элемент
            tmp = tmpTail; // передали удаляемый элемент в переменную tmp
        }
        //-------------------------------------------------------------------------------------------
        else 
        {
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
            head = elem = tail = NULL; //Обнуляем
        }
    }

    //упорядочение нового элемента
    void sort_elem(T value) {
        elem = head;
        TElem *tmp = new TElem; // выделяем память на новый элемент
        tmp->Inf = value;	// записываем значение

        //-------------------------------------------------------------------------------------------
        // Повыносил дублирующиеся строки
        //-------------------------------------------------------------------------------------------

        if (head->Inf >= value) {
            
            tmp->Next = head;	// указатель с первого элемента на второй
            head = tmp;			// меняем голову на новый элемент
            tail->Next = head;	// меняем указатель на начало списка
        }
        else {
            while (elem != tail && value > elem->Next->Inf)
            {
                elem = elem->Next; // доходим до конца списка
            }
            tmp->Next = elem->Next;
            elem->Next = tmp;
        }
    }


    //-------------------------------------------------------------------------------------------
    //Эта функция не нужна (ее нет в ТЗ)
    //-------------------------------------------------------------------------------------------
    //изменение информационной части элемента
    /*
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
    }*/


    //упорядочение текущего элемента
    void sort_now_elem() 
    {
        // elem - текущий элемент (сортируемый)
        // tmp - курсор

        // проверка на пустой список
        if (!head || !tail) 
            return; 

        // проверка на наличие "текущего" элемента
        if (!elem) 
            elem = head;

        TElem *tmp = head;

        if (elem == head)
        {
            if (elem->Inf <= head->Next->Inf)
                return; // значит сортировать смысла нет
            //вырезали 
            head = head->Next;
            tail->Next = head;
        }
        else
        {
            //находим эл-т перед текущим
            while (tmp->Next != elem)
            {
                tmp = tmp->Next;
            }

            if (elem == tail)
            {
                if (tmp->Inf < elem->Inf)
                    return;// снова нет смысла сортировать

                           //вырезаем
                tail = tmp;
                tail = elem->Next;
            }
            else
            {
                if (tmp->Inf < elem->Inf && elem->Inf < elem->Next->Inf)
                    return;// снова нет смысла сортировать

                           // вырезаем
                tmp->Next = elem->Next;
                tmp = elem;
                elem = head;
            }
        }

        

        // если элемент больше следующего - необходимо искать место текущему элементу во второй части списка
        // иначе до этого места
        tmp = (elem->Inf > elem->Next->Inf) ? elem->Next : head;

        while (elem->Inf > tmp->Inf)
        {
            // нашли нужное место
            if (elem->Inf <= tmp->Next->Inf) 
            {
                //вставили
                elem->Next = tmp->Next;
                tmp->Next = elem;
                break;
            }
            else if (tmp == tail) //если дошли до конца списка
            {
                elem->Next = head;
                tail->Next = elem;
                tail = elem;
                break;
            }
            tmp = tmp->Next;
        }
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

    

    //перегруженный оператор присваивания
    List<T>& operator=(List<T>& right)
    {
        //-------------------------------------------------------------------------------------------
        // Логика: 
        //      Присвоение идет поверх существующего списка, если в этом списке уже есть элементы - будем перезаписывать 
        //      текущее информационное поле, если в нашем списке элементов больше - удаляем лишние уже после перезаписанной 
        //      первой части списка (удаляем только лишее, то чего в этом списке быть не должно). Если же в этом списке элементов меньше
        //      добавляем новые, как делал старый алгоритм
        //
        //      Итого, у нас три варианта развития событий (сравнение двух списков)
        //          1) есть_элемент     есть_элемент - в данном случае перезаписываем инф часть
        //          2) есть_элемент     нет_элемента - удаляем "лишний" элемент в данном списке
        //          3) нет_элемента     есть_элемент - добавляем в конец этого списка 
        //      

        if (this == &right) //проверка на самоприсваивание 
        {
            return *this;
        }

        TElem *rightHead = right.getHead();
        TElem *rightCurrent = rightHead;

        TElem *tmp = head, *prevTmp = NULL; // курсоры в левом списке

        while (tmp || rightCurrent)
        {
            if (rightCurrent && tmp)
            {
                tmp->Inf = rightCurrent->Inf;
            }
            else if (tmp && !rightCurrent)
            {
                elem = tmp;
                tmp = prevTmp;
                deleteCurrentElement(prevTmp);
            }
            else if (!tmp && rightCurrent)
            {
                addToEnd(rightCurrent->Inf);
            }

            if(prevTmp != tmp)
                prevTmp = (tmp) ? tmp : NULL;

            if (tmp)
                tmp = (tmp->Next == head) ? NULL : tmp->Next;
            
            if (rightCurrent)
                rightCurrent = (rightCurrent->Next == rightHead) ? NULL : rightCurrent->Next;
        }
        return *this;

        //-------------------------------------------------------------------------------------------

        /*
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
        return *this;*/
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
        head = elem = tail = NULL; // обнуляем
    }

    //пузырек
    bool sort_bubble() {
        TElem *tmp = head;

        bool flag = false;
        do
        {
            flag = false;
            tmp = head;
            while (tmp->Next != head)
            {
                if (tmp->Inf > tmp->Next->Inf)
                    return false;

                tmp = tmp->Next;
            }
        } while (flag);

        return true;
    }

private:

    //получить указатель на голову
    TElem* getHead()
    {
        return head;
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

    //private функция для удаления текущего элемента
    void deleteCurrentElement(TElem *prevTmp)
    {
        TElem *tmp;
        if (!head)
            return;
        else if (elem == head)
        {
            tmp = head;

            if (head->Next == head)
            {
                head = NULL;
            }
            else
            {
                elem = head->Next;
                head = elem;
                tail->Next = head;
            }
        }
        else
        {
            tmp = elem;
            elem = elem->Next;
            prevTmp->Next = elem;

        }

        delete tmp;

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
    //TBList<int> student_test1;

    //проверка сортировки
    for (int i = 1; i <= 7; i = i + 1)
    {
        tmp = rand() % 100;
        student_test.addToBegin(tmp);
        //student_test1.AddBeforeHead(tmp);
        //student_test.addToEnd(i);
    }
    student_test.addToBegin(27);
    cout << " My list " << endl;
    cout << " Список из 1000000 элементов. Сортировка.\n" << endl;
    //student_test.show();

    start_time = clock(); // начальное время
    student_test.sort();
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    cout << " Время работы сортировки слиянием: " << ((float)search_time) / CLOCKS_PER_SEC << " с.\n";
    student_test.show();
    student_test.addToBegin(51);
    student_test.show();
    student_test.setCurrToHead();
    student_test.sort_now_elem();
    student_test.show();

    List<int> asd;
    asd = student_test;
    asd.show();
    cout << endl;

    student_test.addToBegin(24);
    asd = student_test;
    cout << "student_test: \n";
    student_test.show();
    cout << "asd: \n";
    asd.show();
    cout << endl;

    student_test.setCurrToHead();
    ++student_test;
    student_test.del_Inf(27);
    asd = student_test;
    cout << "student_test: \n";
    student_test.show();
    cout << "asd: \n";
    asd.show();
    cout << endl;


    system("pause");


    /*
    start_time = clock(); // начальное время
    //student_test1.SortListBiDir();
    end_time = clock(); // конечное время
    search_time = end_time - start_time; // искомое время
    cout << "\n Время работы сортировки в примере: " << ((float)search_time) / CLOCKS_PER_SEC << " с.\n";
    */
    //***********************************************************************
    //
    //************************************************************************

    /*
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
    student_test.found(val);*/

    /*//add after num
    int num, value;
    cout << "\n\n Введите номер элемента, после которого нужна вставка: ";
    cin >> num;
    cout << " Введите значение элемента: ";
    cin >> val;
    student_test.addAfterNum(val, num);
    student_test.show();*/

    /*
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
    student_test.show();*/

    //*******************************************************
    //перегруженный оператор !, определяющий существование элементов в структуре данных
    cout << "\n Определение существования элементов в структуре данных:\n";
    if (!student_test) cout << "\n Список не пуст\n";
    else cout << "\n Список пуст\n";

    //*******************************************************
    //копирование списка
    cout << "\n Новый список - копия старого\n";
    student_testcopy = student_test;
    student_testcopy.show();

    //************************************************************************
    //Текущий элемент
    //************************************************************************

    /*//проверка того, что выше мы получили действительно указатель на информационную часть элемента списка
    *a = 20;
    student_test.show();*/
    
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

