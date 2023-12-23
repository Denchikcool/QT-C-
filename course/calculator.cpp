#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);
    QIcon icon(":/pics/calc.png");
    this->setWindowIcon(icon);
    this->setWindowTitle("Calculator");
    this->setMinimumHeight(350);
    this->setMinimumWidth(200);
    this->setMaximumHeight(350);
    this->setMaximumWidth(200);

    firststring = new QLabel(""); firststring->setMinimumSize (150, 50);
     displaystring = new QLabel(""); displaystring->setMinimumSize (150, 50);
     displaystring->setFont(QFont("sans", 14, QFont::Bold));
     QChar aButtons[4][4] = {
      {'7', '8', '9', '/'},
      {'4', '5', '6', '*'},
      {'1', '2', '3', '-'},
      {'0', '.', '=', '+'}
     };
     QGridLayout *myLayout = new QGridLayout;
     myLayout->addWidget(firststring, 0, 0, 1, 4);
     myLayout->addWidget(displaystring, 1, 0, 1, 4);
     myLayout->addWidget(createButton("CE"), 2, 3);
     for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
       myLayout->addWidget(createButton(aButtons[i][j]), i + 3, j);
      }
     }
     setLayout(myLayout);
}

calculator::~calculator()
{
    delete ui;
}

QPushButton* calculator::createButton (const QString& str) {
 QPushButton* pcmd = new QPushButton(str);
 pcmd->setMinimumSize(40, 30);
 connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
 return pcmd;
}

void calculator::calculate() {
 double dOperand2 = stack.pop().toDouble();
 QString strOperation = stack.pop();
 double dOperand1 = stack.pop().toDouble();
 double dResult = 0;
 if (strOperation == "+") { dResult = dOperand1 + dOperand2; }
 else if (strOperation == "-") { dResult = dOperand1 - dOperand2; }
 else if (strOperation == "/") { dResult = dOperand1 / dOperand2; }
 else if (strOperation == "*") { dResult = dOperand1 * dOperand2; }
 displaystring->setText(QString("%1").arg(dResult, 0, 'f', 3));
}

void calculator::input(QString str) {
 QString text = displaystring->text(); //отображаемый текст
 int len = text.length();
 QString last = "";
 if (len>0) last = text.right(1); //самый правый символ ввода
 if (((len==0 && stack.count()==0) ||
      ((stack.count()==2 && len>1 && (last=="+"||last=="-"||last=="*"||last=="/"))))
     && (str.contains(QRegExp("[0-9]")) || str=="-")) {
  //На экране пусто и стек пуст или введен 1-й операнд и операция
  //и при этом нажата цифра или "-"
  firststring->setText(text);
  text=str; //Стереть то, что было отображено, и отобразить нажатый символ
 }
 else if ((text+str).contains(QRegExp("^-?[0-9]+\\.?[0-9]*$"))) {
  text+=str; //Пока вводим число - добавлять символ
 }
 else if (text.contains(QRegExp("^-?[0-9]+\\.?[0-9]*$"))) { //Уже набрано число
  if (str=="*"||str=="/"||str=="+"||str=="-"||str=="=") { //Вычислить
   if (stack.count()==2) { //Есть 1-й операнд и число
    stack.push(text); //Положить в стек 2-й операнд
    firststring->setText(firststring->text()+text+"="); //отобразить вычисляемое выражение
    calculate(); //Вычислить
    text=displaystring->text(); //Показать результат
   }
   if (str!="=") { //Для вычисления "по цепочке"
    stack.push(text); //Положить в стек 1-й операнд
    text+=str; //Отобразить операцию до след.нажатия кнопки
    stack.push(str); //Положить в стек операцию
    firststring->setText(text);
   }
  }
 }
 displaystring->setText(text);
}

void calculator::clearAll() {
  stack.clear(); displaystring->setText(""); firststring->setText("");
}

void calculator::slotButtonClicked() {
 QString str = ((QPushButton*)sender())->text();
 if (str == "CE") clearAll();
 else input(str);
}

void calculator::keyPressEvent(QKeyEvent *event) {
 int key=event->key();
 QString str = QString(QChar(key));
 if (key==Qt::Key_Delete) clearAll();
 else input(str);
}
