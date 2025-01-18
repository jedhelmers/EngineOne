#pragma once

#include "Graphics.hpp"
#include "Entity.hpp"


class Application {
public:
    // Constructor / Destructor
    Application();
    ~Application();

    // Initialize all resources (returns false if something fails)
    bool init();

    // The main loop: keep running until the user closes the window
    void run();

private:
    // You might store your GLFWwindow* here
    struct GLFWwindow* m_window;
    std::unique_ptr<Graphics> m_graphics;

    // Store my entities
    std::vector<Entity> m_scene;

    // Private methods
    void processEvents();
    void update();
    void render();
};
