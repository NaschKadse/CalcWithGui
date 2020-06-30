#include "CalcWithGui.h"
#include <QString>
#include <QDebug>
#include <string>

CalcWithGui::CalcWithGui(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton_0, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_1, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_2, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_3, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_4, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_5, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_6, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_7, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_8, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_9, SIGNAL(released()), this, SLOT(button_pressed()));

    //connect(ui.pushButton_point, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_bracketopen , SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_bracketclose, SIGNAL(released()), this, SLOT(button_pressed()));

    connect(ui.pushButton_plus, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_minus, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_mult, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_divide, SIGNAL(released()), this, SLOT(button_pressed()));

    /////////////////////////////////////

}

void CalcWithGui::button_pressed()
{
    QPushButton* button = (QPushButton*)sender();

    QString label_term;

    label_term = (ui.label_term->text() + button->text());

    ui.label_term->setText(label_term);
}

void CalcWithGui::on_pushButton_root_released()
{
    QPushButton* button = (QPushButton*)sender();
    QString label_term;

    label_term = (ui.label_term->text() + "sqr(");
    ui.label_term->setText(label_term);
}
void CalcWithGui::on_pushButton_pi_released()
{
    QPushButton* button = (QPushButton*)sender();
    QString label_term;

    label_term = (ui.label_term->text() + "pi");
    ui.label_term->setText(label_term);
}

void CalcWithGui::on_pushButton_delete_released()
{
    QString label_term;
    QString label_result;

    label_term = ui.label_term->text();
    label_result = ui.label_result->text();

    if ((label_term.size() > 0) && !(label_result.size() > 0))
    {
        //Behandlung von Wurzeln
        if ((label_term.size() > 3) && (label_term[label_term.size() - 4] == ("s")) && (label_term[label_term.size() - 3] == ("q")) && (label_term[label_term.size() - 2] == ("r")))
        {
            label_term.resize(label_term.size() - 4);
        }
        else
        {
            if ((label_term.size() > 1) && (label_term[label_term.size() - 2] == ("p")) && (label_term[label_term.size() - 1] == ("i")))
            {
                label_term.resize(label_term.size() - 2);
            }
            else
            {
                label_term.resize(label_term.size() - 1);
            }
        }        
        ui.label_term->setText(label_term);
    }
}

void CalcWithGui::on_pushButton_allclear_released()
{
    ui.label_term->setText("");
    ui.label_result->setText("");
}

void CalcWithGui::on_pushButton_result_released()
{
    QString label_term;
    label_term = ui.label_term->text();
    ui.label_result->setText(label_term);
}