#[derive(Debug, Copy, Clone)]
struct Point {
    x: i32,
    y: i32,
}

//Реализация макроса для перегрузки операторов +-*/
macro_rules! override_op {
    ($tr:ident, $func:ident) => (
        impl std::ops::$tr for Point {
            type Output = Self;
            fn $func(self, _rhs: Self) -> Self {
                let _x = std::ops::$tr::$func(self.x, _rhs.x);
                let _y = std::ops::$tr::$func(self.y, _rhs.y);
                Self {x: _x, y: _y}
            }
        }
    )
}


//Реализация макроса, который применякт override_op для произвольного количествы аргументов
macro_rules! override_ops {
    ($tr:ident, $func:ident) => (
        override_op!($tr, $func);
    );

    ($tr:ident, $func:ident, $($coms:ident),+) => (
        override_op!($tr, $func);
        override_ops!($($coms),+);
    )
}

override_ops!(Add, add, Sub, sub, Mul, mul, Div, div);


fn main() {
    let p1 = Point{x: 10, y: 15};
    let p2 = Point{x: 5, y: 3};
    let points: [Point; 4] = [p1 + p2, p1 - p2, p1 * p2, p1 / p2];

    //Выводим результат применения операций +-*/ над точками p1, p2
    for p in points.iter() {
        println!("{:?}", p);
    }
}



