#include "Student.h"

Student::Student()
{
    _StYearOfBirht = _StAverMark = 0;
}

Student::Student(const Student& right)
{
    *this = right;
}

void Student::setName(std::basic_string<TS>& name)
{
    _StName = name;
}

std::basic_string<TS> Student::getName()
{
    return _StName;
}

void Student::setLastname(std::basic_string<TS>& lastname)
{
    _StLastname = lastname;
}

std::basic_string<TS> Student::getLastname()
{
    return _StLastname;
}

void Student::setSurname(std::basic_string<TS>& surname)
{
    _StSurname = surname;
}

std::basic_string<TS> Student::getSurname()
{
    return _StSurname;
}

void Student::setYearOfBirht(int year)
{
    _StYearOfBirht = year;
}

short int Student::getYearOfBirht()
{
    return _StYearOfBirht;
}

void Student::setAverMark(float averMark)
{
    _StAverMark = averMark;
}

float Student::getAverMark()
{
    return _StAverMark;
}

Student& Student::operator=(const Student& right)
{
    if (this != &right)
    {
        _StName = right._StName;
        _StSurname = right._StSurname;
        _StLastname = right._StLastname;
        _StYearOfBirht = right._StYearOfBirht;
        _StAverMark = right._StAverMark;
    }

    return *this;
}

int Student::compareStudents(const Student& right) const
{
    int result = _StSurname.compare(right._StSurname); //сравниваем отчество

    if (result == 0) // если полностью совпадает 
    {
        result = _StName.compare(right._StName); // проверяем имя 

        if (result == 0) // если имя и отчество совпадают
        {
            result = _StLastname.compare(right._StLastname); // проверяем фамилию
        }
    }

    return result; // возвращаем то, что получили
}

bool Student::operator==(const Student& right)
{
    return compareStudents(right) == 0;
}

bool Student::operator!=(const Student& right)
{
    return compareStudents(right) != 0; // нас удовлетворяет любой результат кроме 0 (см. Student.h там комментарий)
}

bool Student::operator>=(const Student& right)
{
    return compareStudents(right) != -1; // нас удовлетворяет любой результат кроме -1 (см. Student.h там комментарий)
}

bool Student::operator<=(const Student& right)
{
    return compareStudents(right) != 1; // нас удовлетворяет любой результат кроме 1 (см. Student.h там комментарий)
}

bool Student::operator>(const Student& right)
{
    return compareStudents(right) == 1;
}

bool Student::operator<(const Student& right)
{
    return compareStudents(right) == -1; // нас удовлетворяет любой результат кроме -1 (см. Student.h там комментарий)
}

outputstream& operator<<(outputstream& output, Student& right)
{
    output << right._StSurname << __T(" ") << right._StName << __T(" ")
        << right._StLastname << __T(" ") << right._StYearOfBirht << __T(" ")
        << right._StAverMark << std::endl;

    return output;
}


inputStream& operator >> (inputStream& input, Student& right)
{
    input >> right._StSurname >> right._StName 
        >> right._StLastname >> right._StYearOfBirht 
        >> right._StAverMark;

    return input;
}
