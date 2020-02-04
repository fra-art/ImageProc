#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QStandardPaths>
#include <imagedisplaymainwindow.h>
#include "imageprocessingcollection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

    void closeWindows ();
    void bildLaden ();
    void zeitmessung (QString time);
    void invertieren();
    void testBildLangsam();
    void testBildSchnell();
    void show_new_image(QImage image, QString name);
    void set_active_window(int idx);


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ImageProcessingCollection im_proc;
    ImageDisplayMainWindow* activeWindow;
    std::vector<ImageDisplayMainWindow*> windows;
    int active_window_idx;
};

#endif // MAINWINDOW_H
