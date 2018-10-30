#include <initializer_list>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;


class Vector                 
{
  public:
    Vector(void);
    Vector(const unsigned int);
    Vector(const Vector &copycat);            // copy contructor
    Vector &operator=(const Vector &copycat); // copy assignment
    void Push_back(int element);
    size_t Size();
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
/*    if (copycat.mem_p == NULL || copycat.elements_n == 0) {
        cout << "Trying to copy from uninitialized vector\n";
        return;
    }
*/
}


void Vector::Push_back(int element)
{
    if ((elements_real - elements_user) < 1) {
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


void Vector::Print_all(void)
{
    for (int i = 0; i < elements_real; i++) {
        cout << "Element " << i << ": " << mem_p[i] << "\n";
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
    cout << "\nInitializing vector(3)...\n";
    Vector bla(3);
    cout << "Vector's size is: " << bla.Size() << "\n";

    cout << "\nPushing 1,2,3,4,5 to vector...\n";
    bla.Push_back(1);
    bla.Push_back(2);
    bla.Push_back(3);
    bla.Push_back(4);
    bla.Push_back(5);
    cout << "Vector size is: " << bla.Size() << "\n";
    cout << "Priting all the elements of vector, hidden ones included...\n";
    bla.Print_all();

    bla.Push_back(5);
    bla.Push_back(5);
    bla.Push_back(5);
    bla.Push_back(5);
    bla.Print_all();

    cout << "\nInitializing new vector with copy contructor.\n";
    Vector bla2=bla;
    cout << "New vector's size is: " << bla2.Size() << "\n";
    cout << "Printing all elements of new vector...\n";
    bla2.Print_all();

    return 0;
}
