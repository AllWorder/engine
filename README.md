# Краткое руководсво пользователя
## Основная информация
Наш движок поддерживает физику с произвольными выпуклыми многоугольниками и кругами, статичные анимации, пользовательские скрипты и пользовательскую физику.
Программа использует SingleTon, учтите это.
* Для компиляции используйте комманду:
```
g++ test.cpp CustomScripts.cpp DataStorage.cpp GraphicManager.cpp Renderer.cpp ScriptController.cpp Singleton.cpp Collider.cpp PhysController.cpp Animator.cpp -o test -lsfml-graphics -lsfml-window -lsfml-system

```
* для запуска же:
```
./test
```
* после первой компиляции можно будет перекомпилировать только изменённые cpp
## Структура программы
Пользователю для работы необходимо работать лишь с несколькими разделами программы:
* **test.cpp**, где происходит создание всех объектов в начале игры и собственно основной цикл game.run()
* **CustomScripts.hpp** и **CustomScripts.cpp**, где пользователь описывает собственные скрипты и их реализацию
* **PhysicScripts.hpp** , где описывается физика
## API, инструкция по применению
В нашей программе есть API для более удобного написания программы, пройдёмся по основным коммандам:
### void createObject(std::string name)
создаёт объект с заданным именем
* два объекта не могут иметь одно и то же имя! Останется только первый
* можно вызывать и при написании своих скриптов
### void deleteObject(std::string name)
удаляет объект с заданным именем
### GameObject* getObject(std::string name)
возвращает указатель на объект
###std::vector<Collider*> getAllCollisions(sing)
возвращает массив указателей на Collider столкнувшихся в данный момент объектов. Полезно для привязки логики при ударе. Состоит из пар объектов: нулевой столкнулся с первым, второй с третьим и т. д. Каждая пара входит в массив 2 раза с изменённым порядком следования (a столкнулся с b, и b столкнулся с a).
```
//пример применения:
 API::createObject("player");
 API::deleteObject("player");
// по указателю монжо обращаться и к методам или переменным объекта: 
 API::getObject("obj1") -> x = 500;
 API::getObject("obj1") -> y = 360;
```
## Об компонентах:
В нашей программе добавление функциональности объектам происходит через добавление соответсвующих компонент:
* **Renderer** отвечает за отрисовку, текстуры
* **Collider** отвечает за столкновения и хитбокс(набор вершин многоугольника), хранит скорость
* **Animation** отвечает за статические анимации и хранение массива текстур для анимации
* **PhysScript name** отвечают за физическое поведение, их вы можете писать спокойно сами, например:
* **VelocityPhysic** отвечает за обработку скоростей, требует Collider
* **GravitationPhysic** за графитацию
* **BWCollided name** отвечают за поведение при столкновениях, есть базовые готовые, но ничего не мешает вам написать свои. Из готовых:
* **BWCollided_player** все объекты с такой компонентой упруго или неупруго сталкиваются
* **BWCollided_wall** прописывается для стен и барьеров

## Базовая работа с компонентами
### addComponent<Т>(sing)
* Добавляет игровому объекту компоненту класса Т
* Две одинаковых компоненты иметь нельзя
* (sing) просто техничекая хрень
```
// пример добавления различных компонент:
 API::getObject("obj1") -> addComponent<Renderer>(sing);
 API::getObject("wall1") -> addComponent<Collider>(sing);
 API::getObject("spawner") -> addComponent<MonsterSpawner>(sing);
// в данном случае MonsterSpawner просто скрипт по спавну монстров, написанный самостоятельно пользователем 
 ```
 ### deleteComponent<Т>(sing)
* удаляет у игрового объекта компоненту класса Т
### Component* getComponent<Т>(sing)
* Возвращает указатель на компоненту, чтобы монжо было использовать переменные и методы компоненты
```
  API::getObject("obj1") -> getComponent<Renderer>() -> loadTexture("resources/opexus.png");
  API::getObject("obj1") -> getComponent<Renderer>() -> setSize(100, 100);
```
# Далее поговорим подробно о GameObject и всех базовых компонентах:


## GameObject
* хранит в себе координаты float **x, y** (центр объекта, если есть размер)
* имеет имя std::string **name**, его-то мы и задавали при создании
* хранит приватный вектор компонент


