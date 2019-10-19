#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentImage = new  QImage ("C:/gitProjects/freeCode/Pyramide/Pyramid/img/mount.jpg");
    iteam = new QGraphicsPixmapItem(QPixmap::fromImage(*currentImage ));
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addItem(iteam);
    updateLables();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAdd_new_triggered()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Images (*.png *.jpg)"));

    scene->clear();
    currentImage = new  QImage (fileName);
    QGraphicsItem* iteam2 =new QGraphicsPixmapItem  (QPixmap::fromImage(*currentImage ));
    scene->setSceneRect( currentImage->rect());
    scene->addItem(iteam2);
    updateLables();
}

void MainWindow::updateLables()
{
    ui->widthValuelabel->setNum(currentImage->width());
    ui->heightValuelabel->setNum(currentImage->height());
}
