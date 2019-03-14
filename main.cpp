#include <iostream>
using namespace std;

double ** newtonInterpolation(unsigned int points, double ** xyTab) {
    
    double ** diffQuotients = new double * [points - 1];
    for (int i = 0; i < points - 1; i++) {
        diffQuotients[i] = new double [points];
    }
    
    int rozmiar = points - 1;
    int xi = 2;
    
    for (int i = 0; i < points - 1; i++) {
        int xn = xi - 1;
        
        for (int j = 0; j < rozmiar; j++) {
            if (i == 0) {
                diffQuotients[i][j] = (xyTab[j + 1][1] - xyTab[j][1]) / (xyTab[j + 1][0] - xyTab[j][0]);
            }
            else
            {
                for (int l = 0; l < rozmiar; l++) {
                    diffQuotients[i][j] = (diffQuotients[i - 1][j + 1] - diffQuotients[i - 1][j]) / (xyTab[xn][0] - xyTab[xn - xi + 1][0]);
                }
                xn++;
            }
        }
        rozmiar--;
        xi++;
    }
    return diffQuotients;
}

void displayQuotients(double ** diffQuotients, int points){
    int iter = points - 1;
    for (int i = 0; i < points - 1; i++) {
        cout << "Ilorazy roznicowe rzedu " << i + 1 << endl;
        for (int j = 0; j < iter; j++) {
            cout << diffQuotients[i][j];
            if (j != iter - 1) {
                cout << ", ";
            }
        }
        iter--;
        cout << endl;
    }
}

double * coefficients(unsigned int points, double ** diffQuotients, double ** xyTab) {
    double * coefTab = new double[points];
    coefTab[0] = xyTab[0][1];
    for (int i = 0; i < points - 1; i++) {
        coefTab[i+1] = diffQuotients[i][0];
    }
    return coefTab;
}

double factors(int unknown, double ** xyTab, int iter)
{
    if (iter == 0) { return 1; }
    else {
        return factors(unknown, xyTab, iter - 1) * (unknown - xyTab[iter - 1][0]);
    }
}

double polymonial(unsigned int points, int unknown, double * coefTab, double ** xyTab) {
    double result = 0;
    for (int i = 0; i < points; i++) {
        result += coefTab[i] * factors (unknown, xyTab, i);
    }
    return result;
}



int main()
{
    unsigned int points = 0;
    int unknown = NULL;
    
    cout << "Podaj liczbe znanych punktow: ";
    cin >> points;
    
    double ** xyTab = new double * [points];
    for (int i = 0; i < points; i++) {
        xyTab[i] = new double[2];
    }
    
    for (int i = 0; i < points; i++) {
        cout << "Podaj x i y dla " << i+1 << " punktu: ";
        cin >> xyTab[i][0];
        cin >> xyTab[i][1];
    }
    
    /*
    EXAMPLE VALUES for points = 5
    xyTab[0][0] = 0;
    xyTab[0][1] = 0;
    xyTab[1][0] = 2;
    xyTab[1][1] = 8;
    xyTab[2][0] = 3;
    xyTab[2][1] = 27;
    xyTab[3][0] = 5;
    xyTab[3][1] = 125;
    xyTab[4][0] = 6;
    xyTab[4][1] = 216;
    */
    
    double ** diffQuotients = new double * [points - 1];
    diffQuotients = newtonInterpolation(points, xyTab);
    
    double * coefTab = new double [points - 1];
    coefTab = coefficients(points, diffQuotients, xyTab);
    
    cout << "Podaj obliczana liczbe: ";
    cin >> unknown;
    
    // DISPLAY DIFFERENTIAL QUOTIENTS
    displayQuotients(diffQuotients, points);
    
    // DISPLAY COEFFICIENTS
    cout << "Wspolczynniki: ";
    for (int i = 0; i < points; i++) {
        cout << coefTab[i] << ", ";
    }
    
    // DISPLAY POLYMONIAL
    double result = 0;
    result = polymonial(points, unknown, coefTab, xyTab);
    cout << endl << "Wartosc wielomianu dla " << unknown << " wynosi " << result << endl;
}
