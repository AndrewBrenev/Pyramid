#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H


#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit  ImageView(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // IMAGEVIEW_H
