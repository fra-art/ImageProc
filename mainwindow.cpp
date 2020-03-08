#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagedisplaymainwindow.h"

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
    {
    TIME_THIS
    im_proc.test_image_fast();
    }
}

void MainWindow::resize()
{
            int height = QInputDialog::getInt(this, "Skalieren", "neue Höhe des Bildes:");
            int width = QInputDialog::getInt(this, "Skalieren", "neue Breite des Bildes:");
            {
                TIME_THIS
            im_proc.resize_image(height, width, windows[active_window_idx]->get_image());
            }
}

void MainWindow::equalize()
{

    TIME_THIS
            im_proc.equalize_histogram(windows[active_window_idx]->get_image());
}

void MainWindow::gaussian()
{
            int height = QInputDialog::getInt(this, "Größe des Filters", "Wähle eine ungerade Zahl: ");
            double sigma = QInputDialog::getDouble(this, "Sigmawert", "Bitte Sigmawert angeben: ", 0);
            int width = height;
            {
                TIME_THIS
                if(height % 2){
                im_proc.gaussian_blurr(height, width, sigma, windows[active_window_idx]->get_image());
                }
                else{
                QMessageBox::critical(this, "Error", "Zahl darf nicht gerade sein!");
                }
            }
}

void MainWindow::median()
{
    TIME_THIS
    int size = QInputDialog::getInt(this, "Größe des Filters", "Wähle eine ungerade Zahl: ");
    if(size % 2){
        im_proc.median(size, windows[active_window_idx]->get_image());
    }
    else{
        QMessageBox::critical(this, "Error", "Zahl darf nicht gerade sein!");
    }
}

void MainWindow::mean()
{
            int size = QInputDialog::getInt(this, "Filtergröße", "Bitte Filtergröße angeben: ");
            TIME_THIS
                    im_proc.mean(windows[active_window_idx]->get_image(), size);
}

void MainWindow::mean_seperated()
{
    int height = QInputDialog::getInt(this, "Filtergröße", "Wähle eine ungerade Zahl: ");
    int width = height;
    if(height % 2){
        TIME_THIS{
        im_proc.mean_separated(windows[active_window_idx]->get_image(), width, height);
        }
    }
    else{
        QMessageBox::critical(this, "Error", "Zahl darf nicht gerade sein!");
    }

}

void MainWindow::dilate()
{
    TIME_THIS
            im_proc.dilate(windows[active_window_idx]->get_image());

}

void MainWindow::erode()
{
    TIME_THIS
    im_proc.erode(windows[active_window_idx]->get_image());

}


void MainWindow::laplacian()
{
    TIME_THIS
            im_proc.laplacian(windows[active_window_idx]->get_image());
}

void MainWindow::canny()
{
    double t1 = QInputDialog::getDouble(this, "erster Grenzwert", "Wähle den ersten Grenzwert(0-255): ");
    double t2 = QInputDialog::getDouble(this, "zweiter Grenzwert", "Wähle den zweiten Grenzwert(0-255): ");

    TIME_THIS
            im_proc.canny_filter(windows[active_window_idx]->get_image(), t1, t2);
}

void MainWindow::sobel()
{
            auto sobel_dialog = new QDialog(this);
            sobel_dialog->setWindowTitle("Ableitungsrichtung");
            auto layout = new QVBoxLayout();
            auto x_checkbox = new QCheckBox("Sobel in x-Richtung", this);
            auto y_checkbox = new QCheckBox("Sobel in y-Richtung", this);
            layout->addWidget(x_checkbox);
            layout->addWidget(y_checkbox);
            auto button_layout = new QHBoxLayout();
            auto ok_button = new QPushButton("Ok", this);
            auto cancel_button = new QPushButton("Cancel", this);
            auto size_line_edit = new QLineEdit(this);
            size_line_edit->setPlaceholderText("Filtergröße");
            size_line_edit->setInputMask("D");
            button_layout->addWidget(ok_button);
            button_layout->addWidget(cancel_button);
            layout->addWidget(size_line_edit);
            layout->addLayout(button_layout);
            sobel_dialog->setLayout(layout);
            int size = 1;
            QImage active_image = windows[active_window_idx]->get_image();
            int x = 0;
            int y = 1;
            connect(size_line_edit, &QLineEdit::textChanged, [&size](QString text){size = text.toInt();});
            connect(cancel_button, &QAbstractButton::clicked, sobel_dialog, &QDialog::close);
            connect(x_checkbox, &QCheckBox::clicked, [&x](bool checked){x = checked ? 1 : 0;});
            connect(y_checkbox, &QCheckBox::clicked, [&y](bool checked){y = checked ? 1 : 0;});
            connect(ok_button, &QAbstractButton::clicked, [=](){
               sobel_dialog->close();
               {
               TIME_THIS
               if(!(size % 2) || size > 7){
                   return;
               }
               im_proc.sobel_filter(x, y, size, active_image);
               }
            });
            sobel_dialog->show();
}
#if 0
void MainWindow::draw_line()
{


    im_proc.draw_line(cv::Point(TrackingGraphicsViewPixmapItem::mouse_moved(x(),y()), TrackingGraphicsViewPixmapItem::y()), windows[active_window_idx]->get_image());
}
#endif

