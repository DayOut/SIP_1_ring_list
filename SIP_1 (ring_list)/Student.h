#pragma once

#include <string>
#include <iostream>
#include <tchar.h>

//для автоматического выбора юникода или ANSI 
#ifdef UNICODE 
#define outputstream    std::wostream
#define inputStream     std::wistream
#define myout           std::wcout
#define TS              wchar_t
#else
#define outputstream    std::ostream
#define inputStream     std::istream
#define myout           std::cout
#define TS              char
#endif


class Student
{
public:
    Student();
    Student(const Student&);

    void setName (std::basic_string<TS>&);
    std::basic_string<TS> getName();

    void setLastname (std::basic_string<TS>&);
    std::basic_string<TS> getLastname();

    void setSurname (std::basic_string<TS>&);
    std::basic_string<TS> getSurname();

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
        вся логика класса завязана на этой приватной функции compareStudents
        В ней идет сравнение сначала отчества, имени и фамилии. 
        Если функция возвращает 
        0 - полное совпадение
        1 - текущий студент больше (имеется в виду, что то первые символы в его имени/фамилии/отчестве будут стоять выше по алфавиту)
        -1 - текущий студент меньше

    */
    int compareStudents (const Student&) const;

    std::basic_string<TS> _StName{}; //объявляем строку сразу пустой
    std::basic_string<TS> _StLastname{};
    std::basic_string<TS> _StSurname{};
    short int _StYearOfBirht;
    float _StAverMark;
};
