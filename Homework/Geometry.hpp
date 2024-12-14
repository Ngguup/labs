#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

template<typename T>
using Matrix = std::vector<std::vector<T>>;

class Point {
    int x, y;
    public:
        void set(int x, int y) {
            this -> x = x;
            this -> y = y;
        }

        Point() {x = -1; y = -1;};
        Point(int x, int y) {
            this -> set(x, y);
        }

        int getX() {return x;}
        int getY() {return y;}
        std::vector<int> get() {return {x, y};}
        void fill(int &x, int &y) {
            x = this -> x;
            y = this -> y;
        }

        bool is_none() {
            if ((x == -1) && (y == -1)) return true;
            return false;
        }

        bool operator ==(Point p) {return (x == p.x) && (y == p.y);}
        bool operator ==(std::vector<int> v) {return (x == v[0]) && (y == v[1]);}
        bool operator <(const Point &p) const {return (x + y) < (p.x + p.y);}

        bool operator !=(Point p) {return (x != p.x) || (y != p.y);}
        Point operator +(Point& p) {return Point(x + p.x, y + p.y);}
        Point operator -(Point& p) {return Point(x - p.x, y - p.y);}

        //Point& operator =(const Point &p) {return *this;}
        void operator =(Point p) {this -> set(p.x, p.y);}
};

int read(const char* file_name, int **&arr);
void print(int** arr);

double Distance(Point p1, Point p2);
int F(Point p, Point p1, Point p2);
std::vector<Point> draw_line(Point p1, Point p2);

//std::vector<Point> short_path(int field [M][N], Point start, Point finish);
int short_path(int **field, Matrix<bool> &used, Matrix<Point> &paths, Point start, Point finish);
std::vector<Point> make_path(Matrix<Point> &paths, Point p1, Point p2);
void make_way_matrix(int** field, Matrix<bool> &used, Matrix<Point> &paths, Matrix<int> &dist, Point pos, int points = (N * M));

std::vector<Point> make_circle(Point O, int R);
std::vector<Point> make_circle2(Point O, int R);
std::vector<Point> remove(const std::vector<Point> &v1);

#endif