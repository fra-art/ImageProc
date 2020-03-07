#include "binarisedialog.h"
#include "ui_binarisedialog.h"

BinariseDialog::BinariseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinariseDialog)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &BinariseDialog::binarise_from_slider_val);
}

BinariseDialog::~BinariseDialog()
{
    delete ui;
}

void BinariseDialog::update_window()
{
    auto pixmap = QPixmap::fromImage(m_image_bin);
    auto scene = new QGraphicsScene();
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

}

void BinariseDialog::set_image(QImage image)
{
    m_image_src = image;
    m_image_bin = image;
    update_window();
}

void BinariseDialog::binarise_from_slider_val(int val)
{
    m_image_bin = ImageProcessingCollection::binarisieren(m_image_src, val);
    update_window();
}

void BinariseDialog::emit_image_finished()
{
    emit finished_image(m_image_bin, "Binarisiert");
}
