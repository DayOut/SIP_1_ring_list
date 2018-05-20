// sip_1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
//#include "blist.h"
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
    TElem *tail, *elem; //��������� �� ����� ������, elem - ��������� �� ������� �������
    int k = 0;

public:

    List() {
        elem = tail = NULL;
    }

    //���������� ��������
    void sort()
    {
        if (tail) {
            TElem *head = tail->Next;
            tail->Next = NULL; // ������ �� ���������� - ����������� ������
            mergeSort(head); // ���������
                             // ���� �����, ����� ������������
            TElem *tmp = head;
            do
            {
                tmp = tmp->Next;
            } while (tmp->Next);
            tail = tmp;
            tail->Next = head; // ������������ ������
            cout << "\n ���������� ����������� �������: " << k << "\n";
            k = 0;
        }
    }

    //������� ���������� �������� � ����� ������
    void addToEnd(T value)
    {
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������
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
        elem = tail;
    }

    //���������� � ������ ������
    void addToBegin(T value)
    {
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������
        if (tail)
            tmp->Next = tail->Next;
        else
            tail = tmp;
        tail->Next = tmp; //��������� � ������� �������� �� ������
        elem = tail->Next;
    }

    //����� ��������
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

    //�������� �������� � ��������� ���. ������
    void del_Inf(T a) {
        if (tail)
        {
            TElem *prev = tail;
            TElem *cur = tail->Next;
            do {
                if (cur->Inf == a) {
                    if (cur != cur->Next) {
                        prev->Next = cur->Next;
                        if (cur == tail)
                            tail = prev;
                    }
                    else
                        tail = NULL;

                    break;
                }

                prev = cur;
                cur = cur->Next;

            } while (cur != tail);

            delete cur;
        }
    }

    //delete all
    void del_all() {
        if (tail) {
            TElem *current, *next;
            current = tail->Next;
            tail->Next = NULL;
            tail = current; 
            // = current->Next;

            while (tail) 
            {
                current = tail;
                tail = tail->Next;
                delete current;
            }

            delete tail;
            tail = NULL;
            elem = NULL;
        }
    }

    //������������ ������ ��������
    void sort_elem(T value) {
        if (tail) {
            TElem *newElement = new TElem;
            newElement->Inf = value;
            TElem *current = tail;
            if (current->Inf < value) { //���� ��������� ����� ������
                newElement->Next = current->Next;
                current->Next = newElement;
                tail = newElement;
            }
            else {
                while (current->Next->Inf < value) {
                    current = current->Next;
                }
                newElement->Next = current->Next;
                current->Next = newElement;
            }

        }
    }

    void sort_now_elem()
    {
        // elem - ������� ������� (�����������)
        if (tail)
        {
            TElem *pos = NULL; // ������� ����� �������� ���� ��������� current
            TElem *prev = tail, *cur = tail->Next; // ������� ����� current � ��������� ������
            bool findFlag = false;

            while (cur != elem) // ���� �� ������ ���������� ����� ������� (elem)
            {
                if (cur->Inf >= elem->Inf) // ���� ����� ����� ��� �������
                {
                    pos = prev;
                    findFlag = true;
                    break;
                }
                prev = cur;
                cur = cur->Next;
            }

            for (; cur != elem; prev = cur, cur = cur->Next);

            if (!findFlag) // ��������� ������ �� ������������ ��������
            {
                cur = cur->Next;
                pos = prev;

                while (cur != tail->Next)
                {
                    if (cur->Inf >= elem->Inf) // ���� ��� ������ ���� � �� ����� (������ ���� ��������� ����� ������)
                    {
                        if (pos) // �������� �� ������ ���� ��������� ����� ��������� � �������
                        {
                            if (elem == tail)
                            {
                                tail = elem->Next;
                            }

                            prev->Next = elem->Next; // �������� �������

                            elem->Next = pos->Next; //�������
                            pos->Next = elem;
                        }

                        return;
                    }
                    pos = cur;
                    cur = cur->Next;
                }

                /*
                ���� � ������ ��� � �� ����� ����� -> ���� ��������� � �����
                ����� �� ��������� ��� � �����, ����� ������� ����, ��� ��� � ����� ������ ������� ���� ������ � ���� ������
                */

                //������� � ����� ������
                if (elem == tail)
                {
                    tail = prev;
                }

                prev->Next = elem->Next; // �������� �������

                elem->Next = pos->Next; //�������
                pos->Next = elem;
                if (pos == tail)
                    tail = elem;
                

                return;
            }

            //��������� ����� �� ������������ �������� 

            if (elem == tail)
                tail = prev;

            if (pos != elem)
            {
                prev->Next = elem->Next;// �������� �������
                elem->Next = pos->Next;//�������
                pos->Next = elem;
            }


        }
    }


   /* //������������ �������� �������� (�������� ��� �� ������ � ��������� � ������ �����)
    void sort_now_elem() {
        if (tail) // ���� ���� ������
        {
            TElem *prevNew = NULL; // ������� ����� �������� ����� �������
            TElem *prev = tail, *cur = tail->Next;
            bool found = false;

            while (cur != elem)
            {
                if (cur->Inf >= elem->Inf) // ����� ���� ���������
                {
                    prevNew = prev;
                    found = true;
                    break;
                }
                prev = cur;
                cur = cur->Next;
            }

            for (; cur != elem; prev = cur, cur = cur->Next);

            if (!found)
            {
                cur = cur->Next;
                while (cur != tail->Next)
                {
                    if (cur->Inf <= elem->Inf) {
                        if (elem->Next != cur) {

                        }
                        return;
                    }

                    prevNew = cur;
                    cur = cur->Next;


                }
                return;
            }


            if (prevNew != prev) // ���� ��������� ����� �� ����� ����������� ����� ����������� ���������, ������ ���� �����������
            {
                if (!prevNew)
                    prevNew = tail;

                if (prevNew == elem && prev == tail)
                {
                    prev->Next = elem->Next;
                    elem->Next = prev->Next;
                    prev->Next = elem;
                }
                else
                {
                    if (elem == tail)
                        tail = prev;
                    //�������� �������
                    prev->Next = elem->Next;

                    //�������
                    elem->Next = prevNew->Next;
                    prevNew->Next = elem;
                }

            }

            if (prevNew == tail)
            {
                elem->Inf > tail->Inf ? tail = elem : tail = tail;
            }
        }
    }*/

    //����� ������
    void show()
    {
        if (tail) // ���� ������ ����������� ()
        {
            TElem *tmp = tail->Next;
            do
            {
                cout << tmp->Inf << "   ";
                tmp = tmp->Next; //������� �� ����� ������
            } while (tmp != tail->Next); //� ������ ���������� ������ ��������� ���� �� ������ ������� ���������
        }
    }
    /*******************************************************************/

    T getCurrInf() // get current elem copy Inf - ��������� ����� �������������� ����� 
    {
        return elem->Inf;
    }

    //��������� ��������� �� ������� ������� � ������
    void setCurrToHead()
    {
        if (tail)
            elem = tail->Next;
    }

    //��������� ��������� �� ������� ������� � �����
    void setCurrToTail() {
        elem = tail;
    }

    //������������� �������� !, ������������ ������������� ��������� � ��������� ������
    bool operator! () {
        return tail != NULL;
    }

    //������������� �������� ������������
    List<T>& operator=(const List<T>& right)
    {
        if (this != &right) //�������� �� ���������������� 
        {
            TElem *leftHead = tail, *leftCur, *leftCurPrev;
            TElem *rightHead = right.tail, *rightCur;

            if (rightHead) // ���� ���� ������ ������
            {
                rightHead = rightHead->Next; //������� � ������ �� ������
                rightCur = rightHead;

                if (tail)
                {
                    leftHead = leftHead->Next;
                    leftCur = leftHead;
                    do //���� ���� right and left
                    {
                        leftCur->Inf = rightCur->Inf;
                        leftCurPrev = leftCur;
                        leftCur = leftCur->Next;
                        rightCur = rightCur->Next;
                    } while (rightCur != rightHead && leftCur != leftHead);

                    //������ ����������, ������� ���������� �������� ������
                    if (rightCur == right.tail->Next) {
                        TElem *del;
                        leftCurPrev->Next = leftHead;
                        tail = leftCurPrev;
                        do {
                            del = leftCur;
                            leftCur = leftCur->Next;
                            delete del;
                        } while (leftCur != leftHead);
                    }
                }
                //����� ����������, ��������� �������� �� ������� � �����
                else {
                    if (rightCur != rightHead) {
                        do //���� ���� right
                        {
                            addToEnd(rightCur->Inf);
                            rightCur = rightCur->Next;
                        } while (rightCur != right.tail->Next);
                    }
                }
            }
            else del_all(); //������� ��� �������� �� left
        }
        return *this;
    }

    //����������� �����������
    List<T>(const List<T>& right)
    {
        elem = tail = NULL;
        *this = right; // ����������� � ������� �������������� ��������� ������������
    }

    //������������� �������� - ������� � ���������� ��������
    List<T>& operator++()
    {
        elem = elem ? elem->Next : tail;
        return *this;
    }

    /*******************************************************************/
    /*����������*/
    ~List()
    {
        del_all();
    }

    //�������
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

    // ��������� ��������� �� �������������� ����� �������� ��������
    T& GetCurrInfPtr()
    {
        if (tail)
        {
            return elem->Inf;
        }
        //return elem->Inf;
        throw -1; // errcode -1 - ����������� ������

    }
    /*T& GetCurrInfPtr()
    {
        if (!elem)
        {
            elem = tail->Next;
        }
        return elem->Inf;
    }*/


