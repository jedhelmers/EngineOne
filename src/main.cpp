#include "Application.hpp"

int main() {
    // Create the application (or "Engine") object
    Application app;

    // Initialize (create window, init GLAD, etc.)
    if (!app.init()) {
        return -1;
    }

    // Run the main loop
    app.run();

    // Cleanup and exit
    return 0;
}
