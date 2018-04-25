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
    TElem *head, *tail, *elem; //��������� �� ������ ������, elem - ��������� �� ������� �������
    int k = 0;

public:

    List() {
        head = NULL;
        tail = NULL;
        elem = NULL;
    }

    //���������� ��������
    void sort()
    {
        if (head) {
            tail->Next = NULL; // ������ �� ���������� - ����������� ������
            mergeSort(&head); // ���������
            findTail(); // ���� �����, ����� ������������
            cout << "\n ���������� ����������� �������: " << k << "\n";
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
        k++; //���������� ����������� �������
        TElem *list1, *list2;
        TElem *head = *root;
        if ((head == NULL) || (head->Next == NULL))
        {
            return;
        }

        findMid(head, &list1, &list2);

        mergeSort(&list1); //��������� ������ �����
        mergeSort(&list2);

        *root = mergeList(list1, list2);

    }

    TElem* mergeList(TElem *list1, TElem *list2)
    {
        TElem temphead = { 0, NULL }, *tail = &temphead;

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

    void findMid(struct TElem *root, struct TElem **list1, struct TElem **list2)
    {
        /**
        ���������� ��������� �� ������� ��������� TElem<T> ����� � ��������� ������
        � ����� �������� ������������ ������ ����� ���� ���������
        */
        struct TElem *slow, *fast;

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
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������
        tmp->Next = head;	// ��������� � ������� �������� �� ������
        if (!head) // ���� ������ ����������� ()
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

    //���������� � ������ ������
    void addToBegin(T value) // add_to_begin / add_begin
    {
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
            tail->Next = head;	// ������ ��������� �� ������ ������
        }
    }

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

    //�������� �������� � ��������� ���. ������
    void del_Inf(T a) {
        if (head) {
            elem = head;
            TElem * tmp;
            if (a == head->Inf) {
                tmp = head; // ������� ���
                tail->Next = head->Next;
                head = head->Next;
                elem = head; //������� a ������
            }
            else if (a == tail->Inf) //���� ��� �����
            {
                tmp = head;
                TElem *tmpTail = tail;
                while (tmp->Next != tail) //������� ����� �������
                {
                    tmp = tmp->Next;
                }
                tmp->Next = head; //������ �������� �������
                tail = tmp;
                tmp = tmpTail; //��, ��� ����� ������� delete
            }
            else {
                while (elem->Next->Inf != a)
                {
                    if (elem == tail && elem->Inf != a)
                        return;

                    elem = elem->Next;
                }
                tmp = elem->Next; // ������� ���
                elem->Next = elem->Next->Next;
            }
            delete tmp;
        }
    }

    //delete all
    void del_all() {
        if (head) // ���� ������ ����������� ()
        {
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
        TElem *tmp = new TElem; // �������� ������ �� ����� �������
        tmp->Inf = value;	// ���������� ��������

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

    //������������ �������� ��������
    void sort_now_elem() {
        // elem - ������� ������� (�����������)
        // tmp - ������
        if (head && tail) {
            if (!elem)
                elem = head;

            TElem *tmp = head;
            if (elem == head) //���� ������� ������
            {
                head = head->Next; //�������� �������
                tail->Next = head;
            }
            else
            {
                //������� ������� ����� �������
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
                if (elem->Inf <= tmp->Next->Inf) //����� ������ �����
                {
                    elem->Next = tmp->Next; //���������
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
    }

    //����� ������
    void show()
    {
        if (head) // ���� ������ ����������� ()
        {
            TElem *tmp = head;
            do
            {
                cout << tmp->Inf << "   ";
                tmp = tmp->Next; //������� �� ����� ������
            } while (tmp != head); //� ������ ���������� ������ ��������� ���� �� ������ ������� ���������
            cout << endl;
        }
    }
    /*******************************************************************/
    //�����, ����������� ��������� �� ������� ������� � ������(�����, ��� �������������) ������.
    void toBeg() {
        elem = head;
    }

    T getCurrInf() // get current elem copy Inf - ��������� ����� �������������� ����� 
    {
        if (elem && head)
            return elem ? elem->Inf : head->Inf;
        return 0;
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
    List<T>& operator=(const List<T>& right)
    {
        if (this == &right) //�������� �� ���������������� 
        {
            return *this;
        }
        // ������ ������ ��� ���, �� �������� ����� ��������� ��������
        TElem *rightHead = right.head; //��������� ������ ������ �� �������
        TElem *rightCurrent = rightHead; //������� ������� �� ����� �� ������

        TElem *tmp = head, *prevTmp = NULL; //������� � ����� ������
        if (rightHead)
        {
            while (rightCurrent && tmp) // ���� ��� ������ ���� �������� �� ������� � �����
            {
                tmp->Inf = rightCurrent->Inf;
                prevTmp = (tmp) ? tmp : NULL;
                tmp = (tmp->Next == head) ? NULL : tmp->Next;
                rightCurrent = (rightCurrent->Next == rightHead) ? NULL : rightCurrent->Next;
            }

            while (tmp && !rightCurrent) //���� ���� ������ ����� 
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

            while (!tmp && rightCurrent) //���� ���� ������ ������
            {
                addToEnd(rightCurrent->Inf);
                rightCurrent = (rightCurrent->Next == rightHead) ? NULL : rightCurrent->Next;
            }
        }
        else
        {
            del_all(); //���� ������ ������ ��������� ������ - ������� ����
        }

        findTail();

        return *this;
    }

    //����������� �����������
    List<T>(const List<T>& right)
    {
        head = NULL;
        elem = NULL;
        
        if (right.head != NULL)
        {
            *this = right; 
        }
    }

    //������������� �������� - ������� � ���������� ��������
    List<T>& operator++()
    {
        if (elem)
            elem = elem->Next;
        else
            elem = head;
        return *this;
    }

    /*******************************************************************/
    /*����������*/
    ~List()
    {
        del_all();
        head = elem = tail = NULL;
    }

    //�������
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

    // ��������� ��������� �� �������������� ����� �������� ��������
    

    //private ������� ��� �������� �������� ��������
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

    //�������� �� ������ �������������
    Iterator(const Iterator<T> &iterator)
    {
        iter = iterator;
    }

    void toBeg() {
        iterelem = iterhead;
    }

    //get current elem copy Inf - ��������� ����� �������������� ����� 
    T getCurrInf1()
    {
        return iterelem ? iterelem->Inf : iterhead->Inf;
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

private:

    //�������� ��������� �� ������
    typename List<T>::TElem* getHead()
    {
        return iterhead;
    }

    //��������� ��������� �� �������������� ����� �������� ��������
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
    List<int> student_test, student_testcopy;
    TBList<int> student_test1;
    //�������� ������
    for (int i = 1; i <= 10; i = i + 1)
    {
        tmp = rand() % 25;
        student_test.addToBegin(tmp);
        student_testcopy.addToBegin(tmp);
    }
    cout << "\n ������:" << endl;
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
        cout << "������� �������: " << student_test.getCurrInf();

        std::cin >> *val;
        student_test.sort_now_elem();

        student_test.show();
        std::cout << std::endl;
    }



    //---------------------------------------------------------

    //student_testcopy.show();
    List<int> st(student_test); //���. ����������� �����������

    int variant = menu();

    switch (variant) {
    case 1:
        //�������� ����������
        student_test.del_all();
        for (int i = 1; i <= 10; i = i + 1)
        {
            tmp = rand() % 100;
            student_test.addToBegin(tmp); // 
            student_test1.AddBeforeHead(tmp); 
        }

        cout << " ������ �� 1000000 ���������. ����������." << endl;

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

        //�������� ����������
        if (student_test.sort_bubble())
            cout << " ������������ ��� - ������ ������������ �����.\n";
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
    cout << endl << endl;

    return 0;
}

