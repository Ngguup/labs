fn main() {
    let numbers = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

    //Используем итератор и фильтр, чтобы выбрать только чётные числа
    let even_numbers: Vec<i32> = numbers
        .iter() 
        .filter(|&x| x % 2 == 0) 
        .cloned() 
        .collect(); 

    println!("Чётные числа: {:?}", even_numbers);

    //Используем map для преобразования чисел: возводим каждое в квадрат
    let squared_numbers: Vec<i32> = numbers
        .iter()
        .map(|x| x * x) 
        .collect();

    println!("Квадраты чисел: {:?}", squared_numbers);

    //Реализация функции с каррированием
    let multiply_by = |factor: i32| move |x: i32| x * factor;

    //Создаём функции, которые умножают на 2 и на 3
    let multiply_by_2 = multiply_by(2);
    let multiply_by_3 = multiply_by(3);

    let doubled_numbers: Vec<i32> = numbers.iter().map(|&x| multiply_by_2(x)).collect();
    let tripled_numbers: Vec<i32> = numbers.iter().map(|&x| multiply_by_3(x)).collect();

    println!("Числа, умноженные на 2: {:?}", doubled_numbers);
    println!("Числа, умноженные на 3: {:?}", tripled_numbers);

    //Используем reduce для суммирования всех чисел
    let sum: i32 = numbers.iter().copied().reduce(|acc, x| acc + x).unwrap_or(0);

    println!("Сумма чисел: {}", sum);
}
