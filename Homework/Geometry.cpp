#include "Main.hpp"

int read(const char* file_name, int **&arr) {
    std::ifstream fin(file_name, std::ios::in);
    if (!fin) {
        std::cout << "Heт файла " << file_name << std::endl;
        return -1;
    }

    arr = new int* [M];

    for (int i = 0; i < M; i++) {
        arr[i] = new int [N];
        for (int j = 0; j < N; j++) {
            fin >> arr[i][j];
        }
    }

    fin.close();
    return 0;
}

void print(int** arr) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int F(Point p, Point p1, Point p2) {
    p1 = p1 - p;
    p2 = p2 - p;

    int xy1 = abs(p1.getX() * p2.getY());
    int xy2 = abs(p2.getX() * p1.getY());

    return abs(xy1 - xy2);
}


double Distance(Point p1, Point p2) {
    int x1, y1, x2, y2;
    p1.fill(x1, y1);
    p2.fill(x2, y2);
    return pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
}


std::vector<Point> draw_line(Point p1, Point p2) {
    std::vector<Point> path;
    path.push_back(p1);

    Point pk1{0, 0}, pk2{0, 0};
    int dx = p2.getX() - p1.getX();
    int dy = p2.getY() - p1.getY();

    if (dx != 0) pk1.set(dx / abs(dx), 0);
    if (dy != 0) pk2.set(0, dy / abs(dy));

    if (!dx || !dy) {
        while (p1 != p2) {
            p1 = p1 + pk1 + pk2;
            path.push_back(p1);
        }
    } else {
        Point p = p1;
        while (p != p2) {
            p = p + (F(p1, p2, p + pk1) < F(p1, p2, p + pk2) ? pk1 : pk2);
            path.push_back(p);
        }
    }
    return path;
}

int short_path(int **field, Matrix<bool> &used, Matrix<Point> &paths, Point start, Point finish) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) used[j][i] = false;
    }

    Point to;
    std::queue<Point> q;

    used[start.getY()][start.getX()] = true;
    q.push(start);


    int X, Y, x, y;
    while (!q.empty()) {
	        Point v = q.front();
	        q.pop();
            X = v.getX(); Y = v.getY();
	        for (int i = 0; i < 4; ++i) {
                switch (i)
                {
                case 0:
                    x = X + 1; y = Y;
                    break;
                case 1:
                    x = X - 1; y = Y;
                    break;
                case 2:
                    x = X; y = Y + 1;
                    break;
                case 3:
                    x = X; y = Y - 1;
                    break;
                }

                if ((x < 0 || x >= N) || (y < 0 || y >= M) || (field[y][x] != 0)) continue;

                to.set(x, y);
                if (to == finish) {
                    paths[y][x] = v;
                    return 0;
                }

		        if (!used[y][x]) {
			        used[y][x] = true;
			        q.push (to);
			        paths[y][x].set(X, Y);
		        }
	        }
    }
    
    //std::cout << "no such way" << std::endl;
    return -1;
}


void make_way_matrix(int** field, Matrix<bool> &used, Matrix<Point> &paths, Matrix<int> &dist, Point pos, int points) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            used[j][i] = false;
            dist[j][i] = -1;
        };
    }

    Point to;
    std::queue<Point> q;

    used[pos.getY()][pos.getX()] = true;
    dist[pos.getY()][pos.getX()] = 0;

    q.push(pos);


    int X, Y, x, y;
    while (!q.empty()) {
	        Point v = q.front();
	        q.pop();

            X = v.getX(); Y = v.getY();
            if (dist[Y][X] == points) continue;

	        for (int i = 0; i < 4; ++i) {
                switch (i)
                {
                case 0:
                    x = X + 1; y = Y;
                    break;
                case 1:
                    x = X - 1; y = Y;
                    break;
                case 2:
                    x = X; y = Y + 1;
                    break;
                case 3:
                    x = X; y = Y - 1;
                    break;
                }

                if ((x < 0 || x >= N) || (y < 0 || y >= M) || (field[y][x] != 0)) continue;

                to.set(x, y);

		        if (!used[y][x]) {
			        used[y][x] = true;
			        q.push (to);
			        paths[y][x].set(X, Y);
                    dist[y][x] = dist[Y][X] + 1;
		        }
	        }
    }

    return;
}


std::vector<Point> make_path(Matrix<Point> &paths, Point p1, Point p2) {
    std::vector<Point> path;
    while (!p2.is_none()) {
        if (p1 == p2) {
            std::reverse(path.begin(), path.end());
            return path;
        }

        path.push_back(p2);
        p2 = paths[p2.getY()][p2.getX()];
    }
    return {};
}

std::vector<Point> make_circle(Point O, int R) {
    std::vector<Point> circle (4 * R);
    int k[4][2] = {{1, 1}, {-1, 1}, {-1 , -1}, {1, -1}};

    const int cx = O.getX(), cy = O.getY();
    int x, y;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < R; j++) {
            x = j * k[i][0];
            y = (R - j) * k[i][1];

            if (i % 2 == 1) std::swap(x, y);
            x += cx; y += cy;
            circle[i * R + j].set(x, y);
        }
    }

    return remove(circle);
}

std::vector<Point> make_circle2(Point O, int R) {
    std::vector<Point> circle;
    const int cx = O.getX(), cy = O.getY();

    int x = 0, y = R;
    int r, r1, r2, r3;
    R *= R;

    while (y > 0) {
        r = x * x + y * y;
        r1 = r + 2 * x + 1;
        r2 = r + 2 * x - 2 * y + 2;
        r3 = r - 2 * y + 1;

        if (r1 <= R) {x++; r = r1;}
        else if (r2 <= R) {x++; y--; r = r2;}
        else {y--; r = r3;}

        circle.push_back({cx + x, cy + y});
        circle.push_back({cx + y, cy - x});
        circle.push_back({cx - x, cy - y});
        circle.push_back({cx - y, cy + x});
    }

    return remove(circle);
}

std::vector<Point> remove(const std::vector<Point> &v1) {
    std::vector<Point> v2;
    int x, y;

    for (Point p : v1) {
        x = p.getX(); y = p.getY();
        if (p.is_none() || (x < 0 || x >= N) || (y < 0 || y >= M)) continue;
        v2.push_back(p);
    }

    return v2;
}





/*
double H(Point p, Point p1, Point p2) {
    p1 = p1 - p;
    p2 = p2 - p;

    int x1 = abs(p1.getX()), y1 = abs(p1.getY());
    int x2 = abs(p2.getX()), y2 = abs(p2.getY());

    double pol1, pol2, pol3;
    pol1 = pow(x1, 2) + pow(y1, 2);
    pol2 = pow(x2, 2) + pow(y2, 2);
    pol3 = x1 * x2 + y1 * y2;

    if (!pol1) return pol2;

    return pow(pol2 - pow(pol3, 2) / pol1, 0.5);
}
*/