use std::fmt;

// Трейт для вычисления площади фигуры
trait Shape {
    fn area(&self) -> f64;
}

// Трейт для печати информации о фигуре
trait IPrint {
    fn print(&self);
}

// Структура Прямоугольник
struct Rectangle {
    width: f64,
    height: f64,
}

impl Rectangle {
    fn new(width: f64, height: f64) -> Rectangle {
        Rectangle { width, height }
    }
}

// Реализация трейта Shape для прямоугольника
impl Shape for Rectangle {
    fn area(&self) -> f64 {
        self.width * self.height
    }
}

// Реализация трейта ToString для прямоугольника
impl fmt::Display for Rectangle {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Rectangle: width = {}, height = {}, area = {}", self.width, self.height, self.area())
    }
}

// Реализация трейта IPrint для прямоугольника
impl IPrint for Rectangle {
    fn print(&self) {
        println!("{}", self);
    }
}

// Структура Квадрат
struct Square {
    side: f64,
}

impl Square {
    fn new(side: f64) -> Square {
        Square { side }
    }
}

// Реализация трейта Shape для квадрата
impl Shape for Square {
    fn area(&self) -> f64 {
        self.side * self.side
    }
}

// Реализация трейта ToString для квадрата
impl fmt::Display for Square {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Square: side = {}, area = {}", self.side, self.area())
    }
}

// Реализация трейта IPrint для квадрата
impl IPrint for Square {
    fn print(&self) {
        println!("{}", self);
    }
}

// Структура Круг
struct Circle {
    radius: f64,
}

impl Circle {
    fn new(radius: f64) -> Circle {
        Circle { radius }
    }
}

// Реализация трейта Shape для круга
impl Shape for Circle {
    fn area(&self) -> f64 {
        std::f64::consts::PI * self.radius * self.radius
    }
}

// Реализация трейта ToString для круга
impl fmt::Display for Circle {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "Circle: radius = {}, area = {}",
            self.radius,
            self.area()
        )
    }
}

// Реализация трейта IPrint для круга
impl IPrint for Circle {
    fn print(&self) {
        println!("{}", self);
    }
}

/// Реализация супертрейта для объединения всех трёх трейтов
trait Figure: Shape + IPrint + fmt::Display {}
impl Figure for Rectangle {}
impl Figure for Square {}
impl Figure for Circle {}

/// Функция, применяющая все методы трейта Figure
fn print_figures(figures: &[&dyn Figure]) {
    for f in figures.iter() {
        println!("{}", f.to_string());
        f.print();

        println!("Area: {}", f.area());
        println!();
    }
}


fn main() {
    let rect = Rectangle::new(3.0, 4.0);
    let square = Square::new(5.0);
    let circle = Circle::new(2.0);

    print_figures(&[&rect, &square, &circle]);
}


