#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>
#include <QFileDialog>

#include <set>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
	class QImage;
	class QPixmap;
}
QT_END_NAMESPACE

struct Image
{
	QPixmap pixmap;
	QString fileName;

	Image() {}
	~Image() {}
	Image(const QPixmap& _pixmap, const QString& _fileName) :pixmap(_pixmap), fileName(_fileName) {}
	bool operator < (const Image& compElem) const
	{
		double firstDiagonal = sqrt(pixmap.width() * pixmap.width() + pixmap.height() * pixmap.height());
		double secondDiagonal = sqrt(compElem.pixmap.width() * compElem.pixmap.width() + compElem.pixmap.height() * compElem.pixmap.height());
		return firstDiagonal < secondDiagonal;
	}
};


using QPixmapContainer = std::set<Image>;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void on_actionAdd_new_triggered();
	void on_doubleSpinBox_valueChanged(double arg1);
	void on_doubleSpinBox_valueChanged(const QString& arg1);
	void on_spinBox_valueChanged(const QString& arg1);
	void on_spinBox_valueChanged(int arg1);
	void on_comboBox_currentIndexChanged(int index);

private:
	QPixmap buildPyramidLevel(const QPixmap& basePixmap, int level, double crop);
	void showCurrentPixmap(const QPixmap& pixmapToShow);
	void setLoadedFiles(const QString& activeImage);

	QPixmapContainer imagesList;
    QPixmapContainer::iterator currentObject;

	Ui::MainWindow* ui;
	QGraphicsItem* iteam;
	QGraphicsScene* scene;
};
#endif // MAINWINDOW_H
