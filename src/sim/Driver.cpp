#include "Driver.h"

#include <QApplication>
#include <QObject>
#include <QThread>

#include "Directory.h"
#include "FontImage.h"
#include "Logging.h"
#include "MainWindow.h"
#include "Screen.h"
#include "Settings.h"
#include "SimUtilities.h"
#include "State.h"
#include "Time.h"
#include "Model.h"

namespace mms {

int Driver::drive(int argc, char* argv[]) {

    // Make sure that this function is called just once
    ASSERT_RUNS_JUST_ONCE();

    // Initialize Qt
    QApplication app(argc, argv);

    // Initialize the Time object
    Time::init();

    // Initialize the Screen object
    Screen::init();

    // Initiliaze the Logging object
    Logging::init();

    // Initialize the Settings object
    Settings::init();

    // Initialize the Directory object
    Directory::init(app.applicationFilePath());

    // TODO: MACK
    // Initialize the State object in order to:
    // 1) Set the runId
    // 2) Avoid a race condition (between threads)
    // 3) Initialize the Param object
    S()->setRunId(""); // TODO: MACK

    // Initialize the FontImage object
    FontImage::init(
        Directory::get()->getResImgsDirectory() +
        P()->tileTextFontImage());

    // Initialize the model, start the physics loop
    Model::init();
    QThread modelThread;
    QObject::connect(
        &modelThread, &QThread::started,
        Model::get(), &Model::simulate);
    Model::get()->moveToThread(&modelThread);
    modelThread.start();

    // Create the main window
    MainWindow window;
    window.show();

    // Start the event loop
    return app.exec();
}

} // namespace mms
