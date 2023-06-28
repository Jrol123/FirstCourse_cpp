#include <iostream>
#include <vector>
#define vec std::vector
#define pr std::pair

template<typename type>
void print(type item)
{
    std::cout << item << std::endl;
}

/**
 * @brief ����� DSF (Disjoint Set Forest) ��� �������������� ��������.
 *
 * DSF ��������� ���������� ��������� � ����������, � ����� ��������� ��������� �������.
 *
 * @tparam type ��� ��������� ���������.
 */
template<typename type>
struct DSF
{
private:
    /**
     * @brief ������ ��������.
     *
     * ���������� ��� ��������� ���. \n
     * ����� ��������� � �������.
     */
    vec<pr<unsigned int, type>> mass_elements;

    /**
     * @brief ���������� ���������.
     *
     * ����� ��� �������� �� ����� �� ����� �������.
     */
    unsigned int size;

    /**
     * @brief ������� ��� �������� �������� ������������� �������� �� ������������ ��������.
     *
     * @param index �������� ������������� ������.
     * @return bool � ��������� �� ������ � ���������� ��������.
     */
    bool check_bounds(const unsigned int& index)
    {
        return (0 < index <= size);
    }

    /**
     * @brief ��������������� ����� ��� ����������� ��������.
     *
     * @param child_index ������ ��������, ��� ��������� ����� �������� � ��������� parent_index.
     * @param parent_index ������ ��������, � ��������� �������� ����������� ��������� child_index.
     */
    void combine_private(const unsigned int &child_index, const unsigned int &parent_index)
    {
        mass_elements[child_index].first = parent_index;
    }

    /**
     * @brief ��������������� ����� ��� ��������� ������ ��������� ��������.
     *
     * @���������< <b> ������ ����</b> \n
     * ������������ ��������� ������ ����. \n
     * ����������� � ���������� ������ �� ������������ ���� ����� �������, ����� ��� ��������� ��������������� �� �������� ����. \n
     * ����� �������� ������� �� �����: \n
     * https://neerc.ifmo.ru/wiki/index.php?title=���_(����������_�_�������_����_��������_��������)
     *
     * @param index_item ������ ��������, ����� ��������� �������� ����� ��������.
     * @return int � ����� ���������, � ������� ��������� �������.
     */
    int get_private(const unsigned int &index_item)
    {
        if (mass_elements[index_item].first != index_item)
        {
            mass_elements[index_item].first = get_private(mass_elements[index_item].first);
        }
        return mass_elements[index_item].first;
    }

public:

    /**
     * @brief ����������� ������ DSF.
     *
     * ���������� � ������� �������� ��� ���������.
     *
     * @param size ���������� ��������� � ���������.
     * @param elements ������ ��������� ���������.
     */
    DSF(const unsigned int &size, const vec<type> &elements)
    {
        this->size = size;
        mass_elements.resize(size);
        for (unsigned int index = 0; index < size; index++)
        {
            mass_elements[index].first = index;
            mass_elements[index].second = elements[index];
        }
    }

    /**
     * @brief ����� ��� ����������� ��������.
     *
     * ������� �������� ������������ ������������ (������� � 1-��).
     *
     * @param child_index ������ ��������, ��� ��������� ����� �������� � ��������� parent_index.
     * @param parent_index ������ ��������, � ��������� �������� ����������� ��������� child_index.
     * @pre 0 < < index <= size
     */
    void combine(const unsigned int &child_index, const unsigned int &parent_index)
    {
        if (!check_bounds(child_index) || !check_bounds(parent_index))
        {
            return;
        }
        return combine_private(child_index - 1, parent_index - 1);
    }

    /**
     * @brief ����� ��� ��������� ������ ��������� ��������.
     *
     * ������ �������� ������������ ������������ (������� � 1-��).
     *
     * @param index_item ������ ��������, ����� ��������� �������� ����� ��������.
     * @return int � ����� ���������, � ������� ��������� �������.
     * @pre 0 < index <= size
     */
    int get(const unsigned int &index_item)
    {
        if (!check_bounds(index_item))
        {
            return -1;
        }
        return get_private(index_item - 1) + 1;
    }
};

/**
 * @brief ������ ������������� ������ DSF
 */
void example_usage()
{
    // �������� ������� ������ DSF.
    DSF<int> dsf (5, {1, 2, 3, 4, 5});

    // ����������� ��������, � ������� ��������� �������� � ��������� 1 � 2.
    dsf.combine(1, 2);

    // ��������� ������ ���������, � ������� ��������� ������� � �������� 1.
    int set_number = dsf.get(1);

    // �����.
    print(set_number);
}

/**
 * @brief �������� �� ����-������������� �����.
 */
void test1()
{
    DSF<int> dsf (5, {1, 2, 3, 4, 5});

    dsf.combine(1, 2);

    int set_number1 = dsf.get(1);
    int set_number3 = dsf.get(3);

    print(set_number1);
    print(set_number3);

    print("");
}

/**
 * �������� �� ����� �� ������� �������.
 */
void test2()
{
    DSF<int> dsf (5, {1, 2, 3, 4, 5});

    dsf.combine(1, 2);

    int set_number = dsf.get(6);

    print(set_number);

    print("");
}

int main()
{
    test1();
//    test2();

    return 0;
}