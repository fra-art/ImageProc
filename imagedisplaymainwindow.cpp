#include "imagedisplaymainwindow.h"
#include "ui_imagedisplaymainwindow.h"



ImageDisplayMainWindow::ImageDisplayMainWindow(QImage im, QString title, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageDisplayMainWindow),
    image(im)
{
ui->setupUi(this);

setWindowTitle(title);
QPixmap pixmap = QPixmap::fromImage(im);
tracking_pixmap = new TrackingGraphicsViewPixmapItem(pixmap);
scene.addItem(tracking_pixmap);
ui->graphicsView->setScene(&scene);

setMouseTracking(true);
init_statusbar();
connect(tracking_pixmap, &TrackingGraphicsViewPixmapItem::mouse_moved, this, &ImageDisplayMainWindow::update_statusbar);
//connect(&scene, SIGNAL(mouseMove(int, int)), this, SLOT(mouseMoved(int, int)));
}

ImageDisplayMainWindow::~ImageDisplayMainWindow()
{
}

void ImageDisplayMainWindow::init_statusbar()
{
    xy_label = new QLabel(this);
    rgb_label = new QLabel(this);
    ui->statusbar->addWidget(xy_label);
    ui->statusbar->addWidget(rgb_label);
}

QImage ImageDisplayMainWindow::get_image()
{
    return image;
}

void ImageDisplayMainWindow::update_statusbar(int x, int y)
{
    xy_label->setText(QString::number(x) + " " + QString::number(y));
    if(x < 0 || y < 0){
        return;
    }
    QRgb rgb = image.pixel(x, y);
    int r = (rgb & 0x00FF0000) >> 16;
    int g = (rgb & 0x0000FF00) >> 8;
    int b = (rgb & 0x000000FF);
    QString red = "<font COLOR=#FF0000> R: " + QString::number(r) + " ";
    QString green = "<font COLOR=#00FF00> G: " + QString::number(g) + " ";
    QString blue =  "<font COLOR=#0000FF> B: " + QString::number(b);
    QString rgb_str = red + green + blue;
    rgb_label->setText(rgb_str);
}

void ImageDisplayMainWindow::update_status_bar_image_type(QImage::Format format)
{

}

void ImageDisplayMainWindow::update_image_view(QImage new_image)
{
    setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    scene.clear();
    image = new_image;
    QPixmap pixmap = QPixmap::fromImage(image);
    if(tracking_pixmap){
        delete tracking_pixmap;
    }
    tracking_pixmap = new TrackingGraphicsViewPixmapItem(pixmap);
    scene.addItem(tracking_pixmap);
    ui->graphicsView->fitInView(scene.itemsBoundingRect(),Qt::KeepAspectRatio);
    update_status_bar_image_type(new_image.format());
}

void ImageDisplayMainWindow::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    emit got_focus();
}


TrackingGraphicsView::TrackingGraphicsView()
    : QGraphicsView()
{
    setMouseTracking(true);
}

TrackingGraphicsView::TrackingGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setMouseTracking(true);
}

void TrackingGraphicsView::resizeEvent(QResizeEvent *event)
{
    fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
    event->accept();
}

TrackingGraphicsViewPixmapItem::TrackingGraphicsViewPixmapItem(QPixmap pixmap)
    : QGraphicsPixmapItem(pixmap)
{
    setAcceptHoverEvents(true);
}

void TrackingGraphicsViewPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    emit mouse_moved(x, y);
    event->accept();
}
