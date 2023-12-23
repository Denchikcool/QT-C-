#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStack>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTCore/qmath.h>
#include <QKeyEvent>
#include <Qt>

namespace Ui {
class calculator;
}

class calculator : public QWidget
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = 0);
    QPushButton* createButton (const QString& str);
    void clearAll (); //Очистить всё
    void input(QString); //Обработка нажатия кнопки или клавиши
    void calculate (); //Вычисление
    ~calculator();

private:
    Ui::calculator *ui;
    QLabel *firststring; //метка для вывода предыдущего операнда или операции
    QLabel *displaystring;
    QStack <QString> stack;
protected:
    virtual void keyPressEvent(QKeyEvent *event); //Класс будет обрабатывать нажатия клавиш!
public slots:
    void slotButtonClicked ();
};

#endif // CALCULATOR_H
