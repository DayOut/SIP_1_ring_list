#pragma once

#include <string>
#include <iostream>
#include <tchar.h>

//��� ��������������� ������ ������� ��� ANSI 
#ifdef UNICODE 
#define outputstream    std::wostream
#define inputStream     std::wistream
#define myout           std::wcout
#else
#define outputstream    std::ostream
#define inputStream     std::istream
#define myout           std::cout
#endif


class Student
{
public:
    Student();
    Student(const Student&);

    void setName (std::basic_string<TCHAR>&);
    std::basic_string<TCHAR> getName();

    void setLastname (std::basic_string<TCHAR>&);
    std::basic_string<TCHAR> getLastname();

    void setSurname (std::basic_string<TCHAR>&);
    std::basic_string<TCHAR> getSurname();

    void setYearOfBirht (int);
    short int getYearOfBirht();

    void setAverMark (float);    
    float getAverMark();

    Student& operator = (const Student&);
    bool operator == (const Student&);
    bool operator != (const Student&);
    bool operator >= (const Student&);
    bool operator <= (const Student&);
    bool operator > (const Student&);
    bool operator < (const Student&);

    friend outputstream& operator << (outputstream&, Student&);
    friend inputStream& operator >> (inputStream&, Student&);

private:
    /* 
        ��� ������ ������ �������� �� ���� ��������� ������� compareStudents
        � ��� ���� ��������� ������� ��������, ����� � �������. 
        ���� ������� ���������� 
        0 - ������ ����������
        1 - ������� ������� ������ (������� � ����, ��� �� ������ ������� � ��� �����/�������/�������� ����� ������ ���� �� ��������)
        -1 - ������� ������� ������

    */
    int compareStudents (const Student&) const;

    std::basic_string<TCHAR> _StName{}; //��������� ������ ����� ������
    std::basic_string<TCHAR> _StLastname{};
    std::basic_string<TCHAR> _StSurname{};
    short int _StYearOfBirht;
    float _StAverMark;
};
