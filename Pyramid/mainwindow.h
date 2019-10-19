#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtGui>


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

    void updateLables();

private:

    Ui::MainWindow *ui;

    QImage *currentImage;
    QGraphicsItem *iteam;
    QGraphicsScene *scene;


};
#endif // MAINWINDOW_H
