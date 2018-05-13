// sip_1.cpp: ���������� ����� ����� ��� ����������� ����������.
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

    //������� ���������� �������� � ����� ������
    void addToEnd(T value)
    {
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������
        tmp->Next = tail ? tail->Next : tmp;
        if (tail)
        {
            tail->Next = tmp;
        }
        tail = tmp;

    }

    //���������� � ������ ������
    void addToBegin(T value)
    {
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������
        if (!tail)
            tail = tmp;
        else
            tmp->Next = tail->Next;
        tail->Next = tmp; //��������� � ������� �������� �� ������
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
        TElem *element = found(a) ? elem : NULL; //���� ������ � ���� ������� ����
        if (element != NULL) {
            TElem *prev = element;
            if (prev == prev->Next) //���� ������� ���� � ������
                tail = NULL;
            else {
                do {
                    prev = prev->Next;
                } while (prev->Next != element); //������� ���������� �������
                prev->Next = element->Next; //�������� �������
                if (element == tail) //���� ������� ��� �������
                    tail = prev;
            }
            delete element; //������� �������
        }
    }

    //delete all
    void del_all() {
        if (tail) {
            tail->Next = NULL;
            while (tail != NULL)  //���� �� ������ �� �����
            {
                TElem *temp = tail; //���������� ��� ������ ���������� ��������
                tail = tail->Next;
                delete temp;
            }
            tail = NULL; //�������� �����
        }
    }

    //������������ ������ ��������
    void sort_elem(T value) {
        if (tail) {
            TElem *newElement = new TElem;
            newElement->Inf = value; //������� ����� �������
            TElem *current = tail; //��������� ��������� � �����
            if (current->Next->Inf < value) { //���� ����� �������� ����� ������
                do { //���� ����������
                    current = current->Next;
                } while (current->Next->Inf < value && current != tail);

                if (current == tail) //���� ����� �������� �����
                    tail = newElement;
            }
            newElement->Next = current->Next; //��������� �������
            current->Next = newElement;
        }
    }

    //������������ �������� �������� (�������� ��� �� ������ � ��������� � ������ �����)
    void sort_now_elem() {
        if (tail && elem && elem->Inf > elem->Next->Inf) { //���� ������� ������ �������� � ����� �����������
            TElem *prev = tail;
            do {
                prev = prev->Next;
            } while (prev->Next != elem); //������� ���������� �������
            prev->Next = elem->Next; //�������� �������
            if (elem == tail) //���� ������� ��� �������
                tail = prev;
            //������ ������� ������� � ������ �����
            TElem *current = tail; //��������� ��������� � �����
            if (current->Next->Inf < elem->Inf) { //���� ����� �������� ����� ������
                do { //���� ���������� ����� ���, ���� ���������
                    current = current->Next;
                } while (current->Next->Inf < elem->Inf && current != tail);

                if (current == tail) //���� ����� �������� �����
                    tail = elem;
            }
            elem->Next = current->Next; //��������� �������
            current->Next = elem;
        }
    }

    //����� ������
    void show()
    {
        if (tail) // ���� ������ ����������� ()
        {
            elem = tail->Next;
            do
            {
                cout << elem->Inf << "   ";
                elem = elem->Next; //������� �� ����� ������
            } while (elem != tail->Next); //� ������ ���������� ������ ��������� ���� �� ������ ������� ���������
        }
    }
    /*******************************************************************/

    T getCurrInf() // get current elem copy Inf - ��������� ����� �������������� ����� 
    {
        return elem ? elem->Inf : 0;
    }

    //��������� ��������� �� ������� ������� � ������
    void setCurrToHead()
    {
        elem = tail->Next;
    }

    //��������� ��������� �� ������� ������� � �����
    void setCurrToTail()
    {
        elem = tail;
    }

    //������������� �������� !, ������������ ������������� ��������� � ��������� ������
    bool operator! () {
        return tail; // ���� ������ ����������� ()
    }

    //������������� �������� ������������
    List<T>& operator=(const List<T>& right)
    {
        if (this != &right) //�������� �� ���������������� 
        {
            TElem *leftHead = tail->Next;
            TElem *rightHead = right.tail->Next;
            if (right.tail != NULL) //���� right �� ����
            {
                do //���� ���� right and left
                {
                    leftHead->Inf = rightHead->Inf;
                    leftHead = leftHead->Next;
                    rightHead = rightHead->Next;
                } while (rightHead != right.tail->Next && leftHead != tail->Next);
                //������ ����������, ������� ���������� �������� ������
                if (rightHead == right.tail->Next) {
                    TElem *del;
                    do
                    {
                        del = leftHead;
                        leftHead = leftHead->Next;
                        delete del;
                    } while (leftHead != tail->Next);
                }
                //����� ����������, ��������� �������� �� ������� � �����
                else if (leftHead == tail->Next) {
                    do //���� ���� right
                    {
                        addToEnd(rightHead->Inf);
                        rightHead = rightHead->Next;
                    } while (rightHead != right.tail->Next);
                }
            }
            else del_all(); //������� ��� �������� �� left
        }
        return *this;
    }

    //����������� �����������
    List<T>(const List<T>& right)
    {
        elem = NULL;
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
        elem = tail = NULL;
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

private:
    //�������� ��������� �� ������
    TElem* getHead()
    {
        return tail->Next;
    }

    // ��������� ��������� �� �������������� ����� �������� ��������
    T& GetCurrInfPtr()
    {
        return elem ? elem->Inf : tail->Next->Inf;
    }

};

