#include <iostream>

int areaOfTriangle(int w, int h);

int main() {
    std::vector<int> wh = {5,10};

    int area = areaOfTriangle(wh[0], wh[1]);

    printf("hello world\n");
    std::cout << area << std::endl;

    return 0;
}

int areaOfTriangle(int w, int h) {
    return (w * h)/2;
}

