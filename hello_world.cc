#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;


class Vector                 
{
  public:
    Vector(void);
    Vector(const unsigned int);
    Vector(std::initializer_list<int>);
    Vector(const Vector&);            // copy contructor
    Vector &operator=(const Vector&); // copy assignment
    int at_change(unsigned int, unsigned int);
    void Push_back(int);
    size_t Size();
    int at(unsigned int);
    void Print_all(void);
    ~Vector();

 private:
    int *mem_p;
    size_t elements_user;
    size_t elements_real;
};


Vector::Vector()
{
    mem_p = (int *)calloc(20, sizeof(int));
    if (!mem_p) {
        cout << "Failed to allocate memory for vector\n";
        return;
    }

    elements_user = 0;
    elements_real = 20;
}


Vector::Vector(unsigned int user_size)
{
    if (user_size == 0) {
        mem_p = (int *)calloc(20, sizeof(int));
        if (!mem_p) {
            cout << "Failed to allocate memory for vector\n";
            return;
        }

        elements_user = 0;
        elements_real = 20;
        return;
    }

    mem_p = (int *)calloc(user_size, sizeof(int));
    if (mem_p == NULL) {
        cout << "Failed to allocate " << user_size << " elements\n";
        return;
    }

    elements_real = user_size;
    elements_user = 0;
}


Vector::Vector(std::initializer_list<int> elements)
{
    const int *it;
    int j = 0;
    elements_user = 0;

    if (elements.size() < 20) {
        mem_p = (int *)calloc(20, sizeof(int));
        elements_real = 20;
    } else {
        mem_p = (int *)calloc(elements.size(), sizeof(int));
        elements_real = elements.size();
    }

    for (it = elements.begin(); it != elements.end(); it++) {
        *(mem_p + j) = *it;
        elements_user++;
        j++;
    }
}


Vector::Vector(const Vector &copycat)
{
    if (copycat.mem_p == NULL) {
        cout << "Trying to copy from or to uninitialized vector\n";
        return;
    }

    if (copycat.elements_user <= 0) {
        cout << "No elements to copy\n";
        /* Continue anyways, allocate at least 20 bytes and zero them out*/
    }

    mem_p = (int *)calloc(copycat.elements_real, sizeof(int));
    if (mem_p == NULL) {
        cout << "Failed to allocate memory for new vector\n";
        return;
    }
    elements_real = copycat.elements_real;

    for (int i = 0; i < copycat.elements_user; i++) {
        mem_p[i] = copycat.mem_p[i];
    }

    elements_user = copycat.elements_user;
}


Vector &Vector::operator=(const Vector &copycat)
{
    if (this == &copycat) {
        cout << "Trying to copy yourself\n";
        return *this;
    }

    if (elements_real < copycat.elements_user) {
        cout << "Need to reallocate vector, TODO\n";
    }

    for (int i = 0; i < copycat.elements_user; i++) {
        mem_p[i] = copycat.mem_p[i];
    }

    elements_user = copycat.elements_user;

}


void Vector::Push_back(int element)
{
    if ((elements_real - elements_user) < 1) {
        /* Double the size each time we hit the boundary */
        int *new_memp = (int *)realloc(mem_p, elements_real * sizeof(int) * 2);
        if (!new_memp) {
            cout << "Failed to allocate memory for element: " << element << "\n";
            return;
        }

        mem_p = new_memp;
        for (int i = 0; i < elements_real; i++) {
            *(mem_p + elements_real + i) = 0x00;
        }
        elements_real += elements_real;
    }

    mem_p[elements_user] = element;
    elements_user++;
}


size_t Vector::Size()
{
    return elements_user;
}

int Vector::at(unsigned int index)
{
    if (index >= elements_user) {
        throw invalid_argument("Index out of bounds!\n");
    }

    return *(mem_p + index);
}

int Vector::at_change(unsigned int index, unsigned int value)
{
    *(mem_p + index) = value;
}


void Vector::Print_all(void)
{
    for (int i = 0; i < elements_user; i++) {
        cout << "\tElement " << i << ": " << mem_p[i] << "\n";
    }
}


Vector::~Vector()
{
    if (mem_p) {
        free(mem_p);
        mem_p = NULL;
        elements_user = 0;
        elements_real = 0;
    }
}


int main()
{
    cout << "\nInitializing vector(3)\n";
    Vector bla({1,2,3});
    cout << "Vector size is: " << bla.Size() << "\n";

    cout << "\nPushing 4,5 to vector...\n";
    bla.Push_back(4);
    bla.Push_back(5);
    cout << "Vector size is: " << bla.Size() << ", expected 5\n";

    cout << "Trying copy constructor\n";
    Vector bla2 = bla;
    cout << "Copied vector size is " << bla2.Size() << "\n";

    cout << "Trying self assignment...\n";
    bla = bla;

    cout << "Trying copy assignment with default constructor\n";
    Vector bla3;
    bla3 = bla;
    cout << "Vector3 size is " << bla3.Size() << "\n";
    cout << "Vector3 elements are:\n";
    bla3.Print_all();
    cout << "Vector elements are:\n";
    bla.Print_all();

    bla.at_change(1, 13);
    cout << "Vector elements are:\n";
    bla.Print_all();
    cout << "Vector3 elements are:\n";
    bla3.Print_all();

    cout << "Vector2 at 2: " << bla2.at(2) << "\n";
    cout << "Trying to print Vector2 at 32.\n";
    try {
        cout << "Vector2 at 32: " << bla2.at(32) << "\n";
    } catch (const std::invalid_argument& e) {
        cout << "Exception catched: " << e.what();
    }

    return 0;
}
