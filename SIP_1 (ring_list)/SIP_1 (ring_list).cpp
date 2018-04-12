// sip_1.cpp: ���������� ����� ����� ��� ����������� ����������.
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
    TElem *head, *tail, *elem; //��������� �� ������ ������, elem - ��������� �� ������� �������
    int k = 0;

public:

    
   
    List() 
    { 
        head = NULL; 
        //-------------------------------------------------------------------------------------------
        tail = NULL; // ���� �������� ��� ����������
        elem = NULL; // � ��� ����� � ����� � ������� �������
        //-------------------------------------------------------------------------------------------
    }

    //-------------------------------------------------------------------------------------------
    //��� ������ �� ����, ��� ���� �������
    
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
        //��� ����� �������� �� ������� ������
        //-------------------------------------------------------------------------------------------
        if (!head) // ���� ������ ��� - �� � ����������� ������
            return;

        tail->Next = NULL; // ������ �� ���������� - ����������� ������
        mergeSort(head); // ���������
        findTail(); // ���� �����, ����� ������������
        cout << "\n ���������� ����������� �������: " << k << "\n";
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
    // ��� ���� mergeSort(struct TElem **root), �� ��� �� �� ��� ������������, ��� ����� ��� ���������
    // ��� ��� ������ ����� ������ ������� �� ������
    //-------------------------------------------------------------------------------------------
    void mergeSort(TElem **root)
    {
        // ������� ���������� �����, ������ ���-�� � ��������� �������������, �� � �� ���� ���� ������ 
        // ��������, ������� �������� � ���� ����

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
        ���������� ��������� �� ������� ��������� TElem<T> ����� � ��������� ������
        � ����� �������� ������������ ������ ����� ���� ���������
        */
        TElem *slow, *fast;

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

    //������� ���������� �������� � ����� ������
    bool addToEnd(T value) // add_end / ...
    {
        //-------------------------------------------------------------------------------------------
        //������� �������
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������
        tmp->Next = head;	// ��������� � ������� �������� �� ������

        if (!head) // ���� ������ ����������� ()
        {
            //�������� ��� � ������ � ��������������
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
        /* //����� �������� ������� ��� ����
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
        }*/
        return true;
    }


    //���������� � ������ ������
    void addToBegin(T value) 
    {
        //-------------------------------------------------------------------------------------------
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������
        tmp->Next = head;	// ��������� � ������� �������� �� ������
        head = tmp;			// ������ ������ �� ����� �������

        if (!head) // ���� ������ ����������� ()
        {
            head->Next = head;	// ��������� �� ��������� �������
            tail = head;
        }
        else
        { 
            // � ��� ������ ����� ����� � ���� ����� ����, ������� ��������� ���� �� ����� �� ����
            tail->Next = head;	// ������ ��������� �� ������ ������
        }
        //-------------------------------------------------------------------------------------------
    }


    /* 
    //���� ����� ������� 
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
    }*/


    //-------------------------------------------------------------------------------------------
    //������� ��� ������� �� bool ��� ���� ������ ������� �������� true ��� � ��������� ������ - false
    //-------------------------------------------------------------------------------------------
    //����� ��������
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
    // �������� �� ����� ���������� �������, �� ���������� ���� ������������ delete ���� ���, ������ ������
    // ���, �������, ������ delete ������ ���� ��� � ���� �������, ���������� �� �������� �������� 
    // �� � ����� ��� cout-�
    //-------------------------------------------------------------------------------------------
    //�������� �������� � ��������� ���. ������
    void del_Inf(T a) {
        elem = head;

        TElem *tmp;

        if (a == head->Inf) {
            tmp = head; // ������� ���
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
            tmp = elem->Next; // ������� ���
            elem->Next = elem->Next->Next;
        }

        delete tmp;
    }


    //delete all
    void del_all() {
        if (!head) // ���� ������ ����������� ()
        {
            return;
        }
        else {
            tail->Next = NULL;
            while (head != NULL)  //���� �� ������ �� �����
            {
                TElem *temp = head; //��������� ���������� ��� �������� ������ ���������� ��������
                head = head->Next;
                delete temp; //����������� ����� ������������ ������

            }
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
                elem = elem->Next; // ������� �� ����� ������
            }
            TElem *tmp = new TElem; // �������� ������ �� ����� �������
            tmp->Inf = value;	// ���������� �������� 
            tmp->Next = elem->Next;
            elem->Next = tmp;
        }
    }

    //��������� �������������� ����� ��������
    void change_Inf() {
        cout << "\n�������, ������� ���������� ��������:\n";
        int a, b;
        cin >> a;
        cout << "\n����� �������� ��������:\n";
        cin >> b;
        for (int i = 1; i < a; i++) {
            elem = elem->Next;
        }
        elem->Inf = b;
    }

    //������������ �������� ��������
    void sort_now_elem() {
        if (!elem || !head->Next)
            return;
        TElem *p, *t1, *t2;
        if (elem == tail) //���� ������� - �����
        {
            t2 = head;
            while (t2->Next != tail) t2 = t2->Next; //���� ����� �����
            if (t2->Inf < elem->Inf) return; //���� ���������� ������� ������ ������, ��������� ��� ����
            t2->Next = head; //�������������� ����� ����� �� ������
            tail = t2; //���������� ����� �����
        }
        else {
            if (elem == head) //���� ������� - ������
            {
                if (elem->Next->Inf >= elem->Inf) return; //���� ��������� ������� ������ ������, ��������� ��� ����
                else {
                    head = head->Next; //����� ������
                    tail->Next = head; //����� �����
                }
            }
            else //���� ������� - �� ������ � �� �����
            {
                t2 = head; //� ������ ������, ���� ���������� ������� �� ��������
                while (t2->Next != elem) t2 = t2->Next;
                if (elem->Next != head) //���� ��������� �� ������� - �� ������
                    t2->Next = t2->Next->Next; //��������� ������� � ������
                else
                    t2->Next = head;
            }
        }
        p = head; //������� � ������, ���� ����� ����� ��� ��������
        if (p->Inf > elem->Inf) //�������� �� ������� ����� �������
        {
            elem->Next = p;
            head = elem;
            tail->Next = head;
            return;
        }
        while (p->Next != head && p->Next->Inf < elem->Inf) //���� ��������� �� ������ ������ ��������
            p = p->Next;
        if (p->Next != head) //�, ���� ��������� �� ������, �������� ������� ����� ���������
        {
            t1 = p->Next;
            p->Next = elem;
            elem->Next = t1;
        }
        else
        {
            p->Next = elem;
            elem->Next = head;
            tail = elem; //����� �����
        }
        /*cout << " ������� ������� - " << elem->Inf << "\n";
        while (elem->Next != tmp) {
        elem = elem->Next;
        }
        if (elem->Inf < elem->Next->Inf) {
        cout << " ������� ����������.\n";
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
    void toBeg() {
        elem = head;
    }

    // ��������� ��������� �� �������������� ����� �������� ��������
    T& GetCurrInfPtr()
    {
        if (elem)
        {
            return elem->Inf;
        }
        return head->Inf;
    }

    T getCurrInf() // get current elem copy Inf - ��������� ����� �������������� ����� 
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
    //-------------------------------------------------------------------------------------------
    // ������� �������� �����������, ������ ���������� �������� ������� �������� ���� ���������
    //-------------------------------------------------------------------------------------------
    /*����������*/
    ~List()
    {
        del_all();
    }

    //�������
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
        cout << "������ ������������." << endl;
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

    //�������� �� ������ �������������
    Iterator(const Iterator<T> &iterator)
    {
        iter = iterator;
    }

    void toBeg() {
        iterelem = iterhead;
    }

    //��������� ��������� �� �������������� ����� �������� ��������
    T& GetCurrInfPtr()
    {
        if (iterelem)
        {
            return iterelem->Inf;
        }
        return iterhead->Inf;
    }

    //get current elem copy Inf - ��������� ����� �������������� ����� 
    T getCurrInf1()
    {
        if (iterelem)
        {
            return iterelem->Inf;
        }
        return iterhead->Inf;
    }

    //��������� ��������� �� ������� ������� � ������
    void setCurrToHead()
    {
        iterelem = iterhead;
    }

    //��������� ��������� �� ������� ������� � �����
    void setCurrToTail()
    {
        iterelem = itertail;
    }

    //�������� ������������� ��������� � ������
    bool isEmpty() const
    {
        return iterhead == 0;
    }

    //������������� �������� !, ������������ ������������� ��������� � ��������� ������
    bool operator! () {
        return (iterhead != NULL); // ���� ������ ����������� ()
    }

    //�������� ��������� �� ������
    typename List<T>::TElem* getHead()
    {
        return iterhead;
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
            do   //���� �� ������ �� �����
            {
                TElem *temp = iterhead; //��������� ���������� ��� �������� ������ ���������� ��������
                iterhead = iterhead->Next;
                delete temp; //����������� ����� ������������ ������
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

    //�������� ����������
    for (int i = 1; i <= 10; i = i + 1)
    {
        tmp = rand() % 1000000;
        student_test.addToBegin(tmp);
        student_test1.AddBeforeHead(tmp);
        //student_test.addToEnd(i);
    }
    //cout << " My list " << endl;
    cout << " ������ �� 1000000 ���������. ����������." << endl;
    //student_test.show();

    start_time = clock(); // ��������� �����
    student_test.sort();
    end_time = clock(); // �������� �����
    search_time = end_time - start_time; // ������� �����
    cout << " ����� ������ ���������� ��������: " << ((float)search_time) / CLOCKS_PER_SEC << " �.";

    start_time = clock(); // ��������� �����
    student_test1.SortListBiDir();
    end_time = clock(); // �������� �����
    search_time = end_time - start_time; // ������� �����
    cout << "\n ����� ������ ���������� � �������: " << ((float)search_time) / CLOCKS_PER_SEC << " �.\n";

    ///************************************************************************/
    ///**/
    ///************************************************************************/

    //�������� ��������� ������� ������
    student_test.del_all();
    for (int i = 1; i <= 10; i = i + 2)
    {
        tmp = rand() % 25;
        student_test.addToBegin(tmp);
        student_testcopy.addToBegin(tmp);
    }
    cout << "\n ������:" << endl;
    student_test.show();
    student_testcopy.show();

    //add to end
    tmp = rand() % 100;
    cout << endl << "\n ���������� �������� � �����: " << tmp << endl;
    student_test.addToEnd(tmp);
    student_test.show();
    cout << endl;

    //add to beg
    tmp = rand() % 100;
    cout << endl << "\n ���������� �������� � ������: " << tmp << endl;
    student_test.addToBegin(tmp);
    student_test.show();


    //����� �������� � ��������� ���. ������
    cout << "\n\n ������� �������� �������� ��� ������\n";
    int val;
    cin >> val;
    student_test.found(val);

    /*//add after num
    int num, value;
    cout << "\n\n ������� ����� ��������, ����� �������� ����� �������: ";
    cin >> num;
    cout << " ������� �������� ��������: ";
    cin >> val;
    student_test.addAfterNum(val, num);
    student_test.show();*/

    //del elementa s Inf
    cout << "\n\n ������� �������� ��������, ������� ���������� �������:\n";
    cin >> val;
    student_test.del_Inf(val);
    student_test.show();


    //������������ �������� ��������
    cout << "\n\n ������� �������� ��������, ������� ���������� ��������\n";
    cin >> val;
    student_test.sort_elem(val);
    student_test.show();

    //�������������� �������� ��������
    cout << "\n\n ���������� �������� � ������:\n";
    student_test.addToBegin(28);
    student_test.show();
    cout << "\n\n �������������� �������� ��������:\n";
    student_test.sort_now_elem();
    student_test.show();

    /*******************************************************/
    //������������� �������� !, ������������ ������������� ��������� � ��������� ������
    cout << "\n ����������� ������������� ��������� � ��������� ������:\n";
    if (!student_test) cout << "\n ������ �� ����\n";
    else cout << "\n ������ ����\n";

    /*******************************************************/
    //����������� ������
    cout << "\n ����� ������ - ����� �������\n";
    student_testcopy = student_test;
    student_testcopy.show();

    /************************************************************************/
    /*������� �������*/
    /************************************************************************/

    // ��������� ��������� �� �������������� ����� �������� 
    int *a = &student_test.GetCurrInfPtr();
    cout << "\n ������� ������� " << *a << endl;

    /*//�������� ����, ��� ���� �� �������� ������������� ��������� �� �������������� ����� �������� ������
    *a = 20;
    student_test.show();*/
    /**/
    //��������� ����� �������������� ����� 
    int b = student_test.getCurrInf();
    cout << "\n ����� �������������� ����� �������� ��������\n " << b << endl;

    //��������� �������
    ++student_test;
    b = student_test.getCurrInf();
    cout << "\n ��������� � ���������� ��������\n " << b << endl;

    //������� � ������ ������
    student_test.setCurrToHead();
    b = student_test.getCurrInf();
    cout << "\n ������ ������ - ������� �������\n " << b << endl;

    //�������� ����������
    cout << "\n ���������� ��������, ���������� ���������:\n" << b << endl;
    student_testcopy = student_test;
    student_test.sort();
    student_testcopy.sort_bubble();
    student_test.show();
    student_testcopy.show();

    cout << endl << endl;

    return 0;
}