## Renderer
* хранит текстуру **sf::Texture texture**, её можно загрузить и сразу применить при помощи:
* void **loadTexture(std::string imagePath)**, где imagePath - путь до картинки
```
API::getObject("obj1") -> getComponent<Renderer>() -> loadTexture("resources/opexus.png");
лучше хранить все текстуры в специальной папке resources
```
* void **setTexture(sf::Texture* newTexture)**, меняет текстуру по указателю newTexture
* Renderer хранит размеры текстур int **xSize, ySize**
* void **setSize(int xLen, int yLen)**, задаёт размеры текстуры
```
API::getObject("obj1") -> getComponent<Renderer>() -> setSize(100, 100);
теперь на объект натянута картинка 100 на 100
```
* int **layer**, отвечает за слой. По умолчанию 1. Слои от 0 до 10. Слои с меньшим числом перекрывают слои с большим.
```
API::getObject("background") -> getComponent<Renderer>() -> layer = 3;
увели фон на задний слой, чтобы он не перекрывал игрока с layer = 1
```
* bool **isVisible** отвечает за то, будет ли объект отрисовываться или нет

## Collider
```
  class Shape
  {
    bool ifCollideable = true; будет ли объект сталкиваться с другими
    bool ifMoveable = true; будет ли обрабатываться движение объекта
    bool ifElastic = true; для ударов. Упругий или неупругий
    bool ifCircle = false; true заставит его вести себя физически как круг с радиусом r
    float mass = 10; масса для рассталкивания по импульсу
    float r = 1;
    std::vector<float> velocityS = {0, 0}; вектор скоростей
    std::vector<std::vector <float>> vertex; вектор вершин, образающий замкнутый многоугольник
  }
 ```
 * **void addVertex(float x, float y)** добавляет вершину в локальных координатых, где центр имеет координаты (0, 0)
 ```
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(-50, -50);
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(50, -50);
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(50, 50);
    API::getObject("obj2") -> getComponent<Collider>() -> shape.addVertex(-50, 50);
    по факту задали вершины квадрата размером 100 на 100 в локульных координатах
 ```
 * **НЕ ПУГАЙТЕСЬ, если не поняли предыдущий пункт, есть метод попроще для прямоугольников**
 * void **setSquareVertexes(std::string name, int xSize, int ySize)** делает прямоугольных хитбокс объекту с именем name.
 ```
 API::setSquareVertexes("obj2", 100, 100);
 
 по факту это эквивалентно тому, что в примере выше, но проще и короче
 однако данная функция только для прямоугольников (кому-то от жизни надо больше!?)
 для произвольных замкнутых многоугольников используйте ручное задание вершин в локальных координатах
 ```
 * void **setVelocity(float vx, float vy)**, задаёт скорость объекту
 ```
 API::getObject("obj2") -> getComponent<Collider>() -> shape.setVelocity(5, 0);
 ```
 * bool **checkCrossingBetweenPreviousTics(Collider* source, Collider* obj2)**, помогает узнать, столкнулись ли быстро движущиеся объекты, например, пуля и игрок, или маленькие объекты (расстояние пролёта между тиками больше размера объекта).
  ```
 Collider* collider1 = API::getObject("obj1") -> getComponent<Collider>();
 Collider* collider2 = API::getObject("obj2") -> getComponent<Collider>();
 collider1 -> checkCrossingBetweenPreviousTics(collider1, collider2);   // true/false
 ```
 Стоит заметить, что функция работает корректно, если рассматривается столкновение быстрого объекта с медленным. Единица времени (dT)=1, так что если планируете использовать эту функцию в программе примите шаг времени равным единице.
 
 * замечание про удары: все объекты имеющие коллайдер и с пометками ifCollideable = true у обоих, будут расталкиваться упруго, если они оба упругие, неупруго, если хотя бы один из них неупругий, и если хотя бы у одного проставлено ifMoveable = true.
Если ifMoveable = false, то это соответствует объекту с бесконечной массой. Два объекта с бесконечными массами удару не подвергаются. Некоторые методы принадлежат структуре shape в Collider, так что будьте аккуратны. 
 
 
 ## Animator
