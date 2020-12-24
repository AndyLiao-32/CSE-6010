#include <stdio.h> // For printf function
#include <math.h> /* In order to utilize math function of C, we need to add this call.
                     For example, math function of log(), pow() and exp(). */

#define arr_size 19 /* This means that I have 19 data items, and before compiling, 
                        all the arr_size will be replaced by 19. */

int main(int argc, const char * argv[]) {
    /* In order to implement the powerlaw, we have to find out the coefficient (c) 
       and the power (a) */
    // Powerlaw equation: z = cu^a => logz = logc + alogu

    // First, set the data Mass & Max Speed into array
    // x refer to Mass
    double mass[arr_size] = { 
        4.22E-04, 4.50E-04, 3.90E-04, 0.0138, 5.22E-06, 6.86E-06, 1.30E-06, 1.76E-07,
        7.47E-07, 7.89E-08, 2.05E-07, 9.0E-05, 1.70E-04, 0.0015, 4.73E-05, 0.002,
        0.002, 6.52E-05, 1.01E-04
    };
    // y refer to Max Speed
    double max_speed[arr_size] = { 
        36, 27, 25.92, 36, 6.48, 4.8, 3.6, 
        3.24, 6.84, 3.06, 4.32, 36, 36, 
        25.56, 6, 19.08, 18, 10.8, 23.76
    };

    /* For checking our powerlaw function, use a dummy powerlaw z = 5*(u^2), 
    and we should get c = 5, a = 2 in the final result.*/
    // Set dummy Mass and Max Speed data
    // Dummy Mass
    // double mass[n];
    // for (int i = 0; i < n; i++) {
    //     mass[i] = i + 1.0;
    // }
    // // Dummy Max Speed
    // double max_speed[n];
    // for (int i = 0; i < n; i++) {
    //     max_speed[i] = 5.0 * (mass[i] * mass[i]);
    // }
    /* We will then get the following print out: 
        The power law exponent is 2.000 and the coefficeint is 5.000 */


    // Second, we use x, y to represent the log value of Mass and Max_Speed. 
    // Convert Mass & Max Speed => log_Mass = log(Mass), log_Max_Speed = log(Max Speed)
    double log_Mass[arr_size]; // log(Mass)
    double log_Max_Speed[arr_size]; // log(Max_Speed)

    // Loop through each value and convert it into log()
    for (int i = 0; i < arr_size; i++) {
        log_Mass[i] = log(mass[i]);
        log_Max_Speed[i] = log(max_speed[i]);
    }

    // Third, calculating the value of the M matrix (m11, m12, m21, m22)
    double m11 = arr_size * 1.0; // m11 = 1*1*n and n = 19 (number of rows of the data)
    double m12;
    double m21;
    double m22;
    for (int i = 0; i < arr_size; i++) {
        m12 += log_Mass[i];
        m21 += log_Mass[i];
        m22 += pow(log_Mass[i], 2.0);
    }
    // printf("M = [[%.3f, %.3f],[%.3f, %.3f]]\n", m11, m12, m21, m22); 
    // M = [[19.000, -192.355],[-192.355, 2176.641]]


    /* Then, we know b = [b1, b2] = [(sum(y_i) and i from 0 to n-1), 
    (sum(x_i*y_i) and i from 0 to n-1)]*/
    // Calculate b vector
    double b1;
    double b2;
    for (int i = 0; i < arr_size; i++) {
        b1 += log_Max_Speed[i];
        b2 += log_Mass[i] * log_Max_Speed[i];
    }
    // printf("b1: %.3f & b2: %.3f\n", b1, b2); 
    // b1: 47.703 & b2: -430.891

    /* Next, according to M_inverse = (1/(m11*m22-m12*m21))*[[m22, -m12],[-m21, m11]], 
    now we can derive the value of k_0, k_1 (k = [k_0, k_1]_T)  */
    double k0;
    double k1;

    k0 = (1/(m11*m22-m12*m21))*(m22*b1-m12*b2);
    k1 = (1/(m11*m22-m12*m21))*(-m21*b1+m11*b2);
    // printf("k0: %.3f & k1: %.3f\n", k1, k0); 
    // k0: 0.227 & k1: 4.809

    /* Finally, we can calculate our final result of coefficient and power via above data*/
    // k0 + k1*x = y which equals to logc + logu^a => k0 = e^c & k1 = a
    double a = k1; // a = power or we call it exponent, which is 0.227
    double c = exp(k0); // c = coefficient, which is 122.620
    // printf("a: %.3f & c: %.3f\n", a, c);
    // a: 0.227 & c: 122.620

    printf("The power law exponent is %.3f and the coefficeint is %.3f.\n", a, c);
    // Print Out: The power law exponent is 0.227 and the coefficeint is 122.620.

    /* For compiling and running C program on my operating system (MacOS), I type the command 
    "gcc /Users..../powerlaw.c" on my terminal, then the compiler "clang" 
    will help me compile the program.*/
}