#include <iostream>

// Implementor Interface
class Renderer {
public:
    virtual void render() = 0;
};

// Concrete Implementor
class OpenGLRenderer : public Renderer {
public:
    void render() override {
        std::cout << "Rendering with OpenGL" << std::endl;
    }
};

// Concrete Implementor
class DirectXRenderer : public Renderer {
public:
    void render() override {
        std::cout << "Rendering with DirectX" << std::endl;
    }
};

// Abstraction
class Shape {
protected:
    Renderer* renderer; // Bridge Interface

public:
    Shape(Renderer* renderer) : renderer(renderer) {}

    virtual void draw() = 0;
};

// Refined Abstraction
class Circle : public Shape {
public:
    Circle(Renderer* renderer) : Shape(renderer) {}

    void draw() override {
        std::cout << "Drawing Circle ";
        renderer->render();
    }
};

// Refined Abstraction
class Square : public Shape {
public:
    Square(Renderer* renderer) : Shape(renderer) {}

    void draw() override {
        std::cout << "Drawing Square ";
        renderer->render();
    }
};

int main() {
    Renderer* openglRenderer = new OpenGLRenderer();
    Renderer* directxRenderer = new DirectXRenderer();

    Shape* circle = new Circle(openglRenderer);
    Shape* square = new Square(directxRenderer);

    circle->draw(); // Drawing Circle Rendering with OpenGL
    square->draw(); // Drawing Square Rendering with DirectX

    delete openglRenderer;
    delete directxRenderer;
    delete circle;
    delete square;

    return 0;
}

// /usr/bin/clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g /Users/liuyicheng/gitProj/the_road_to_cs/C++设计模式/bridge_pattern/code.cpp -o /Users/liuyicheng/gitProj/the_road_to_cs/C++设计模式/bridge_pattern/code
