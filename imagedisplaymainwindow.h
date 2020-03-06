#ifndef IMAGEDISPLAYMAINWINDOW_H
#define IMAGEDISPLAYMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <iostream>
#include <QLabel>
#include <QGraphicsSceneHoverEvent>


namespace Ui{
class ImageDisplayMainWindow;
}

class TrackingGraphicsViewPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    TrackingGraphicsViewPixmapItem(QPixmap pixmap);

public slots:

signals:
    void mouse_moved(int x, int y);


    // QGraphicsItem interface
protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
};

class TrackingGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    TrackingGraphicsView();
    TrackingGraphicsView(const TrackingGraphicsView&);
    TrackingGraphicsView(QWidget* parent = nullptr);
    ~TrackingGraphicsView() override = default;

public slots:

signals:
    void mouse_moved(int x, int y);
    void got_rgb(int r, int b, int g);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

class ImageDisplayMainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel* xy_label;
    QLabel* rgb_label;
    QLabel* image_type;

public:

    ImageDisplayMainWindow(QImage im, QString title, QWidget *parent = 0);
    ~ImageDisplayMainWindow();
    void init_statusbar();
    QImage get_image();

public slots:
    void update_statusbar(int x, int y);
    void update_status_bar_image_type(QImage::Format format);
    void update_image_view(QImage new_image);

signals:
    void got_focus();



private:

    Ui::ImageDisplayMainWindow *ui;
    QGraphicsScene scene;
    TrackingGraphicsViewPixmapItem* tracking_pixmap = nullptr;
    QImage image;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // IMAGEDISPLAYMAINWINDOW_H