void MainWindow::binarise()
{
    binarise_dialog->set_image(windows[active_window_idx]->get_image());
    binarise_dialog->open();
}

void MainWindow::grauwert()
{
    TIME_THIS
            im_proc.convert_to_gray_value(windows[active_window_idx]->get_image());
}

void MainWindow::rotate()
{
    int angle = QInputDialog::getInt(this, "Rotationswinkel", "Wähle den gewünschten Rotationswinkel: ");
    TIME_THIS
            im_proc.rotate(windows[active_window_idx]->get_image(), angle);

}

void MainWindow::histogram()
{
    im_proc.histogram(windows[active_window_idx]->get_image());

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
    ,binarise_dialog(new BinariseDialog(this))
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    setWindowIcon(QIcon(":/image_proc.png"));

    connect(ui->actionEnde, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    connect(ui->actionBild_laden, &QAction::triggered,this,&MainWindow::bildLaden);
    connect(ui->actionInvertieren, &QAction::triggered, this, &MainWindow::invertieren);
    connect(ui->actionTestbild_langsam, &QAction::triggered, this, &MainWindow::testBildLangsam);
    connect(ui->actionTestbild_schnell, &QAction::triggered, this, &MainWindow::testBildSchnell);
    connect(&im_proc, &ImageProcessingCollection::time_measured, this, &MainWindow::zeitmessung);
    connect(&im_proc, &ImageProcessingCollection::image_finished, this, &MainWindow::show_new_image);
    connect(ui->actionScaling, &QAction::triggered, this, &MainWindow::resize);
    connect(ui->actionHistogrammausgleich, &QAction::triggered, this, &MainWindow::equalize);
    connect(ui->actionGaussfilter, &QAction::triggered, this, &MainWindow::gaussian);
    connect(ui->actionMedianfilter, &QAction::triggered, this, &MainWindow::median);
    connect(ui->actionMittelwertfilter, &QAction::triggered, this, &MainWindow::mean);
    connect(ui->actionDilatieren, &QAction::triggered, this, &MainWindow::dilate);
    connect(ui->actionErodieren, &QAction::triggered, this, &MainWindow::erode);
    connect(ui->actionLaPlace_Operator, &QAction::triggered, this, &MainWindow::laplacian);
    connect(ui->actionKantenfilter_Canny, &QAction::triggered, this, &MainWindow::canny);
    connect(ui->actionSobelfilter, &QAction::triggered, this, &MainWindow::sobel);
    connect(binarise_dialog, &BinariseDialog::finished_image, this, &MainWindow::show_new_image);
    connect(ui->actionBinarisieren, &QAction::triggered, this, &MainWindow::binarise);
    connect(binarise_dialog, &BinariseDialog::accepted, binarise_dialog, &BinariseDialog::emit_image_finished);
    connect(ui->actionFarbbild_zu_Grauwertbild, &QAction::triggered, this, &MainWindow::grauwert);
    connect(ui->actionRotieren, &QAction::triggered, this, &MainWindow::rotate);
    connect(ui->actionHistogramm, &QAction::triggered, this, &MainWindow::histogram);
    connect(ui->actionseparierter_Mittelwertfilter, &QAction::triggered, this, &MainWindow::mean_seperated);
}

MainWindow::~MainWindow()
{
    delete ui;
}

