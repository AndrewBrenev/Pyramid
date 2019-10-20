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

	currentObject = QPixmap(filePath);
	filePath = filePath.mid(filePath.lastIndexOf("/") + 1);
	Image currentImage(currentObject, filePath);
	imagesList.insert(currentImage);
	setLoadedFiles(filePath);
	showCurrentPixmap(buildPyramidLevel(currentObject, ui->spinBox->value(), ui->doubleSpinBox->value()));

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
	ui->sizeLable->setText(QString::number(currentObject.width()) + "x" + QString::number(currentObject.height()));
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
		showCurrentPixmap(buildPyramidLevel(currentObject, arg, ui->doubleSpinBox->value()));
}

void MainWindow::on_spinBox_valueChanged(const QString& arg)
{
	if (ui->doubleSpinBox->value() > 0 && arg.toInt() > 0)
		showCurrentPixmap(buildPyramidLevel(currentObject, arg.toInt(), ui->doubleSpinBox->value()));
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg)
{
	if (ui->spinBox->value() > 0 && arg > 0)
		showCurrentPixmap(buildPyramidLevel(currentObject, ui->spinBox->value(), arg));

}

void MainWindow::on_doubleSpinBox_valueChanged(const QString& arg)
{
	if (ui->spinBox->value() > 0 && arg.toDouble() > 0)
		showCurrentPixmap(buildPyramidLevel(currentObject, ui->spinBox->value(), arg.toDouble()));

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
	if (index >= 0)
	{
		auto it = imagesList.begin();
		std::advance(it, index);
		currentObject = it->pixmap;
		showCurrentPixmap(buildPyramidLevel(currentObject, ui->spinBox->value(), ui->doubleSpinBox->value()));
	}
}
