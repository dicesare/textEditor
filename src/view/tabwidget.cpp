#include "tabwidget.h"
#include <QTextEdit>

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    connect(this, &QTabWidget::tabCloseRequested, this, &TabWidget::closeTab);
}

void TabWidget::addTabWithContent(const QString &content)
{
    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setPlainText(content);

    int newIndex = addTab(textEdit, "New Tab");
    setCurrentIndex(newIndex);
}

void TabWidget::closeTab(int index)
{
    QWidget *widgetToRemove = widget(index);
    removeTab(index);
    delete widgetToRemove;
}
