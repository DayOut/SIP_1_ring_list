#pragma once

#include "SIP_1 (ring_list).cpp"
#include <string>

/*
    как выяснил суть всех лаб в том, что ты изначально разрабатываешь класс List 
    который может работать с любыми данными, будь то число или друга структура.

    вторая лаба - это уже конкретная задача - написание стркутуры для универа

    четвертая лаба - модифицируешь свой универсальный список для конкретной задачи
    а точнее создаешь списки студентов/групп/факультетов... 

    ---------------------------------------------------------------------------------
    на счет ListName.compare(rList.ListName)
    string объявленая через std::basic_string<TCHAR> имеет уже набор готовых функций
    в частности это compare. Метод уже оптимизированный до нас сравнивающий посимвольно на 
    совпадение двух строк и возвращающий значения. Их я рассписывал в студенте, но повторюсь 
    0 - полное совпадение
    1 - текущий студент больше (имеется в виду, что то первые символы в его имени/фамилии/отчестве 
                                будут стоять выше по алфавиту)
    -1 - текущий студент меньше


*/

template <typename T>
class NamedList : public List<T>
{
public:
    //std::basic_string<TCHAR> это готовое решение массива символов типа TCHAR.
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
