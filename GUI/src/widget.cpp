#include "widget.h"
#include "ui_widget.h"
#include <QVector>
#include <string>
#include<iostream>
#include "QDebug"
#include "qcustomplot.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->listwidget1->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes |
                              QCP::iSelectLegend | QCP::iSelectPlottables);
    connect(ui->widget, SIGNAL(mouseRelease(QMouseEvent*)),this, SLOT(slot_mouseRelese(QMouseEvent*)));
    ui->widget->setSelectionTolerance(1);

}

void Widget::slot_mouseRelese(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton){
        return;
    }
    QPointF ChickedPoint = event->pos();
    if(!ui->widget->viewport().contains(event->pos())){
        return;
    }
    double currentx = ui->widget->xAxis->pixelToCoord(ChickedPoint.x());
    double currenty = ui->widget->yAxis->pixelToCoord(ChickedPoint.y());
    ui->widget->clearGraphs();
    for (int i = 0; i < ui->listwidget1->count(); i++) {
        QString line = ui->listwidget1->item(i)->text();
        QStringList strlist = line.split(" ");
        create_array(strlist);
    }
    draw();
    updatelistwidget2();
    draw_line(currentx + 0.01, currenty, currentx - 0.01, currenty, "P");
    draw_line(currentx, currenty + 0.01, currentx, currenty - 0.01, "P");
    ui->widget->replot();
    QToolTip::showText(mapToGlobal(event->pos()), QString("%1, %2").arg(currentx).arg(currenty), this);
}

void Widget::create_array(QStringList strlist) {
    int type = 0;
    int a = strlist[1].toInt();
    int b = strlist[2].toInt();
    int c = strlist[3].toInt();
    int d = 0;
    if (strlist[0] == "L") {
        type = 1;
        d = strlist[4].toInt();
    }
    else if (strlist[0] == "R"){
        type = 2;
        d = strlist[4].toInt();
    }
    else if (strlist[0] == "S") {
        type = 3;
        d = strlist[4].toInt();
    }
    else if (strlist[0] == "C"){
        type = 4;
    }
    numArray.push_back(type);
    numArray.push_back(a);
    numArray.push_back(b);
    numArray.push_back(c);
    numArray.push_back(d);
}

void Widget::draw_line(double x1, double y1, double x2,double y2, QString shape) {
    QPen pen;
    QVector<double> x(2), y(2);
    x[0] = x1;
    x[1] = x2;
    y[0] = y1;
    y[1] = y2;
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount() - 1)->setData(x, y);
    if (shape == "L") {
        pen.setColor(Qt::red);
    }
    else if (shape == "S") {
        pen.setColor(Qt::green);
    }
    else if (shape == "R") {
        pen.setColor(Qt::yellow);
    }
    else {
        pen.setColor(Qt::black);
    }
    ui->widget->graph(ui->widget->graphCount() - 1)->setPen(pen);
}

void Widget::draw_cycle(double x, double y, double r, int offset) {
    double originx = x - r;
    QPen pen;
    QVector<double> upx(r * 2 * offset + 1), upy(r * 2 * offset + 1);
    QVector<double> downx(r * 2 * offset + 1), downy(r * 2 * offset + 1);
    for (int i = 0; i <= r * 2 * offset; i++) {
        upx[i] = originx;
        upy[i] = y + sqrt(r * r - (originx - x) * (originx - x));
        originx += 1.0 / offset;
    }
    originx = x - r;
    for (int i = 0; i <= r * 2 * offset; i++) {
        downx[i] = originx;
        downy[i] = y - sqrt(r * r - (originx - x) * (originx - x));
        originx += 1.0 / offset;
    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount() - 1)->setData(upx, upy);
    pen.setColor(Qt::blue);
    ui->widget->graph(ui->widget->graphCount() - 1)->setPen(pen);
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount() - 1)->setData(downx, downy);
    ui->widget->graph(ui->widget->graphCount() - 1)->setPen(pen);
}

void Widget::draw() {
    std::vector<double> res = intersectionconter->getFigures();
    for (int i = 0; i < int(res.size()); i += 5) {
        if (res[i] == 1) {
            draw_line(res[i + 1], res[i + 2], res[i + 3], res[i + 4], "L");
        }
        else if (res[i] == 2) {
            draw_line(res[i + 1], res[i + 2], res[i + 3], res[i + 4], "R");
        }
        else if (res[i] == 3) {
            draw_line(res[i + 1], res[i + 2], res[i + 3], res[i + 4], "S");
        }
        else if (res[i] == 4) {
            draw_cycle(res[i + 1], res[i + 2], res[i + 3], 100);
        }
    }
}

void Widget::updatelistwidget2() {
    QString line;
    intersectionconter->setFigures(numArray);
    std::vector<double> positions = intersectionconter->getIntersects();
    ui->listwidget2->clear();
    line = QString("num: %1").arg(int(positions.size() / 2));
    ui->listwidget2->addItem(line);
    for (int i = 0; i < int(positions.size()); i += 2) {
        line = QString("%1 %2").arg(positions[i]).arg(positions[i + 1]);
        draw_cycle(positions[i], positions[i + 1], 0.02, 100);
        ui->listwidget2->addItem(line);
    }
}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString path = ui->text1->text();
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line = in.readLine();
    int n = line.toInt();
    for (int i = 0; i < n; i++) {
        line = in.readLine();
        ui->listwidget1->addItem(line);
        QStringList strlist = line.split(" ");
        create_array(strlist);
    }
    updatelistwidget2();
    draw();
    ui->widget->replot();
    file.close();
}

void Widget::on_pushButton_2_clicked()
{
    QString line = ui->text2->text();
    ui->listwidget1->addItem(line);
    QStringList strlist = line.split(" ");
    create_array(strlist);
    updatelistwidget2();
    draw();
    ui->widget->replot();
}

void Widget::on_pushButton_3_clicked()
{
    while(ui->listwidget1->selectedItems().size()>0)
    {
        QListWidgetItem* sel = ui->listwidget1->selectedItems().at(0);
        if (sel)
        {
            int r = ui->listwidget1->row(sel);
            sel = ui->listwidget1->takeItem(r);
        }
    }
    ui->widget->clearGraphs();
    numArray.clear();
    intersectionconter->reset();
    for (int i = 0; i < ui->listwidget1->count(); i++) {
        QString line = ui->listwidget1->item(i)->text();
        QStringList strlist = line.split(" ");
        create_array(strlist);
    }
    updatelistwidget2();
    draw();
    ui->widget->replot();
}

void Widget::on_pushButton_4_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(NULL,"标题",".","*.txt");

    if(file_path.isEmpty())
    {
        return;
    }
    else {
        ui->text1->setText(file_path);
    }
}