template <class T>
class Iterator {
private:
    List<T>::TElem *listP; //��������� �� ������

public:

    Iterator(List<T>& list)
    {
        listP = list.tail;
    }

    //�������� �� ������ �������������
    Iterator(Iterator<T>& iterator)
    {
        listP = iterator.listP;
    }

    Iterator<T>& operator++()
    {
        if (listP != 0)
        {
            listP = listP->Next;
        }
        return *this;
    }

    Iterator<T>& operator=(Iterator<T>& right)
    {
        if (this != &right)
        {
            listP = right.listP;
        }
        return *this;
    }

    Iterator<T>& operator=(List<T>& list)
    {
        if (this != &list)
        {
            listP = list.tail;
        }
        return *this;
    }

    bool operator!()
    {
        return listP;
    }

    T getCurrInf()
    {
        return (listP) ? listP->Inf : NULL;
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

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    int tmp, b;
    unsigned int start_time, end_time, search_time;
    List<int> student_test, student_testcopy, student_sort;
    TBList<int> student_test1;
    //�������� ������
    for (int i = 1; i <= 10; i = i + 2)
    {
        tmp = rand() % 25;
        student_test.addToBegin(tmp);
        student_testcopy.addToBegin(tmp);
    }
    cout << "\n ������:" << endl;
    student_test.show();

    //List<int> st(student_test); //���. ����������� �����������

    while (true) {

        int variant = menu();

        switch (variant) {
        case 1:
            //�������� ����������
            for (int i = 1; i <= 1000000; i = i + 1)
            {
                tmp = rand() % 1000000;
                student_sort.addToBegin(tmp);
                student_test1.AddBeforeHead(tmp);
            }
            cout << " ������ �� 1000000 ���������. ����������.\n" << endl;
            start_time = clock(); // ��������� �����
            student_sort.sort();
            end_time = clock(); // �������� �����
            search_time = end_time - start_time; // ������� �����
            cout << " ����� ������ ���������� ��������: " << ((float)search_time) / CLOCKS_PER_SEC << " �.";

            start_time = clock(); // ��������� �����
            student_test1.SortListBiDir();
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
            student_test.sort_now_elem();
            student_test.show();
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
            //st.show();
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

