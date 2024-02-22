#include <fstream>
#include <iostream>

struct Graph // Структура граф
{
private:
    bool** adjacencyMatrix; // Матрица смежности
    bool* visited; // Массив посещенных узлов графа. Для обхода
    int* traversal; // Массив порядка посещенных вершин графа
    int vertices; // Количество вершин
    int currentVertex; // Счетчик для заполнения массива порядка посещенных вершин

    void dfs(int vertex) // Функция для работы метода dfs(). Запуск обхода в графе с вершины vertex и со вспомогательным массивом посещенных вершин.
    {
        visited[vertex] = true; // Помечаем, что посетили вершину
        currentVertex += 1;
        traversal[currentVertex] = vertex + 1; // Заношу вершину в массив порядка посещения
        for (int i = 0; i < vertices; ++i) // Перебираем смежные вершины
        {
            if (adjacencyMatrix[vertex][i] && !visited[i]) // Если существует ребро и вершина еще не посещена
            {
                dfs(i);
            }
        }
    }

public:
    Graph(int vertices) // Конструктор
    {
        this->vertices = vertices;
        adjacencyMatrix = new bool* [vertices]();
        for (int i = 0; i < vertices; ++i)
        {
            adjacencyMatrix[i] = new bool[vertices]();
        }
        visited = new bool[vertices]();
        traversal = new int[vertices]();
        currentVertex = -1;
    }
    void clear() // Очищение памяти.
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
        adjacencyMatrix = nullptr;

        delete[] visited;
        visited = nullptr;

        delete[] traversal;
        traversal = nullptr;
    }

    // Сеттер
    void setVertex(int vertexA, int vertexB, bool edge) // Задание значения элемента матрицы смежности
    {
        adjacencyMatrix[vertexA][vertexB] = edge;
    }

    // Геттеры
    bool getEdge(int vertexA, int vertexB) // Получение элемента матрицы смежности
    {
        return adjacencyMatrix[vertexA][vertexB];
    }

    int getVertices() // Получение количества вершин
    {
        return vertices;
    }

    int getTraversalElement(int index) // Получение элемента матрицы порядка обхода графа
    {
        return traversal[index];
    }

    void dfs() // Обход графа
    {
        for (int i = 0; i < vertices; ++i) // Перебираем вершины графа
        {
            if (!visited[i]) //Если вершину не посетили, то запускаем из нее рекурсивный обход через вспомогательный метод dfs(int vertex)
            {
                dfs(i); //Метод находится в private
            }
        }
    }
};

void fillGraph(Graph& graph, int vertices, std::string file) // Заполнение графа из файла
{
    std::ifstream fin(file);

    int n = 0; // Переменная для считывания информации из файла

    //Пропускаю первое значение (размерность)
    fin >> n;

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            fin >> n;
            graph.setVertex(i, j, static_cast<bool>(n)); //Заполняю матрицу смежности
        }
    }

    fin.close();
}

void printGraph(Graph& graph) // Печать матрицы смежности. Нужна была для сверки. Оставил в коде. Может пригодится.
{
    for (int i = 0; i < graph.getVertices(); ++i)
    {
        for (int j = 0; j < graph.getVertices(); ++j)
        {
            std::cout << graph.getEdge(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void printTraversalGraph(Graph& graph) // Печать порядка обхода графа
{
    for (int i = 0; i < graph.getVertices(); ++i)
    {
        std::cout << graph.getTraversalElement(i) << " ";
    }
}

int main(int argc, char** argv)
{   
    system("chcp 1251");
    std::string file = "input.txt";
    std::ifstream fin(file);

    if (fin.is_open())
    {
        int vertices = 0;// Количество вершин

        //Считываю количество вершин из файла
        fin >> vertices;
        fin.close();

        Graph graph(vertices); // Создаю граф

        fillGraph(graph, vertices, file); //Заполняю его из файла

        std::cout << "Порядок обхода вершин: ";
        graph.dfs(); // Обхожу граф
        printTraversalGraph(graph); // Печатаю порядок обхода

        graph.clear(); // Очищаю память
    }
    else
    {
        std::cout << "Не получилось открыть файл!" << std::endl;
    }

    return 0;
}