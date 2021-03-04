#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

const double ini_a = 0.5;
const double ini_b = 0.3;

const int real_a_bound = 9; // a_probility = real_a_bound / 10.0
const int real_b_bound = 4; // b_probility = real_b_bound / 10.0

int main() {
    double theta_a    = ini_a;
    double theta_b    = ini_b;

    double avg_a      = ini_a;
    double avg_b      = ini_b;

    double is_a       = 0;
    double is_b       = 0;

    srand((int)time(NULL));
    int arr[10][10] = {0};
    int sum        = 0;
    ofstream output("show.csv");

    int count = 2;
    while(count <= 1000) {
        double a_head = 0, a_tail = 0;
        double b_head = 0, b_tail = 0;
        for(int i = 0; i < 10; ++i) {
            sum = 0;
            int bound = real_a_bound;
            if((rand() % 10 + 1) >= 6) bound = real_b_bound; // [1, 5] -> coin a, [6, 10] -> coin b
            for(int j = 0; j < 10; ++j) {
                arr[i][j] = (rand() % 10 + 1) <= bound? 1: 0;
                sum = arr[i][j]? sum + 1: sum;
            }
            double temp_a = pow(theta_a, sum) * pow((1 - theta_a), 10 - sum);
            double temp_b = pow(theta_b, sum) * pow((1 - theta_b), 10 - sum);
            double temp   = temp_a + temp_b;
            is_a = temp_a / temp;
            is_b = temp_b / temp;
            a_head += is_a * sum, a_tail += is_a * (10 - sum);
            b_head += is_b * sum, b_tail += is_b * (10 - sum);

            // cout << "sum: " << sum << ", temp_a: " << temp_a << ", temp_b: " << temp_b << endl;
        }
        theta_a = a_head / (a_head + a_tail);
        theta_b = b_head / (b_head + b_tail);
        avg_a += theta_a;
        avg_b += theta_b;
        output << avg_a / count << "," << avg_b / count++ << endl;
        // cout << "count: " << count << ", avg_a: " << avg_a / count << ", avg_b: " << avg_b / count++ << endl;
        // cout << "sum_a: " << avg_a << ", sum_b: " << avg_b << endl << endl;
    }
    return 0;
}