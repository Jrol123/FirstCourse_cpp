#include <iostream>
#include <iomanip>
using namespace std;

//� ���� ������ �� ������� ���������� ����� x1, y1 ������ ������� �� ������ �������
//� x2, y2 ������ ������� � ������ �������

int main()
{
    double a, b, c, d, x1, x2, y1, y2;
    pair<double, double> vtorayasist, obr; // x | y
    cin >> a >> b >> c >> d >> x1 >> y1 >> x2 >> y2;

    // �����
    vtorayasist.first = a; //���� ������ ������� (x)
    vtorayasist.second = b; //���� ������ ������� (y)

    obr.first = c - vtorayasist.first; //��� ������ ������� x
    obr.second = d - vtorayasist.second; //��� ������ ������� y

    //��������� �����, ���� ��� ������ ������� (�� �� ������ = 1)
    pair<double, double> fPtr {(-a+x1)/obr.first, (-b+y1)/obr.second},
    sPtr {a+x2*obr.first, b+y2*obr.second}; // x | y

    cout << fixed << setprecision(3) << fPtr.first << " " << fPtr.second << " " << sPtr.first << " " << sPtr.second;

    return 0;
}