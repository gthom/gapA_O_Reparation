#include "dialogajoutpieceareparation.h"
#include "ui_dialogajoutpieceareparation.h"

DialogAjoutPieceAReparation::DialogAjoutPieceAReparation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjoutPieceAReparation)
{
    ui->setupUi(this);
    ui->groupBox->setVisible(false);
    //je cache la saisie du stock d'alerte
    ui->labelSeuilAlerte->setVisible(false);
    ui->spinBoxSeuilAlerte->setVisible(false);

}

DialogAjoutPieceAReparation::~DialogAjoutPieceAReparation()
{
    delete ui;
}

QString DialogAjoutPieceAReparation::getReference()
{
    return ui->lineEditPeferencePiece->text();
}

QString DialogAjoutPieceAReparation::getLibelle()
{
    return ui->lineEditLibellePiece->text();
}

QString DialogAjoutPieceAReparation::getQuantite()
{
    return QString::number(ui->spinBoxQuantiteNecessaire->value());
}

QString DialogAjoutPieceAReparation::getSeuilAlerte()
{
    return QString::number(ui->spinBoxSeuilAlerte->value());
}
bool DialogAjoutPieceAReparation::getStocke()
{
    return ui->checkBoxStocke->isChecked();
}

void DialogAjoutPieceAReparation::on_pushButtonNewPiece_clicked()
{
    ui->groupBox->setVisible(true);
}

void DialogAjoutPieceAReparation::on_checkBoxStocke_stateChanged(int arg1)
{
    //on cache ou pas la saisie du stock d'alerte
    ui->spinBoxSeuilAlerte->setVisible(arg1!=0);
    ui->labelSeuilAlerte->setVisible(arg1!=0);
}
