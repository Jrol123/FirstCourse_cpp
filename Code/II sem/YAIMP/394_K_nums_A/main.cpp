#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief ���������� �������� ��� ������ ������������ �������.
 *
 * @param count_problems ���������� �����.
 * @param init_matrix ��������� �������.
 * @return ������� ��������� �����������.
 */
vector<pair<int, int>> Kuhn_Mankres(const unsigned int& count_problems, const vector <vector <int>>& init_matrix)
{
    /// ����������� �������� ��� �����
    vector<int> min_row(count_problems, 0);
    /// ����������� �������� ��� ��������.
    vector<int> min_column(count_problems, 0);
    /// ������� ���������� �����.
    vector<int> marked_indexes(count_problems, -1);

    for (int row = 0; row < count_problems; row++)
    {
        /// ������� ���������� ��������.
        vector<int> visited_column(count_problems, -1);
        /// ����������� �������� ��� ������������ ��������.
        vector<int> unmarked_column_min(count_problems, __INT_MAX__);
        /// ���������� �������.
        vector<bool> visited(count_problems, false);

        /// ���������� ������.
        int marked_row = row;
        /// ���������� �������.
        int marked_column = -1;
        /// ������� � ���������� ���������.
        int min_index_column;

        // ���� �� ������ ��� �������.
        while (marked_row != -1)
        {
            min_index_column = -1;

            // ����� ����������� �������� ��� ��������.
            for (int column = 0; column < count_problems; column++)
            {
                if (visited[column])
                    continue;

                /**
                 * @brief ������� ����� ��������� � ����������� ���������.
                 *
                 * ������������ ��� ����������� ����, ��������� ������� ��������� ��������� ��������� ������.
                 */
                int delta = init_matrix[marked_row][column] - min_row[marked_row] - min_column[column];

                // ��������� ����������� �������� ��� �������� �������.
                if (delta < unmarked_column_min[column])
                {
                    unmarked_column_min[column] = delta;
                    visited_column[column] = marked_column;
                }

                // ����� ����������� ��������.
                if (min_index_column == -1 || delta < unmarked_column_min[min_index_column])
                    min_index_column = column;
            }

            // ��������� �����.
            int diff = unmarked_column_min[min_index_column];

            // ��������� ����� ����� � ��������
            for (int column = 0; column < count_problems; column++)
            {
                if(!visited[column])
                    unmarked_column_min[column] -= diff;

                min_row[marked_indexes[column]] += diff;
                min_column[column] -= diff;
            }

            // �������� ����� ������ � �������
            min_row[row] += diff;
            visited[min_index_column] = true;
            marked_column = min_index_column;
            marked_row = marked_indexes[min_index_column];
        }

        // ���������� ���������� �����.
        for (; visited_column[min_index_column] != -1; min_index_column = visited_column[min_index_column])
            marked_indexes[min_index_column] = marked_indexes[visited_column[min_index_column]];
        marked_indexes[min_index_column] = row;
    }

    /// ������ ��� ����������.
    vector<pair<int, int>> pair_comb;

    // �����
    for (int j = 0; j < count_problems; j++)
    {
        if (marked_indexes[j] != -1)
        {
            pair_comb.push_back(pair<int, int>(marked_indexes[j], j));
        }
    }

    return pair_comb;
}

int main()
{
    // �������������.

    /// ���������� �����.
    unsigned int count_problems;
    /// �������.
    vector <vector <int>> matrix;

    cin >> count_problems;

    // ���� �������.
    for (int row = 0; row < count_problems; row++)
    {
        matrix.push_back(vector<int>());

        for (int column = 0; column < count_problems; column++)
        {
            int tmp;
            cin >> tmp;
            matrix[row].push_back(--tmp);
        }
    }
    /// ������ ��� ����������.
    vector<pair<int, int>> pair_comb = Kuhn_Mankres(count_problems, matrix);
    /// �������� ���������.
    unsigned int result = 0;

    // �����.
    for (unsigned int index = 0; index < pair_comb.size(); index++)
    {
        result += matrix[pair_comb[index].first][pair_comb[index].second] + 1;
    }
    cout << result << endl;
}
