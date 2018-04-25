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
    TElem *head, *tail, *elem; //указатель на голову списка, elem - указатель на текущий элемент
    int k = 0;

public:

    List() {
        head = NULL;
        tail = NULL;
        elem = NULL;
    }

    //сортировка слиянием
    void sort()
    {
        if (head) {
            tail->Next = NULL; // делаем из кольцевого - односвязный список
            mergeSort(&head); // сортируем
            findTail(); // ищем конец, чтобы закольцевать
            cout << "\n Количество рекурсивных вызовов: " << k << "\n";
            k = 0;
        }

    }

    void findTail()
    {
        tail = NULL;
        if (head)
        {
            TElem *tmp = head;
            while (tmp->Next != head && tmp->Next)
            {
                tmp = tmp->Next;
            }
            tail = tmp;
            tail->Next = head;
        }
    }

    void mergeSort(TElem **root)
    {
        k++; //количество рекурсивных вызовов
        TElem *list1, *list2;
        TElem *head = *root;
        if ((head == NULL) || (head->Next == NULL))
        {
            return;
        }

        findMid(head, &list1, &list2);

        mergeSort(&list1); //сортируем каждую часть
        mergeSort(&list2);

        *root = mergeList(list1, list2);

    }

    TElem* mergeList(TElem *list1, TElem *list2)
    {
        TElem temphead = { 0, NULL }, *tail = &temphead;

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

    void findMid(struct TElem *root, struct TElem **list1, struct TElem **list2)
    {
        /**
        Возвращает указатель на элемент структуры TElem<T> рядом с серединой списка
        и после обрезаем оригинальный список перед этим элементом
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

    //функция добавления элемента в конец списка
    bool addToEnd(T value) // add_end / ...
    {
        TElem *tmp = new TElem; // выделяем память на новый элемент
        tmp->Inf = value;	// записываем значение
        tmp->Next = head;	// указатель с первого элемента на второй
        if (!head) // если список отсутствует ()
        {
            head = tmp;
            tail = head;
            elem = head;
        }
        else
        {
            tail->Next = tmp;
            tail = tmp;
        }
        return true;
    }

    //Добавление в начало списка
    void addToBegin(T value) // add_to_begin / add_begin
    {
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
            tail->Next = head;	// меняем указатель на начало списка
        }
    }

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

    //удаление элемента с указанной инф. частью
    void del_Inf(T a) {
        if (head) {
            elem = head;
            TElem * tmp;
            if (a == head->Inf) {
                tmp = head; // Убираем его
                tail->Next = head->Next;
                head = head->Next;
                elem = head; //Элемент a удален
            }
            else if (a == tail->Inf) //если это хвост
            {
                tmp = head;
                TElem *tmpTail = tail;
                while (tmp->Next != tail) //элемент перед хвостом
                {
                    tmp = tmp->Next;
                }
                tmp->Next = head; //уберем конечный элемент
                tail = tmp;
                tmp = tmpTail; //то, что будем удалять delete
            }
            else {
                while (elem->Next->Inf != a)
                {
                    if (elem == tail && elem->Inf != a)
                        return;

                    elem = elem->Next;
                }
                tmp = elem->Next; // Убираем его
                elem->Next = elem->Next->Next;
            }
            delete tmp;
        }
    }

    //delete all
    void del_all() {
        if (head) // если список отсутствует ()
        {
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
        TElem *tmp = new TElem; // выделяем память на новый элемент
        tmp->Inf = value;	// записываем значение

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

    //упорядочение текущего элемента
    void sort_now_elem() {
        // elem - текущий элемент (сортируемый)
        // tmp - курсор
        if (head && tail) {
            if (!elem)
                elem = head;

            TElem *tmp = head;
            if (elem == head) //если текущий голова
            {
                head = head->Next; //вырезаем элемент
                tail->Next = head;
            }
            else
            {
                //находим элемент перед текущим
                while (tmp->Next != elem)
                {
                    tmp = tmp->Next;
                }

                if (tmp->Next != tail)
                {
                    tmp->Next = elem->Next;
                }
                else
                {
                    tail = tmp;
                    tail->Next = elem->Next;
                }
            }

            tmp = head;

            if (elem->Inf <= head->Inf)
            {
                elem->Next = head;
                tail->Next = elem;
                head = elem;
            }

            while (elem->Inf > tmp->Inf)
            {
                if (elem->Inf <= tmp->Next->Inf) //нашли нужное место
                {
                    elem->Next = tmp->Next; //вставляем
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
    }

    //Вывод списка
    void show()
    {
        if (head) // если список отсутствует ()
        {
            TElem *tmp = head;
            do
            {
                cout << tmp->Inf << "   ";
                tmp = tmp->Next; //доходим до конца списка
            } while (tmp != head); //в случае кольцевого списка проверяем есть ли данный элемент последним
            cout << endl;
        }
    }
    /*******************************************************************/
    //метод, переводящий указатель на текущий элемент в начало(конец, при необходимости) списка.
    void toBeg() {
        elem = head;
    }

    T getCurrInf() // get current elem copy Inf - получение копии информационной части 
    {
        if (elem && head)
            return elem ? elem->Inf : head->Inf;
        return 0;
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
    List<T>& operator=(const List<T>& right)
    {
        if (this == &right) //проверка на самоприсваивание 
        {
            return *this;
        }
        // правый список это тот, из которого нужно присвоить значения
        TElem *rightHead = right.head; //получение головы списка из правого
        TElem *rightCurrent = rightHead; //текущий элемент из этого же списка

        TElem *tmp = head, *prevTmp = NULL; //курсоры в левом списке
        if (rightHead)
        {
            while (rightCurrent && tmp) // пока оба списка есть копируем из правого в левый
            {
                tmp->Inf = rightCurrent->Inf;
                prevTmp = (tmp) ? tmp : NULL;
                tmp = (tmp->Next == head) ? NULL : tmp->Next;
                rightCurrent = (rightCurrent->Next == rightHead) ? NULL : rightCurrent->Next;
            }

            while (tmp && !rightCurrent) //если есть только левый 
            {
                elem = tmp;
                tmp = prevTmp ? prevTmp : tail;
                deleteCurrentElement(prevTmp);
                if (tmp)
                    tmp = (tmp->Next == head) ? NULL : tmp->Next;
                else
                {
                    tmp = NULL;
                }
            }

            while (!tmp && rightCurrent) //если есть только правый
            {
                addToEnd(rightCurrent->Inf);
                rightCurrent = (rightCurrent->Next == rightHead) ? NULL : rightCurrent->Next;
            }
        }
        else
        {
            del_all(); //если правый список полностью пустой - удаляем этот
        }

        findTail();

        return *this;
    }

    //конструктор копирования
    List<T>(const List<T>& right)
    {
        head = NULL;
        elem = NULL;
        
        if (right.head != NULL)
        {
            *this = right; 
        }
    }

    //перегруженный оператор - переход к следующему элементу
    List<T>& operator++()
    {
        if (elem)
            elem = elem->Next;
        else
            elem = head;
        return *this;
    }

    /*******************************************************************/
    /*Деструктор*/
    ~List()
    {
        del_all();
        head = elem = tail = NULL;
    }

    //пузырек
    bool sort_bubble() {
        TElem *tmp = head;
        if (head)
        {
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
        return false;
    }

    T& GetCurrInfPtr()
    {
        return elem ? elem->Inf : head->Inf;
    }

private:

    // Получение указателя на информационную часть текущего элемента
    

    //private функция для удаления текущего элемента
    void deleteCurrentElement(TElem *prevTmp)
    {
        TElem *tmp;
        if (head) {
            if (elem == head)
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

    //get current elem copy Inf - получение копии информационной части 
    T getCurrInf1()
    {
        return iterelem ? iterelem->Inf : iterhead->Inf;
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

private:

    //получить указатель на голову
    typename List<T>::TElem* getHead()
    {
        return iterhead;
    }

    //Получение указателя на информационную часть текущего элемента
    T& GetCurrInfPtr()
    {
        return iterelem ? iterelem->Inf : iterhead->Inf;
    }

    ~Iterator()
    {
        iterhead = itertail = iterelem = iter = NULL;
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
    List<int> student_test, student_testcopy;
    TBList<int> student_test1;
    //заполним список
    for (int i = 1; i <= 10; i = i + 1)
    {
        tmp = rand() % 25;
        student_test.addToBegin(tmp);
        student_testcopy.addToBegin(tmp);
    }
    cout << "\n Список:" << endl;
    student_test.show();

    // delete before commit------------------------------------
    student_test.del_all();
    student_test.addToEnd(0);
    student_test.addToEnd(1);
    student_test.addToEnd(9);
    student_test.addToEnd(11);
    student_test.addToEnd(12);
    student_test.addToEnd(14);
    student_test.addToEnd(18);
    student_test.addToEnd(19);
    student_test.addToEnd(22);
    student_test.addToEnd(23);


    student_test.sort();
    student_test.show();
    student_test.setCurrToHead();
    int *val = NULL;
    for (int i = 0; i < 10; i++)
    {
        val = &student_test.GetCurrInfPtr();
        cout << "Текущий элемент: " << student_test.getCurrInf();

        std::cin >> *val;
        student_test.sort_now_elem();

        student_test.show();
        std::cout << std::endl;
    }



    //---------------------------------------------------------

    //student_testcopy.show();
    List<int> st(student_test); //исп. конструктор копирования

    int variant = menu();

    switch (variant) {
    case 1:
        //проверка сортировки
        student_test.del_all();
        for (int i = 1; i <= 10; i = i + 1)
        {
            tmp = rand() % 100;
            student_test.addToBegin(tmp); // 
            student_test1.AddBeforeHead(tmp); 
        }

        cout << " Список из 1000000 элементов. Сортировка." << endl;

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

        //проверка сортировки
        if (student_test.sort_bubble())
            cout << " Перестановок нет - список отсортирован верно.\n";
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
        st.show();
        break;

    case 11:
        exit(EXIT_SUCCESS);
        break;

    default:
        cout << " Вы выбрали неверный вариант.\n";
        exit(EXIT_FAILURE);
        break;
    }
    cout << endl << endl;

    return 0;
}