private:
    void mergeSort(TElem *&root)
    {
        k++; //���������� ����������� �������
        TElem *list1, *list2;
        TElem *head = root;
        if ((head == NULL) || (head->Next == NULL))
        {
            return;
        }

        findMid(head, list1, list2);

        mergeSort(list1); //��������� ������ �����
        mergeSort(list2);

        root = mergeList(list1, list2);

    }

    TElem* mergeList(TElem *list1, TElem *list2)
    {
        TElem temphead = { 0, NULL }, *tail = &temphead;
        k++;
        while ((list1 != NULL) && (list2 != NULL)) //���� � ��������� ��� ���� ��������
        {
            TElem **min = (list1->Inf < list2->Inf) ? &list1 : &list2; //�������� �������
            TElem *Next = (*min)->Next;
            tail = tail->Next = *min;
            *min = Next;
        }
        tail->Next = list1 ? list1 : list2; //���� ���� �� ���������� ����������
        return temphead.Next;
    }

    void findMid(TElem *root, TElem *&list1, TElem *&list2)
    {
        /**
        ���������� ��������� �� ������� ��������� TElem<T> ����� � ��������� ������
        � ����� �������� ������������ ������ ����� ���� ���������
        */
        TElem *slow, *fast;

        //� ������ ������� ������ (��� ���� �������)
        if ((root == NULL) || (root->Next == NULL))
        {
            list1 = root;
            list2 = NULL;
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
            list1 = root;
            list2 = slow->Next;
            slow->Next = NULL;
        }
    }

    //�������� ��������� �� ������
    TElem* getHead()
    {
        if (tail)
            return tail->Next;
    }

};

