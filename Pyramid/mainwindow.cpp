#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	iteam = nullptr;
	scene = new QGraphicsScene(this);
	ui->graphicsView->setScene(scene);

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
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.png *.jpg)"));

    QString fileName = filePath.mid(filePath.lastIndexOf("/") + 1);
    Image currentImage(QPixmap(filePath), fileName);
	imagesList.insert(currentImage);
    setLoadedFiles(fileName);
    showCurrentPixmap(buildPyramidLevel(currentObject->pixmap, ui->spinBox->value(), ui->doubleSpinBox->value()));

}

void MainWindow::setLoadedFiles(const QString& activeImage)
{
	ui->comboBox->clear();

	int distance = 0;
	for (auto img : imagesList)
	{
		ui->comboBox->addItem(img.fileName);
		distance++;
	}
	ui->comboBox->setCurrentText(activeImage);
}

void MainWindow::showCurrentPixmap(const QPixmap& pixmapToShow)
{
	delete iteam;
	scene->clear();
	iteam = new QGraphicsPixmapItem(pixmapToShow);
	scene->setSceneRect(pixmapToShow.rect());
	scene->addItem(iteam);
    ui->sizeLable->setText(QString::number(currentObject->pixmap.width()) + "x" + QString::number(currentObject->pixmap.height()));
}


QPixmap MainWindow::buildPyramidLevel(const QPixmap& basePixmap, int level, double crop)
{
	if (&basePixmap != nullptr && !basePixmap.isNull())
	{
		int scale = pow(crop, level);
		QPixmap resPixmap = basePixmap.scaled(basePixmap.width() / scale, basePixmap.height() / scale, Qt::KeepAspectRatio);
		return resPixmap.scaled(basePixmap.width(), basePixmap.height(), Qt::KeepAspectRatio);
	}
}

void MainWindow::on_spinBox_valueChanged(int arg)
{
	if (ui->doubleSpinBox->value() > 0 && arg > 0)
        showCurrentPixmap(buildPyramidLevel(currentObject->pixmap, arg, ui->doubleSpinBox->value()));
}

void MainWindow::on_spinBox_valueChanged(const QString& arg)
{
	if (ui->doubleSpinBox->value() > 0 && arg.toInt() > 0)
        showCurrentPixmap(buildPyramidLevel(currentObject->pixmap, arg.toInt(), ui->doubleSpinBox->value()));
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg)
{
	if (ui->spinBox->value() > 0 && arg > 0)
        showCurrentPixmap(buildPyramidLevel(currentObject->pixmap, ui->spinBox->value(), arg));

}

void MainWindow::on_doubleSpinBox_valueChanged(const QString& arg)
{
	if (ui->spinBox->value() > 0 && arg.toDouble() > 0)
        showCurrentPixmap(buildPyramidLevel(currentObject->pixmap, ui->spinBox->value(), arg.toDouble()));

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
	if (index >= 0)
	{
		auto it = imagesList.begin();
		std::advance(it, index);
        currentObject = it;
        showCurrentPixmap(buildPyramidLevel(currentObject->pixmap, ui->spinBox->value(), ui->doubleSpinBox->value()));
	}
}
