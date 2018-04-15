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
        mergeSort(&head); // ���������
        findTail(); // ���� �����, ����� ������������
        show();
        //cout << "\n ���������� ����������� �������: " << k << "\n";
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
    // ��� ���� mergeSort(struct TElem **root), �� ��� �� �� ��� ������������, ��� ����� ��� ���������
    // ��� ��� ������ ����� ������ ������� �� ������
    //-------------------------------------------------------------------------------------------
    void mergeSort(TElem **root)
    {
        // ������� ���������� �����, ������ ���-�� � ��������� �������������, �� � �� ���� ���� ������ 
        // ��������, ������� �������� � ���� ����

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

        if (!head->Next) // ���� ������ ����������� ()
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
    // �������� �� ����� ���������� �������, �� ���������� ���� ������������ delete ���� ���
    // ���, �������, ������ delete ������ ���� ��� � ���� �������, ���������� �� �������� �������� 
    // �� � ����� ��� cout-�
    // � ������� ��������� ������ �������� ������ 
    //-------------------------------------------------------------------------------------------
    //�������� �������� � ��������� ���. ������
    void del_Inf(T a) {

        if (!head)
        {
            return;
        }

        elem = head;

        TElem *tmp;

        if (a == head->Inf) {
            tmp = head; // ������� ���
            tail->Next = head->Next;
            head = head->Next;
            elem = head;
        }
        //-------------------------------------------------------------------------------------------
        else if(a == tail->Inf)
        {
            //�������� �������� ���� ������, ����� ����� ������� ����� ������� =(
            tmp = head;
            TElem *tmpTail = tail; // ��������, � �� ����� �� �������. ��-�� ����, ��� delete ����� ���� ���� � �������, 
                                // � ������� ����� ������ ������� tail...

            while (tmp->Next != tail)
            {
                tmp = tmp->Next;
            }
            tmp->Next = head; // �������� �� ������ �������� ������� ��� ��������
            tail = tmp; // ������� ����� ��� �������� �������
            tmp = tmpTail; // �������� ��������� ������� � ���������� tmp
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
            head = elem = tail = NULL; //��������
        }
    }

    //������������ ������ ��������
    void sort_elem(T value) {
        elem = head;
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������

        //-------------------------------------------------------------------------------------------
        // ��������� ������������� ������
        //-------------------------------------------------------------------------------------------

        if (head->Inf >= value) {
            
            tmp->Next = head;	// ��������� � ������� �������� �� ������
            head = tmp;			// ������ ������ �� ����� �������
            tail->Next = head;	// ������ ��������� �� ������ ������
        }
        else {
            while (elem != tail && value > elem->Next->Inf)
            {
                elem = elem->Next; // ������� �� ����� ������
            }
            tmp->Next = elem->Next;
            elem->Next = tmp;
        }
    }


    //-------------------------------------------------------------------------------------------
    //��� ������� �� ����� (�� ��� � ��)
    //-------------------------------------------------------------------------------------------
    //��������� �������������� ����� ��������
    /*
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
    }*/


    //������������ �������� ��������
    void sort_now_elem() 
    {
        // elem - ������� ������� (�����������)
        // tmp - ������

        // �������� �� ������ ������
        if (!head || !tail) 
            return; 

        // �������� �� ������� "��������" ��������
        if (!elem) 
            elem = head;

        TElem *tmp = head;

        if (elem == head)
        {
            if (elem->Inf <= head->Next->Inf)
                return; // ������ ����������� ������ ���
            //�������� 
            head = head->Next;
            tail->Next = head;
        }
        else
        {
            //������� ��-� ����� �������
            while (tmp->Next != elem)
            {
                tmp = tmp->Next;
            }

            if (elem == tail)
            {
                if (tmp->Inf < elem->Inf)
                    return;// ����� ��� ������ �����������

                           //��������
                tail = tmp;
                tail = elem->Next;
            }
            else
            {
                if (tmp->Inf < elem->Inf && elem->Inf < elem->Next->Inf)
                    return;// ����� ��� ������ �����������

                           // ��������
                tmp->Next = elem->Next;
                tmp = elem;
                elem = head;
            }
        }

        

        // ���� ������� ������ ���������� - ���������� ������ ����� �������� �������� �� ������ ����� ������
        // ����� �� ����� �����
        tmp = (elem->Inf > elem->Next->Inf) ? elem->Next : head;

        while (elem->Inf > tmp->Inf)
        {
            // ����� ������ �����
            if (elem->Inf <= tmp->Next->Inf) 
            {
                //��������
                elem->Next = tmp->Next;
                tmp->Next = elem;
                break;
            }
            else if (tmp == tail) //���� ����� �� ����� ������
            {
                elem->Next = head;
                tail->Next = elem;
                tail = elem;
                break;
            }
            tmp = tmp->Next;
        }
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

    

    //������������� �������� ������������
    List<T>& operator=(List<T>& right)
    {
        //-------------------------------------------------------------------------------------------
        // ������: 
        //      ���������� ���� ������ ������������� ������, ���� � ���� ������ ��� ���� �������� - ����� �������������� 
        //      ������� �������������� ����, ���� � ����� ������ ��������� ������ - ������� ������ ��� ����� �������������� 
        //      ������ ����� ������ (������� ������ �����, �� ���� � ���� ������ ���� �� ������). ���� �� � ���� ������ ��������� ������
        //      ��������� �����, ��� ����� ������ ��������
        //
        //      �����, � ��� ��� �������� �������� ������� (��������� ���� �������)
        //          1) ����_�������     ����_������� - � ������ ������ �������������� ��� �����
        //          2) ����_�������     ���_�������� - ������� "������" ������� � ������ ������
        //          3) ���_��������     ����_������� - ��������� � ����� ����� ������ 
        //      

        if (this == &right) //�������� �� ���������������� 
        {
            return *this;
        }

        TElem *rightHead = right.getHead();
        TElem *rightCurrent = rightHead;

        TElem *tmp = head, *prevTmp = NULL; // ������� � ����� ������

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
        return *this;*/
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
        head = elem = tail = NULL; // ��������
    }

    //�������
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

    //�������� ��������� �� ������
    TElem* getHead()
    {
        return head;
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

    //private ������� ��� �������� �������� ��������
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
    //TBList<int> student_test1;

    //�������� ����������
    for (int i = 1; i <= 7; i = i + 1)
    {
        tmp = rand() % 100;
        student_test.addToBegin(tmp);
        //student_test1.AddBeforeHead(tmp);
        //student_test.addToEnd(i);
    }
    student_test.addToBegin(27);
    cout << " My list " << endl;
    cout << " ������ �� 1000000 ���������. ����������.\n" << endl;
    //student_test.show();

    start_time = clock(); // ��������� �����
    student_test.sort();
    end_time = clock(); // �������� �����
    search_time = end_time - start_time; // ������� �����
    cout << " ����� ������ ���������� ��������: " << ((float)search_time) / CLOCKS_PER_SEC << " �.\n";
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
    start_time = clock(); // ��������� �����
    //student_test1.SortListBiDir();
    end_time = clock(); // �������� �����
    search_time = end_time - start_time; // ������� �����
    cout << "\n ����� ������ ���������� � �������: " << ((float)search_time) / CLOCKS_PER_SEC << " �.\n";
    */
    //***********************************************************************
    //
    //************************************************************************

    /*
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
    student_test.found(val);*/

    /*//add after num
    int num, value;
    cout << "\n\n ������� ����� ��������, ����� �������� ����� �������: ";
    cin >> num;
    cout << " ������� �������� ��������: ";
    cin >> val;
    student_test.addAfterNum(val, num);
    student_test.show();*/

    /*
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
    student_test.show();*/

    //*******************************************************
    //������������� �������� !, ������������ ������������� ��������� � ��������� ������
    cout << "\n ����������� ������������� ��������� � ��������� ������:\n";
    if (!student_test) cout << "\n ������ �� ����\n";
    else cout << "\n ������ ����\n";

    //*******************************************************
    //����������� ������
    cout << "\n ����� ������ - ����� �������\n";
    student_testcopy = student_test;
    student_testcopy.show();

    //************************************************************************
    //������� �������
    //************************************************************************

    /*//�������� ����, ��� ���� �� �������� ������������� ��������� �� �������������� ����� �������� ������
    *a = 20;
    student_test.show();*/
    
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