template <class T>
class Iterator {
private:
    typename List<T>::TElem *cur; //��������� �� ������

public:
    Iterator()
    {
        cur = NULL;
    }

    Iterator(List<T>& list)
    {
        cur = list.tail;
    }

    //�������� �� ������ �������������
    Iterator(Iterator<T>& iterator)
    {
        cur = iterator.cur;
    }

    Iterator<T>& operator++()
    {
        cur = cur ? cur->Next : tail;
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
    }

    T& getCurrInfRef() // ������ �� �������������� ����� ��������
    {
        if (cur)
        {
            return cur->Inf;
        }
    }

};

using namespace std;
int menu()
{
    // ��������� ������� �����
    int variant;
    cout << "�������� �������\n" << endl;
    cout << "1.  ����������\n";
    cout << "2.  ���������� � ������ � � �����\n";
    cout << "3.  ����� �������� � ��������� ���. ������\n";
    cout << "4.  �������� �������� � ��������� ���. ������\n";
    cout << "5.  ������������ ������ ��������\n";
    cout << "6.  ������������ �������� ��������\n";
    cout << "7.  ������������� !, ������������ ������������� ��-� � ���������\n";
    cout << "8.  ����������� ������\n";
    cout << "9.  ����� ���. �����, ������� � ����., ������� ������\n";
    cout << "10. ����������� �����������\n";
    cout << "11. �����\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}



/*if (cur != 0)
{
cur = cur->Next;
}
return *this;*/


int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    int tmp, b;
    unsigned int start_time, end_time, search_time;
    List<int> student_test, student_testcopy, student_sort;
    //TBList<int> student_test1;
    //�������� ������
    for (int i = 1; i <= 10; i = i + 2)
    {
        //tmp = rand() % 25;
        tmp = i;
        student_test.addToBegin(tmp);
        //student_testcopy.addToBegin(tmp);
    }
    cout << "\n ������:" << endl;
    student_test.show();

    List<int> st(student_test); //���. ����������� �����������

    while (true) {

        int variant = menu();
        //tmp var
        int *tmpval = NULL;

        switch (variant) {
        case 1:
            //�������� ����������
            for (int i = 1; i <= 1000000; i = i + 1)
            {
                tmp = rand() % 1000000;
                student_sort.addToBegin(tmp);
                //student_test1.AddBeforeHead(tmp);
            }
            cout << " ������ �� 1000000 ���������. ����������.\n" << endl;
            start_time = clock(); // ��������� �����
            student_sort.sort();
            end_time = clock(); // �������� �����
            search_time = end_time - start_time; // ������� �����
            cout << " ����� ������ ���������� ��������: " << ((float)search_time) / CLOCKS_PER_SEC << " �.";

            start_time = clock(); // ��������� �����
                                  //student_test1.SortListBiDir();
            end_time = clock(); // �������� �����
            search_time = end_time - start_time; // ������� �����
            cout << "\n ����� ������ ���������� � �������: " << ((float)search_time) / CLOCKS_PER_SEC << " �.\n";

            //�������� ����������
            if (student_sort.isSorted())
                cout << " ������������ � ����. ��������� ��� - ������ ������������ �����.\n\n";
            break;

        case 2:
            //add to beg
            tmp = rand() % 100;
            cout << endl << "\n ���������� �������� � ������: " << tmp << endl;
            student_test.addToBegin(tmp);
            student_test.show();

            //add to end
            tmp = rand() % 100;
            cout << endl << "\n ���������� �������� � �����: " << tmp << endl;
            student_test.addToEnd(tmp);
            student_test.show();
            cout << endl;
            break;

        case 3:
            //����� �������� � ��������� ���. ������
            cout << "\n\n ������� �������� �������� ��� ������\n";
            int val;
            cin >> val;
            if (student_test.found(val))
                cout << " ������� ���������.\n";
            else
                cout << " ������� �� ���������.\n";
            break;

        case 4: //�������� �������� � ��������� ���. ������
            cout << "\n\n ������� �������� ��������, ������� ���������� �������:\n";
            cin >> val;
            student_test.del_Inf(val);
            student_test.show();
            break;

        case 5: //������������ ������ ��������
            cout << "\n\n ������� �������� ��������, ������� ���������� ��������\n";
            cin >> val;
            student_test.sort_elem(val);
            student_test.show();
            break;

        case 6: //������������ �������� ��������
            cout << "\n\n ������������ �������� ��������:\n";
            student_test.sort();
            student_test.show();
            try
            {
                student_test.del_all();
                for (int i = 0; i < 100; i++)
                {
                    std::cout << "Current elem : " << student_test.GetCurrInfPtr() << std::endl;
                    tmpval = &student_test.GetCurrInfPtr();
                    cin >> *tmpval;
                    student_test.sort_now_elem();
                    //cout << student_test << std::endl;
                    student_test.show();

                }
            }
            catch (int e)
            {
                cout << "\nSome error happened. Error code: " << e << endl;
            }
            
            break;

        case 7:
            //������������� �������� !, ������������ ������������� ��������� � ��������� ������
            cout << "\n ����������� ������������� ��������� � ��������� ������:\n";
            if (!student_test) cout << "\n ������ �� ����\n";
            else cout << "\n ������ ����\n";
            break;

        case 8: //����������� ������
            cout << "\n ����� ������ - ����� �������\n";
            student_testcopy = student_test;
            student_testcopy.show();
            break;

        case 9: //��������� ����� �������������� ����� 
            b = student_test.getCurrInf();
            cout << "\n ����� �������������� ����� �������� ��������\n " << b << endl;

            //��������� �������
            ++student_test;
            b = student_test.getCurrInf();
            cout << "\n ��������� � ���������� ��������\n " << b << endl;

            //������� � ������ ������
            student_test.setCurrToHead();
            b = student_test.getCurrInf();
            cout << "\n ������ ������ - ������� �������\n " << b << endl;
            break;

        case 10:
            cout << " ����� ������ - ����� �������\n";
            st.show();
            break;

        case 11:
            exit(EXIT_SUCCESS);
            break;

        default:
            cout << " �� ������� �������� �������.\n";
            exit(EXIT_FAILURE);
            break;
        }
    }
    cout << endl << endl;

    return 0;
}
