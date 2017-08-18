#ifndef BMS_H
#define BMS_H

#include <QWidget>
#include <QObject>//qt 基类
#include <QSqlDatabase>//创建数据库连接
#include <QSqlQuery>//执行SQL语句。它可以返回所有的执行结果
#include <QVector>//vector stl
#include <QLineEdit>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QFrame>
#include <QGroupBox>
#include <QPushButton>
#include <QTabWidget>
#include <QTreeWidget>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QDateTime>
#include <QtSql>
#include <QStringList>
#include <QPluginLoader>
#include <QMessageBox>
#include <QCheckBox>
#include <QTableWidget>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    QSqlDatabase db;

    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    enum{tourist=-1,normal_user,administator};
    int user_id=0;
    int user_type = tourist;//-1:trveler(search only) 0:normal user(search,borrow,return)
                       //1:administator(search,borrow,return,insert)
    QTimer *timer;
private slots:

    bool createConnection();

    void updateTime();
    void on_treeWidget_clicked(const QModelIndex &index);

    void on_lineEdit_17_returnPressed();//neglect this function;just for learning

    void on_search_button_clicked();

    void on_clear_button_clicked();
    
    void on_login_button_clicked();

    void update_tablewidget(QTableWidget* tableWidget,QVector<QString> &result);

    void on_borrow_button_clicked();

    void on_insert_Button_clicked();

    void on_check_button_clicked();


    void on_return_button_clicked();

    void on_log_out_clicked();

private:
    Ui::Widget *ui;
};

#endif // BMS_H
