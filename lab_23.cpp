#include <iostream>
#include <iomanip>

using namespace std;

void inputData(float* p, int n);
float average(const float* p, int n);
float minValue(const float* p, int n);
float maxValue(const float* p, int n);
float* filterAboveAverage(float* p, int n, int& newCount);

int main() {
    cout << "=== Анализ сенсора ===" << endl;

    int n;
    cout << "Введите количество измерений: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Ошибка!" << endl;
        return 1;
    }
    
    float* data = new float[n];
    cout << "Введите значения: ";
    inputData(data, n);
    
    float avg = average(data, n);
    float minVal = minValue(data, n);
    float maxVal = maxValue(data, n);
    
    cout << fixed << setprecision(1);
    cout << "Среднее значение: " << avg << endl;
    cout << "Минимум: " << minVal << endl;
    cout << "Максимум: " << maxVal << endl;
    
    int countAboveAvg;
    float* aboveAvgData = filterAboveAverage(data, n, countAboveAvg);
    
    cout << "Значения выше среднего:" << endl;
    for (int i = 0; i < countAboveAvg; i++) {
        cout << *(aboveAvgData + i) << " ";
    }
    
    delete[] data;
    delete[] aboveAvgData;
    
    return 0;
}

void inputData(float* p, int n) {
    for (int i = 0; i < n; i++) {
        cin >> *(p + i);
        if (*(p + i) < -50.0 || *(p + i) > 50.0) {
            cout << "Ошибка! Температура вне диапазона от -50 до +50" << endl;
            exit(1);
        }
    }
}

float average(const float* p, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *(p + i);
    }
    return sum / n;
}

float minValue(const float* p, int n) {
    float minVal = *(p);
    for (int i = 1; i < n; i++) {
        if (*(p + i) < minVal) {
            minVal = *(p + i);
        }
    }
    return minVal;
}

float maxValue(const float* p, int n) {
    float maxVal = *(p);
    for (int i = 1; i < n; i++) {
        if (*(p + i) > maxVal) {
            maxVal = *(p + i);
        }
    }
    return maxVal;
}

float* filterAboveAverage(float* p, int n, int& newCount) {
    float avg = average(p, n);
    newCount = 0;
    
    for (int i = 0; i < n; i++) {
        if (*(p + i) > avg) {
            newCount++;
        }
    }
    
    float* result = new float[newCount];
    
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (*(p + i) > avg) {
            *(result + index) = *(p + i);
            index++;
        }
    }
    
    return result;
}