#pragma once

#include "SIP_1 (ring_list).cpp"
#include <string>

/*
    ��� ������� ���� ���� ��� � ���, ��� �� ���������� �������������� ����� List 
    ������� ����� �������� � ������ �������, ���� �� ����� ��� ����� ���������.

    ������ ���� - ��� ��� ���������� ������ - ��������� ��������� ��� �������

    ��������� ���� - ������������� ���� ������������� ������ ��� ���������� ������
    � ������ �������� ������ ���������/�����/�����������... 

    ---------------------------------------------------------------------------------
    �� ���� ListName.compare(rList.ListName)
    string ���������� ����� std::basic_string<TCHAR> ����� ��� ����� ������� �������
    � ��������� ��� compare. ����� ��� ���������������� �� ��� ������������ ����������� �� 
    ���������� ���� ����� � ������������ ��������. �� � ����������� � ��������, �� ��������� 
    0 - ������ ����������
    1 - ������� ������� ������ (������� � ����, ��� �� ������ ������� � ��� �����/�������/�������� 
                                ����� ������ ���� �� ��������)
    -1 - ������� ������� ������


*/

template <typename T>
class NamedList : public List<T>
{
public:
    //std::basic_string<TCHAR> ��� ������� ������� ������� �������� ���� TCHAR.
    NamedList(const std::basic_string<TCHAR>& str)
    {
        ListName = str;
    }

    NamedList(NamedList<T>& str)
    {
        ListName = right.ListName;
        *this = right;
    }

    void setListName(std::basic_string<TCHAR>& str)
    {
        ListName = str;
    }

    std::basic_string<TCHAR> getListName() const
    {
        return ListName;
    }

    const NamedList<T>& operator=(NamedList<T>& right)
    {
        if (this != &right)
        {
            List<T>::operator=(right);
            ListName = right.ListName;
        }
        return *this;
    }

    bool operator==(NamedList<T>& rList)
    {
        return ListName.compare(rList.ListName) == 0;
    }

    bool operator!=(NamedList<T>& rList)
    {
        return ListName.compare(rList.ListName) != 0;
    }

    bool operator>=(NamedList<T>& rList)
    {
        return ListName.compare(rList.ListName) >= -1;
    }

    bool operator<=(NamedList<T>& rList)
    {
        return ListName.compare(rList.ListName) <= 1;
    }

    bool operator>(NamedList<T>& rList)
    {
        return ListName.compare(rList.ListName) == 1;
    }

    bool operator<(NamedList<T>& rList)
    {
        return ListName.compare(rList.ListName) == -1;
    }

private:
    std::basic_string<TCHAR> ListName;
};
