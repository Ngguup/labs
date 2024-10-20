use std::io;

//Функция для получения числа с клавиатуры
fn take() -> f64 {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    return input.trim().parse().unwrap();
}


//Функция записывает найденные корни в массив и возвращает количество корней
fn get_roots(a: f64, b: f64, c: f64, roots: &mut [f64]) -> i32 {
    let D: f64 = b.powi(2) - 4.0 * a * c;
    if D < 0.0 {return 0;
    } else if D == 0.0 {
        roots[0] = -1.0 * b / (2.0 * a);
        return 1;
    } else {
        roots[0] = (-1.0 * b - D.powf(0.5)) / (2.0 * a);
        roots[1] = (-1.0 * b + D.powf(0.5)) / (2.0 * a);
        return 2;
    };
}

fn main() {
    let a = take();
    let b = take();
    let c = take();
    let mut roots: [f64; 2] = [0.0; 2];

    //Отображение результата
    match get_roots(a, b, c, &mut roots) {
        2 => println!("{}, {}", roots[0], roots[1]),
        1 => println!("{}", roots[0]),
        _ => println!("no roots"),
    }
}
