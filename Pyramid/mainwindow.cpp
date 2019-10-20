#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentPixmap= QPixmap("C:/gitProjects/freeCode/Pyramide/Pyramid/img/mount.jpg" );
    //iteam = new QGraphicsPixmapItem(currentPixmap);
    iteam = nullptr;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
   // scene->addItem(iteam);
   // updateLables();

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

    currentPixmap = QPixmap::fromImage(QImage (fileName) );
    showCurrentPixmar(currentPixmap);

}

void MainWindow::showCurrentPixmar(const QPixmap &pixmapToShow)
{
    delete iteam;
    scene->clear();
    iteam = new QGraphicsPixmapItem (pixmapToShow);
    scene->setSceneRect(pixmapToShow.rect());
    scene->addItem(iteam);
    updateLables();
}

void MainWindow::updateLables()
{
  //  ui->widthValuelabel->setNum(currentImage->width());
  //  ui->heightValuelabel->setNum(currentImage->height());
}

QPixmap MainWindow:: buildPyramidLevel(const QPixmap& basePixmap,int level,double crop)
{
    int scale = pow(crop,level);
    QPixmap resPixmap = basePixmap.scaled(basePixmap.width()/ scale, basePixmap.height() / scale,Qt::KeepAspectRatio);
    return resPixmap.scaled(basePixmap.width(),basePixmap.height(),Qt::KeepAspectRatio);
}

void MainWindow::on_spinBox_valueChanged(int arg)
{
   if( ui->doubleSpinBox->value()> 0 && arg > 0)
    showCurrentPixmar(buildPyramidLevel(currentPixmap,arg,ui->doubleSpinBox->value()));
}

void MainWindow::on_spinBox_valueChanged(const QString &arg)
{
    if( ui->doubleSpinBox->value()> 0 && arg.toInt() > 0)
     showCurrentPixmar(buildPyramidLevel(currentPixmap,arg.toInt(),ui->doubleSpinBox->value()));
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg)
{
    if(ui->spinBox->value() > 0 && arg>0)
        showCurrentPixmar(buildPyramidLevel(currentPixmap,ui->spinBox->value(),arg));

}

void MainWindow::on_doubleSpinBox_valueChanged(const QString &arg)
{
    if(ui->spinBox->value() > 0 && arg.toDouble()>0 )
        showCurrentPixmar(buildPyramidLevel(currentPixmap,ui->spinBox->value(),arg.toDouble()));

}


