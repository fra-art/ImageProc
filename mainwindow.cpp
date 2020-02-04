#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::closeWindows()
{
    qApp->closeAllWindows();
}
void MainWindow::bildLaden()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open Image"),QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        tr("Image Files(*.png, *.jpg, *.bmp, *.tif, *.PNG, *.JPG)"));

    if (filename==0)
        return;
    im_proc.bildLaden(filename.toStdString());
}
void MainWindow::invertieren()
{
    if(!windows.empty()){
    TIME_THIS
    im_proc.invert_image(windows[active_window_idx]->get_image());
    }
    else{
        QMessageBox::critical(this, "Error", "Kein Bild vorhanden!");
    }
}
void MainWindow::zeitmessung(QString time)
{
    if(ui->actionZeitmessung->isChecked()){
        QMessageBox::information(this, "Zeitmessung", time);
    }
}
void MainWindow::testBildLangsam()
{
    TIME_THIS
    im_proc.test_image_slow();
}

void MainWindow::testBildSchnell()
{
    TIME_THIS
    im_proc.test_image_fast();
}
void MainWindow::show_new_image(QImage image, QString name)
{
 ImageDisplayMainWindow* w = new ImageDisplayMainWindow(image, name, this);
 w->show();
 windows.push_back(w);
 size_t active_idx = windows.size() - 1;
 connect(w, &ImageDisplayMainWindow::got_focus, this, [=]() -> void {set_active_window(static_cast<int>(active_idx));});
 active_window_idx = static_cast<int>(active_idx);
}
void MainWindow::set_active_window(int idx)
{
    active_window_idx = idx;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    setWindowIcon(QIcon(":/image_proc.png"));

    //connect(ui->actionEnde, SIGNAL(triggered()), this, SLOT(closeAllWindows()));
    connect(ui->actionEnde, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    connect(ui->actionBild_laden, &QAction::triggered,this,&MainWindow::bildLaden);
    connect(ui->actioninvertieren, &QAction::triggered, this, &MainWindow::invertieren);
    connect(ui->actionTestbild_langsam, &QAction::triggered, this, &MainWindow::testBildLangsam);
    connect(ui->actionTestbild_schnell, &QAction::triggered, this, &MainWindow::testBildSchnell);
    connect(&im_proc, &ImageProcessingCollection::time_measured, this, &MainWindow::zeitmessung);
    connect(&im_proc, &ImageProcessingCollection::image_finished, this, &MainWindow::show_new_image);
}

MainWindow::~MainWindow()
{
    delete ui;
}

