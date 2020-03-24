#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"dll.h"
#include"DLL_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    DLL *intersectionconter = new DLL();
    std::vector<int> numArray;
    void draw_line(double x1, double y1, double x2,double y2, QString shape);
    void draw_cycle(double x, double y, double r, int offset);
    void create_array(QStringList strlist);
    void updatelistwidget2();
    void draw();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void slot_mouseRelese(QMouseEvent*);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
