#include "Driver.h"

#include <QApplication>

#include "Assert.h"
#include "Logging.h"
#include "Settings.h"
#include "Window.h"

namespace mms {

int Driver::drive(int argc, char* argv[]) {

    // Make sure that this function is called just once
    ASSERT_RUNS_JUST_ONCE();

    // Initialize Qt
    QApplication app(argc, argv);

    // Initialize singletons
    Logging::init();
    Settings::init();

    // Create the main window
    Window window;
    window.show();

    // Start the event loop
    return app.exec();
}

} 
