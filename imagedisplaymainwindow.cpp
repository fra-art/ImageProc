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
connect(tracking_pixmap, &TrackingGraphicsViewPixmapItem::mouse_moved, this, &ImageDisplayMainWindow::update_statusbar_xy);
//connect(&scene, SIGNAL(mouseMove(int, int)), this, SLOT(mouseMoved(int, int)));
}

ImageDisplayMainWindow::~ImageDisplayMainWindow()
{
}

void ImageDisplayMainWindow::init_statusbar()
{
    xy_label = new QLabel(this);
    ui->statusbar->addWidget(xy_label);
}

QImage ImageDisplayMainWindow::get_image()
{
    return image;
}

void ImageDisplayMainWindow::update_statusbar_xy(int x, int y)
{
    xy_label->setText(QString::number(x) + " " + QString::number(y));
}

void ImageDisplayMainWindow::update_status_bar_rgb(unsigned char r, unsigned char g, unsigned char b)
{

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
    emit mouse_moved(event->pos().x(), event->pos().y());
    event->accept();
}
