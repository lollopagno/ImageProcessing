#include "include/window.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Window window;

    window.resize(600, 550);
    window.setWindowTitle("Image Processing");
    window.show();

    return app.exec();
}