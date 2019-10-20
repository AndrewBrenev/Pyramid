#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class QImage;
class QPixmap;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_new_triggered();
    void on_doubleSpinBox_valueChanged(double arg1);
    void on_doubleSpinBox_valueChanged(const QString &arg1);

    void on_spinBox_valueChanged(const QString &arg1);

private:
    QPixmap buildPyramidLevel(const QPixmap& basePixmap,int level,double crop);
    void updateLables();
    void showCurrentPixmar(const QPixmap &pixmapToShow);
    void on_spinBox_valueChanged(int arg1);

    Ui::MainWindow *ui;
    QPixmap currentPixmap;
    QGraphicsItem *iteam;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
