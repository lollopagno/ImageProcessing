#include <QMainWindow>
#include <QApplication>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget* parent = nullptr);

public slots:
    void open();
    void showImage();
    void convertToGray();
    void canny();
};