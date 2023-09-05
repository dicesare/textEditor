#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = nullptr);
    void addTabWithContent(const QString &content);

private slots:
    void closeTab(int index);
};

#endif // TABWIDGET_H