* int **ticksPerAnimation** = 30, количество тиков для смены анимации на другую
* void **addTexture(std::string texturePath)** добавление тектуры в массив текстур для анимаций по пути до файла texturePath
* void **deleteTexture(std::string texturePath)** удаление
```
    API::getObject("bumbleBee") -> addComponent<Animation>(sing);
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb1.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb2.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> addTexture("resources/bb3.png");
    API::getObject("bumbleBee") -> getComponent<Animation>() -> ticksPerAnimation = 10;
    
    задаём шмелёнку анимацию
```
* важно, чтобы все картинки в аниматоре имели одинаковый размер, например 50x50 пикселей, иначе SFML чудит


## CustomScripts, создание 
* для создания своего скрипта пропишите его описание в **CustomScripts.hpp**
```
class PlayerController: public Script // ОБЯЗАТЕЛЬНО НАСЛЕДОВАНИЕ ОТ SCRIPT!
{
  public:

  PlayerController()
  {
    this->name = typeid(PlayerController).name(); // ОБЯЗАТЕЛЬНО ЭТА СТРОЧКА, вместо PlayerController имя вашего класса
  }

  void execute(Singleton* sing); // его пропишем в cpp

};
```
* описание **execute()** у нас принято писать в **CustomScripts.cpp**
```
void PlayerController::execute(Singleton* sing)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        objPointer -> getComponent<Collider>() -> shape.velocityS[1] -= 0.5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        objPointer -> getComponent<Collider>() -> shape.velocityS[1] += 0.5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        objPointer -> getComponent<Collider>() -> shape.velocityS[0] -= 0.5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        objPointer -> getComponent<Collider>() -> shape.velocityS[0] += 0.5;

}

КАЖДАЯ КОМПОНЕНТА СОДЕРЖИТ УКАЗАТЕЛЬ НА ОБЪЕКТ, К КОТОРОМУ ОНА ПРИВЯЗАНА objPointer!
данный скрипт тупо меняет скорости при нажатии клавиш
здесь можно использовать и API'шные функции тоже
```
* так же, как и остальные компоненты скрипты можно добавлять игровым объектам:
```
API::getObject("player") -> addComponent<PlayerController>(sing);
```

## PhysicScripts, создание
* здесь всё очень похоже на обычные скрипты только всё происходит в **PhysicScripts.hpp**
* cpp по умолчанию нет, но вы его можете добавить сами
```
class GravitationPhysic: public PhysicScript // ОБЯЗАТЕЛЬНО НАСЛЕДОВАНИЕ ОТ PhysicScript 
{
    public:

        GravitationPhysic()
        {
            this->name = typeid(GravitationPhysic).name(); // ЭТО ОЧЕНЬ ВАЖНЫЙ МОМЕНТ, замените GravitationPhysic на имя своего класса
        }

        void executePhysic(Singleton* sing)
        {
            if(objPointer ->getComponent<Collider>())
            {
                objPointer -> getComponent<Collider>() -> shape.velocityS[1] += g;
            }
        }
};
```
* можно их так же добавлять объектам
```
API::getObject("player") -> addComponent<GravitationPhysic>(sing);
```
# Сохранения

## Запись сохранения
Для того чтобы сохраниться, то есть сохранить состояние всех объектов, их компонентов и таймера, нужно просто вызвать функцию:
```
API::saveGame("mySaving");
```
при этом в папке Savings создастся или перезапишется файл с именем "mySaving.txt".

## Считывание сохранения
Если Вы хотите считать сохранение, то вызовите функцию:
```
API::readGame("mySaving");
```
При этом ВСЕ игровые объекты заменятся на считанные из файла "Savings/mySaving.txt". Все объекты до считывания будут безвозвратно потеряны, так что рекоммендуем их сохранить перед считыванием предыдущей функцией, если они ещё понадобятся.
Стоит обратить внимание на считывание компонент Script. Так как пользователь сам пишет скрипты в файле CustomScripts.cpp, то при написании нового скрипта необходимо дописать функцию initScript следующим образом:
```
if (name == typeid(CustomScriptClass).name())
    data -> getObject(object) -> addComponent<CustomScriptClass>(sing);
```
CustomScriptClass - Ваш новый класс. Если Вы не допишите эту функцию, то при считывании эта компонента не добавится к игровому объекту.

# Выводы
* пример и демку смотрите в test.cpp, там достаточно интуитивно понятно
* если есть вопросы, вы знаете, что нам можно написать




 
