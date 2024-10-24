# Классы данных
class Computer:
    def __init__(self, id, name, price, os_id):
        self.id = id
        self.name = name
        self.price = price
        self.os_id = os_id

class OperatingSystem:
    def __init__(self, id, name):
        self.id = id
        self.name = name

class ComputerOSRelation:
    def __init__(self, computer_id, os_id):
        self.computer_id = computer_id
        self.os_id = os_id

# Тестовые данные
computers = [
    Computer(1, "Lenovo ThinkPad", 800, 1),
    Computer(2, "HP EliteBook", 1200, 2),
    Computer(3, "Dell Inspiron", 900, 1),
    Computer(4, "Asus ZenBook", 1000, 3),
    Computer(5, "Acer Predator", 1500, 2)
]

operating_systems = [
    OperatingSystem(1, "Windows 10"),
    OperatingSystem(2, "Linux Ubuntu"),
    OperatingSystem(3, "macOS")
]

computer_os_relations = [
    ComputerOSRelation(1, 1),
    ComputerOSRelation(2, 2),
    ComputerOSRelation(3, 1),
    ComputerOSRelation(4, 3),
    ComputerOSRelation(5, 2)
]

# 1. Вывести список всех компьютеров, у которых название заканчивается на "book", и названия их ОС.
print("Запрос 1: Компьютеры, название которых заканчивается на 'Book', и их операционные системы:")
result_1 = [
    (comp.name, os.name)
    for comp in computers
    for os in operating_systems
    if comp.name.endswith("Book") and comp.os_id == os.id
]
for name, os_name in result_1:
    print(f"Компьютер: {name}, ОС: {os_name}")

# 2. Вывести список операционных систем со средней стоимостью компьютеров, на которых они установлены, отсортированный по средней цене.
print("\nЗапрос 2: Операционные системы и средняя стоимость компьютеров:")
os_avg_price = {}
for os in operating_systems:
    comp_prices = [comp.price for comp in computers if comp.os_id == os.id]
    if comp_prices:
        avg_price = sum(comp_prices) / len(comp_prices)
        os_avg_price[os.name] = avg_price

sorted_os_avg_price = sorted(os_avg_price.items(), key=lambda x: x[1])
for os_name, avg_price in sorted_os_avg_price:
    print(f"ОС: {os_name}, Средняя стоимость: {avg_price}")

# 3. Вывести список всех ОС, у которых название начинается с буквы "L", и список компьютеров, на которых они установлены.
print("\nЗапрос 3: ОС, название которых начинается с буквы 'L', и компьютеры с этими ОС:")
result_3 = [
    (os.name, [comp.name for comp in computers if comp.os_id == os.id])
    for os in operating_systems
    if os.name.startswith("L")
]
for os_name, comp_list in result_3:
    print(f"ОС: {os_name}, Компьютеры: {', '.join(comp_list)}")
