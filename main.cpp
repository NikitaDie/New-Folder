#include <iostream>

template<class T>
class Point
{
private:
    T x;
    T y;

public:
    Point(const T& new_x, const T& new_y) : 
        x{new_x}, 
        y{new_y}
{}

    Point(const Point& obj) = default;

    void setX(const T& new_x){
        x = new_x;
    }

    void setY(const T& new_y){
        y = new_y;
    }

    const T& getX() const{
        return x;
    }

    const T& getY() const{
        return y;
    }

    template<typename S>
    friend std::ostream& operator<<(std::ostream& out, const Point<S>& p);

    template<typename S>
    friend std::istream& operator>>(std::istream& in, Point<S>& p);
};

template<typename S>
std::ostream& operator<<(std::ostream& out, const Point<S>& p)
{
    out << "(" << p.x << "; " << p.y << ")";

    return out;
}

template<typename S>
std::istream& operator>>(std::istream& in, Point<S>& p)
{
    in >> p.x;
    in >> p.y;

    return in;
}


template<class T>
class Polygon
{
private:
    Point<T>** arr{nullptr};
    int count{0};

    void clearMemory(){

        if(arr != nullptr){

            for (int i{}; i < count; ++i){
                delete arr[i];
            }

            delete[] arr;
        }
    }

public:

    Polygon(Point<T>** arr, int count) :
        arr{new Point<T>*[count]},
        count{count}
    {
        for (int i{}; i < count; ++i)
        {
            this->arr[i] = arr[i];
        }
    }

    Polygon(const std::initializer_list<Point<T>*>& list) :
        arr{new Point<T>*[list.size()]},
        count{static_cast<int>(list.size())}
    {
        int id{};
        for(Point<T>* item : list){
            this->arr[id++] = item;
        }
    }

    Polygon(const Polygon& other) :
        arr{new Point<T>*[other.count]},
        count{other.count}
    {
        for (int i{}; i < count; ++i)
        {
            this->arr[i] = other.arr[i];
        }
    }

    Polygon(Polygon&& other) :
        arr{other.arr},
        count{other.count}
    {
        other.arr = nullptr;
    }
    
    Polygon& operator=(const Polygon& other){

        if(this == &other)
            return *this;

        this->count = other.count;

        if(this->arr != nullptr){
            clearMemory();
        }
        
        for (int i{}; i < count; ++i)
        {
            this->arr[i] = other.arr[i];
        }

        return *this;
    }

    Polygon& operator=(Polygon&& other){

        if(this == &other)
            return *this;

        this->count = other.count;
        this->arr = other.arr;

        other.arr = nullptr;

        return *this;
    }


    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Polygon<U>& p);

    ~Polygon()
    {

        clearMemory();
    }
};


template<typename U>
std::ostream& operator<<(std::ostream& out, const Polygon<U>& p)
{
    for(int i{}; i < p.count; ++i){
        out << *p.arr[i] << " ";
    }

    out << std::endl;

    return out;
}


int main() {

    const int COUNT = 10;

    Point<int>* arr[COUNT];

    for (int i{0}; i < COUNT; ++i){
        arr[i] = new Point<int>{i, i+1};
    }

    Polygon<int> a{arr, COUNT};

    std::cout << a << std::endl;

    Polygon<double> p{new Point<double>{1, 2.3}, new Point<double>{1, 3.3}};

    std::cout << p;

    return 0;
}