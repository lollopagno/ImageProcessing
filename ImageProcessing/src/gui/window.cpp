// Qt
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QDesktopServices>
#include <QLabel>
#include <QSettings>

// Header files
#include "../include/window.h"
#include "../include/imaging.h"

#include <iostream>

using namespace std;

QLabel* imageLabel = NULL;
const char* path = NULL;
Mat _img;

void Window::open() {
    path = QFileDialog::getOpenFileName(this, tr("Select an image"), "/home", tr("Images (*.png, *.jpg)")).toLocal8Bit().data();
    if (path != NULL) {
        _img = Imaging::read(path);
    }
}

void Window::showImage() {
    
    if (path != NULL) {
        cout << "[Img] width: " << _img.size().width << ", Height: "<< _img.size().height << "\n";

        Mat img = Imaging::resize(_img);
        img = Imaging::convertToRGB(img);

        QPixmap convImg = QPixmap::fromImage(QImage((unsigned char*)img.data, img.cols, img.rows, QImage::Format_RGB888));

        imageLabel->setPixmap(convImg);
        update();
    }
}

void Window::convertToGray() {
    
    if (path != NULL) {
        Mat img = Imaging::resize(_img);
        img = Imaging::convertTogray(img);

        QPixmap convImg = QPixmap::fromImage(QImage((unsigned char*)img.data, img.cols, img.rows, QImage::Format_Grayscale8));
        imageLabel->setPixmap(convImg);
        update();
    }
}

void Window::canny() {

    if (path != NULL) {
        Mat img = Imaging::resize(_img);
        img = Imaging::convertTogray(img);
        img = Imaging::blur(img, Size(11, 11));
        img = Imaging::canny(img);

        QPixmap convImg = QPixmap::fromImage(QImage((unsigned char*)img.data, img.cols, img.rows, QImage::Format_Grayscale8));
        imageLabel->setPixmap(convImg);
        update();
    }
}

Window::Window(QWidget* parent) : QMainWindow(parent) {

    // Setting menu
    auto* openAction = new QAction("&Open", this);
    auto* showAction = new QAction("&Show", this);
    auto* grayAction = new QAction("&Grayscale", this);
    auto* cannyAction = new QAction("&Canny", this);
    auto* quitAction = new QAction("&Quit", this);
    openAction->setShortcut(tr("CTRL+T"));
    showAction->setShortcut(tr("CTRL+S"));
    quitAction->setShortcut(tr("CTRL+W"));

    QMenu* fileMenu = menuBar()->addMenu("File");
    QMenu* photoMenu = menuBar()->addMenu("Photo");

    fileMenu->addAction(openAction);
    fileMenu->addAction(quitAction);

    photoMenu->addAction(showAction);
    photoMenu->addSeparator();
    photoMenu->addAction(grayAction);
    photoMenu->addAction(cannyAction);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(showAction, SIGNAL(triggered()), this, SLOT(showImage()));
    connect(grayAction, SIGNAL(triggered()), this, SLOT(convertToGray()));
    connect(cannyAction, SIGNAL(triggered()), this, SLOT(canny()));
    connect(quitAction, &QAction::triggered, this, QApplication::quit);

    // Setting image box
    imageLabel = new QLabel(this);
    imageLabel->move(50, 30);
    imageLabel->resize(500, 500);
    imageLabel->show();
}
