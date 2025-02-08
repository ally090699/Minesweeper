/**
 * Name: Allison So
 * Description: customButton class file to handle different mouse clicks (NOT default: left clicks)
 * Date: 2/6/2025
 * */

#include "customButton.h"
#include <QIcon>

/**
 * Name: customButton default constructor
 * Description: Default constructor for customButton, initializes the button with a parent widget.
 * Parameters: QWidget pointer called parent - the parent widget.
 * Return: None
 * */
customButton::customButton(QWidget *parent) : QPushButton(parent){}

/**
 * Name: customButton custom constructor
 * Description: Custom constructor for customButton, initializes the button with text and a parent widget.
 * Parameters:
 *    - QString text: The text displayed on the button.
 *    - QWidget pointer called parent: The parent widget.
 * Return: None
 */
customButton::customButton(QString text, QWidget *parent) : QPushButton(text, parent){}

/**
 * Name: mousePressEvent
 * Description: Handles mouse press events. If the right mouse button is clicked, the button cycles through
 *              different flag states (unopened -> flagged -> question mark -> unopened). Otherwise, it calls
 *              the default QPushButton behaviour.
 * Parameters:
 *    - QMouseEvent pointer called event: The mouse event.
 * Return: None
 */
void customButton::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton){
        if (this->property("flag")=="u"){
            // button is unopened --> flag it
            QIcon icon(":/icons/icons/flag.svg.png");
            this->setIcon(icon);
            this->setProperty("flag", "f");
        }
        else if (this->property("flag")=="f"){
            // button flagged --> question mark
            QIcon icon(":/icons/icons/question.svg.png");
            this->setIcon(icon);
            this->setProperty("flag", "q");
        }
        else if (this->property("flag")=="q"){
            // button question --> unflag it
            QIcon icon(":/icons/icons/0.svg.png");
            this->setIcon(icon);
            this->setProperty("flag", "u");
        }
    } else { // otherwise, default mouse event
        QPushButton::mousePressEvent(event);
    }
}
