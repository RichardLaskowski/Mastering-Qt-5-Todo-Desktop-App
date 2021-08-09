#include "Task.h"
#include "ui_Task.h"

Task::Task(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);

    //Instantiate Public Slots
    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);

    //Instantiate Private Slots
    connect(ui->checkBox, &QCheckBox::toggled, this, &Task::checked);

    //Instantiat Signals
    connect(ui->removeButton, &QPushButton::clicked, [this]{emit removed(this);});
}

void Task::checked(bool checked)
{
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit statusChanged(this);
}
void Task::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit task"), tr("Task name"), QLineEdit::Normal, this->name(), &ok);

    if (ok && !value.isEmpty())
    {
        setName(value);
    }
}
void Task::setName(const QString& name)
{
    ui->checkBox->setText(name);
}

QString Task::name() const
{
    return ui->checkBox->text();
}

bool Task::isCompleted() const
{
    return ui->checkBox->isChecked();
}

Task::~Task()
{
    delete ui;
}
