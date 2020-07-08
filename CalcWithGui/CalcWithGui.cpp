#include "CalcWithGui.h"


std::stack <char> stack;
string Infix;
double result;
History histo(Infix, result);
int counterCalculation = -1;
int indexHisto = 0;



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

    connect(ui.pushButton_point, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_bracketopen, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_bracketclose, SIGNAL(released()), this, SLOT(button_pressed()));

    connect(ui.pushButton_plus, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_minus, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_mult, SIGNAL(released()), this, SLOT(button_pressed()));
    connect(ui.pushButton_divide, SIGNAL(released()), this, SLOT(button_pressed()));
}


void CalcWithGui::button_pressed()
{
    QPushButton* button = (QPushButton*)sender();

    QString label_term;
    QString label_result;

    label_result = ui.label_result->text();

    if (label_result == "")
    {
        label_term = (ui.label_term->text() + button->text());
    }
    else
    {
        string h = (button->text()).toStdString();
        char Zeichen = h[0];

        if (isdigit(Zeichen))
        {
            label_term = button->text();
            ui.label_result->setText("");
        }
        else {
            h = label_result.toStdString();
            if (isdigit(h[0]) || ((h[0] == '-') && isdigit(h[1])))
            {
                label_term = (ui.label_result->text() + button->text());
                ui.label_result->setText("");
            }
            else
            {
                label_term = button->text();
                ui.label_result->setText("");
            }
        }
    }
    ui.label_term->setText(label_term);
}

void CalcWithGui::on_pushButton_root_released()
{
    QString label_term;
    QString label_result;

    label_result = ui.label_result->text();
    if (label_result == "")
    {
        label_term = (ui.label_term->text() + "sqr(");
    }
    else
    {
        ui.label_result->setText("");
        label_term = "sqr(";
    }
    ui.label_term->setText(label_term);
}

void CalcWithGui::on_pushButton_pi_released()
{
    QString label_term;
    QString label_result;

    label_result = ui.label_result->text();

    if (label_result == "")
    {
        label_term = (ui.label_term->text() + "pi");
    }
    else
    {
        label_term = "pi";
        ui.label_result->setText("");
    }
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
            //Behandlung von pi
            if ((label_term.size() > 1) && (label_term[label_term.size() - 2] == ("p")) && (label_term[label_term.size() - 1] == ("i")))
            {
                label_term.resize(label_term.size() - 2);
            }
            else
            {
                //behandlung von Ans
                if ((label_term.size() > 2) && (label_term[label_term.size() - 3] == ("A")) && (label_term[label_term.size() - 2] == ("n")) && (label_term[label_term.size() - 1] == ("s")))
                {
                    label_term.resize(label_term.size() - 3);
                }
                else
                {
                    if ((label_term.size() > 1) && (label_term[label_term.size() - 2] == ("^")) && (label_term[label_term.size() - 1] == ("(")))
                    {
                        label_term.resize(label_term.size() - 2);
                    }
                    else
                    {
                        label_term.resize(label_term.size() - 1);
                    }
                }
            }
        }        
        ui.label_term->setText(label_term);
    }
    else 
    {
        ui.label_result->setText("");
    }
}

void CalcWithGui::on_pushButton_allclear_released()
{
    ui.label_term->setText("");
    ui.label_result->setText("");
}

void CalcWithGui::on_pushButton_result_released()
{
    std::stack <char> stack;
    QString label_term;
    InputCheck check(Infix);
    double help;
    bool errorStatus;
    QString msg;
    bool debug = true;

    try {
        errorStatus = false;

        label_term = ui.label_term->text();
        Infix = label_term.toStdString();
        if(counterCalculation >= 0)
        {
            Infix = check.checkInfix(Infix, histo.outputResult(counterCalculation)); //Ohne Ans
        }
        else
        {
            Infix = check.checkInfix(Infix, 0.0);
        }
        if (debug)
        {
            msg = QString::fromStdString("Checked: "+Infix);
            qDebug() << msg;
        }
        RPN ItoP(Infix);
        std:string Postfix = ItoP.infixToPostfix(stack, Infix);

        if (debug)
        {
            msg = QString::fromStdString("Postfix: "+ Postfix);
            qDebug() << msg;
        }
        Calculation Calculation1(Postfix);
        result = Calculation1.calc(Postfix);
        if (debug)
        {
            msg = QString::fromStdString("Result: " + to_string(result));
            qDebug() << msg;
        }
        label_term = QString::number(result, 'g',10); //Präzision von 10
        ui.label_result->setText(label_term);
    }
    catch (const OwnException & e)
    {
        qDebug() << e.what();
        ui.label_result->setText(e.what());
        errorStatus = true;
    }
    catch (std::exception e)
    {
        msg = QString::fromStdString("Unknown Error: " + string(e.what()));
        qDebug() << msg;
        ui.label_result->setText(msg);
        errorStatus = true;
    }

    if (!errorStatus)
    {
        label_term = ui.label_term->text();
        Infix = label_term.toStdString();
        histo.writeHistory(Infix, result);
        counterCalculation++;
        indexHisto = counterCalculation;
    }
}

void CalcWithGui::on_pushButton_up_released()
{
    QString label_term;
    QString label_result;
    string infixHisto;
    double resultHisto;

    if (indexHisto > 0)
    {
        indexHisto--;
        infixHisto = histo.outputInfix(indexHisto);
        resultHisto = histo.outputResult(indexHisto);

        label_term = QString::fromStdString(infixHisto);
        label_result = QString::number(resultHisto);

        ui.label_term->setText(label_term);
        ui.label_result->setText(label_result);
    }

}

void CalcWithGui::on_pushButton_down_released()
{
    QString label_term;
    QString label_result;
    string infixHisto;
    double resultHisto;

    if (indexHisto < counterCalculation)
    {
        indexHisto++;
        infixHisto = histo.outputInfix(indexHisto);
        resultHisto = histo.outputResult(indexHisto);

        label_term = QString::fromStdString(infixHisto);
        label_result = QString::number(resultHisto);

        ui.label_term->setText(label_term);
        ui.label_result->setText(label_result);
    }
}

void CalcWithGui::on_pushButton_ans_released()
{
    QString label_term;
    QString label_result;

    label_result = ui.label_result->text();

    if (label_result == "")
    {
        label_term = (ui.label_term->text() + "Ans");
    }
    else
    {
        label_term = "Ans";
        ui.label_result->setText("");
    }
    ui.label_term->setText(label_term);
}

void CalcWithGui::on_pushButton_potenz_released()
{
    QString label_term;
    QString label_result;

    label_result = ui.label_result->text();

    if (label_result == "")
    {
        label_term = (ui.label_term->text() + "^(");
    }
    else
    {
        label_term = ui.label_result->text()+"^(";
        ui.label_result->setText("");
    }
    ui.label_term->setText(label_term);
}
