// #include <iostream>
// void swap(int &a, int &b);
//
// int main() {
// int a = 10, b = 20;
//
// std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
// swap(a, b);
// std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
// }
//
// void swap(int &a, int &b) { //pass by reference not value &a and &b are the addresses of a and b
// int temp = a;
// a = b;
// b = temp;
// }


#include <iostream>
void swap(int *a, int *b);

int main() {
int a = 10, b = 20;

std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
swap(&a, &b);
std::cout << "After swap: a = " << a << ", b = " << b << std::endl; }

void swap(int *a, int *b) { // pass by pointer
int temp = *a;
*a = *b;
*b = temp; }
