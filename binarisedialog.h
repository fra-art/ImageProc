#ifndef BINARISEDIALOG_H
#define BINARISEDIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <imageprocessingcollection.h>
namespace Ui {
class BinariseDialog;
}

class BinariseDialog : public QDialog
{
    Q_OBJECT
    QImage m_image_src;
    QImage m_image_bin;
    QGraphicsScene* scene = nullptr;

public:
    explicit BinariseDialog(QWidget *parent = nullptr);
    ~BinariseDialog();

public slots:
    void update_window();
    void set_image(QImage image);
    void binarise_from_slider_val(int val);
    void emit_image_finished();

signals:
    void finished_image(QImage, QString);

private:
    Ui::BinariseDialog *ui;
};

#endif // BINARISEDIALOG_H
