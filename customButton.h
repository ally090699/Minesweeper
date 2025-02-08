#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class customButton : public QPushButton{
    Q_OBJECT

public:
    explicit customButton(QWidget *parent = nullptr);

    explicit customButton(QString text, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // CUSTOMBUTTON_H
