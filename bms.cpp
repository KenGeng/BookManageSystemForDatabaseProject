#include "bms.h"
#include "ui_bms.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    createConnection();

    //initial timer to renew time
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);
    //set initial state
    ui->usertype_edit_label->setText("tourist");

}

Widget::~Widget()
{
    delete ui;
}
void Widget::updateTime(){
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd \nhh:mm:ss\n ddd");
    QString text;
    text = current_date+" ";
    ui->dataText->setText(text);
}

bool Widget::createConnection(){
    //连接MySQL数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    //设置主机名
    db.setHostName("localhost");
    //设置数据库名
    db.setDatabaseName("Book_Management_System");
    //设置账号名
    db.setUserName("root");
    //设置密码名
    db.setPassword("gengbiaosql");
    //设置端口
    db.setPort(3306);
    if(!db.open()){
        QMessageBox::critical(0,QObject::tr("error"),db.lastError().text());
        return false;
    }
    return true;
}


void Widget::on_treeWidget_clicked(const QModelIndex &index)
{

        QSqlQuery query;
        //QString text =
        QString text_search = ui->treeWidget->currentItem()->text(0);
        qDebug()<<text_search;
        QVector<QString>result;
        //根据type，在book表中进行检索
        if (text_search == "type") query.exec("select * from book");
        else query.exec("select * from book where type = '"+text_search+"'");
        if(!query.isActive()){
            QMessageBox::critical(0,QObject::tr("error"),"the query isn't executed!");
        }

        //搜索的结果暂存于结果容器中
        result.clear();
        //remember the following code;query.next is the first query!
        while(query.next()){
            QString str = query.value(0).toString();

            for(int i=0;i<9;i++){
                result.push_back(query.value(i).toString());

            }
        }
    //update the tablewidget to display results
      update_tablewidget(ui->tableWidget,result);

}

void Widget::on_lineEdit_17_returnPressed()//don't care this function
{
    QSqlQuery query;
    //QString text =
    QString text_search = ui->lineEdit_17->text();
    qDebug()<<text_search;

    QVector<QString>result;
    if (text_search == "type") query.exec("select * from book");
    else query.exec("select * from book where type = '"+text_search+"'");

    if(!query.isActive()){
        QMessageBox::critical(0,QObject::tr("error"),"the query isn't executed!");
    }

    result.clear();
    while(query.next()){
        QString str = query.value(0).toString();

        for(int i=0;i<9;i++){
            result.push_back(query.value(i).toString());

        }
    }
    update_tablewidget(ui->tableWidget,result);
}

void Widget::on_search_button_clicked()
{
    QSqlQuery query;
    QString text_name = ui->lineEdit_17->text().isEmpty() ?"": ui->lineEdit_17->text();
    QString text_isbn = ui->lineEdit_18->text().isEmpty() ?"": ui->lineEdit_18->text();
    QString text_author = ui->lineEdit_19->text().isEmpty() ?"": ui->lineEdit_19->text();
    //search accoding to the input of isbn,name,author
    QVector<QString>result;
    int flag1,flag2,flag3;
    flag1 = !!text_name.isEmpty();
    flag2 = !!text_isbn.isEmpty();
    flag3 = !!text_author.isEmpty();
    if (!flag1&&!flag2&&!flag3){//0
        query.exec("select * from book where (name = '"+text_name+"')"+"and (isbn='"+text_isbn
                        +"')"+"and (author='"+ text_author+"')");
    }else if(!flag1&&!flag2&&flag3){//1
        query.exec("select * from book where (name = '"+text_name+"')"+"and (isbn='"+text_isbn
                   +"')");
    }
    else if (!flag1&&flag2&&!flag3) {//2
        query.exec("select * from book where (name = '"+text_name+"')"+"and (author='"+ text_author+"')");
    }
    else if (!flag1&&flag2&&flag3) {//3
        query.exec("select * from book where (name = '"+text_name+"')");
    }
    else if (flag1&&!flag2&&!flag3) {//4
        query.exec("select * from book where (isbn='"+text_isbn
                        +"')"+"and (author='"+ text_author+"')");
    }
    else if (flag1&&!flag2&&flag3) {//5
        query.exec("select * from book where  (isbn='"+text_isbn
                        +"')");
    }
    else if (flag1&&flag2&&!flag3) {//6
        query.exec("select * from book where (author='"+ text_author+"')");
    }
    else if (flag1&&flag2&&flag3) {//7
        QMessageBox::critical(0,QObject::tr("error"),"no input!");
    }


    if(!query.isActive()){
        QMessageBox::critical(0,QObject::tr("error"),"the query isn't executed!");
    }
    //把搜索的结果暂存于结果容器
    result.clear();
    while(query.next()){
        QString ans="";
        QString str = query.value(0).toString();

        for(int i=0;i<9;i++){
            result.push_back(query.value(i).toString());
        }
       // result.push_back(ans);
    }
    if(result.empty()) QMessageBox::critical(0,QObject::tr("!"),"sorry,no result!");
    update_tablewidget(ui->tableWidget,result);
}

void Widget::on_clear_button_clicked()
{
    //clear the search window
    ui->lineEdit_17->clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_19->clear();
    QVector<QString>result_empty(100,"");
    update_tablewidget(ui->tableWidget,result_empty);

}

//void Widget::setTitle(){
//  another way to set the title image
//    QPalette palette;
//    ui->Title->setAutoFillBackground(true);
//    //titleImage->setStyleSheet("border-image: url(C:\\Users\\Ken\\Documents\\TEST_2017\\title.jpg)");
//    QPixmap pixmap("C:\\Users\\Ken\\Documents\\TEST_2017\\6.png");
//    QPixmap fitpixmap=pixmap.scaled(1024,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    //problem: not know how to get the height of the background
//    palette.setBrush(QPalette::Background,QBrush(fitpixmap));

//   // palette.setBrush(QPalette::Background,QBrush(QPixmap("C:\\Users\\Ken\\Documents\\TEST_2017\\6.png")));
//    ui->Title->setPalette(palette);
//}
void Widget::update_tablewidget(QTableWidget* tableWidget,  QVector<QString> &result){
    int row = tableWidget->rowCount();
    int col = tableWidget->columnCount();

    for (int i =0;i<row;i++){
        for (int j =0;j<col;j++){
            if(i*10+j<result.size()-1){
                if (j==0){
                    tableWidget->item(i,j)->setCheckState(Qt::Unchecked);
                }
                else tableWidget->setItem(i,j,new QTableWidgetItem(result[i*row+j-1]));
            }
            else   tableWidget->setItem(i,j,new QTableWidgetItem(""));;
        }
    }
}

void Widget::on_login_button_clicked()
{//login function

    QString text_id = ui->login_userid->text();
    QString text_password = ui->login_password->text();
    QSqlQuery query;

    if (text_id.isEmpty()||text_password.isEmpty()){
        QMessageBox::about(0,QObject::tr("error"),"information isn't complete!");
    }
    else{
        query.exec("select password from user where user_id ='"+text_id+"'");
        if(!query.isActive()){
            QMessageBox::critical(0,QObject::tr("error"),"the query isn't executed!");
        }
         QString str;
        while(query.next()){
            str = query.value(0).toString();
        }
        if(str.isEmpty()) QMessageBox::about(0,QObject::tr("error"),"no such id!");
        else if(str==text_password) {
            QMessageBox::about(0,QObject::tr("success"),"login success!");
            ui->login_userid->setEnabled(false);
            ui->login_password->setEnabled(false);
            user_id = text_id.toInt();
            query.exec("select type from user where user_id ='"+text_id+"'");
           while(query.next()){
               user_type = query.value(0).toInt();
           }
           if(user_type==normal_user) ui->usertype_edit_label->setText("normal user");
           if(user_type==administator) ui->usertype_edit_label->setText("administator");


        }
        else QMessageBox::about(0,QObject::tr("error"),"wrong password!");
    }

}



void Widget::on_borrow_button_clicked()
{//borrow fuction
    if(user_type==tourist) {
        QMessageBox::about(0,QObject::tr("error"),"Please login first!");
        return;
    }
    QSqlQuery query;
    int row = ui->tableWidget->rowCount();
    int col = ui->tableWidget->columnCount();
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd");
    QString idstring = QString::number(user_id, 10);
    for (int i =0;i<row;i++){
            if(ui->tableWidget->item(i,0)->checkState()){
                if (ui->tableWidget->item(i,5)->text()=='0'){
                     QMessageBox::about(0,QObject::tr("error"),"no storage!");
                }
                else {
                    QString temp_isbn = ui->tableWidget->item(i,1)->text();
                    QString temp_name = ui->tableWidget->item(i,2)->text();
                    query.exec("update book set storage= storage-1 where  (isbn='"+temp_isbn
                                +"')");
                    query.exec("insert into record values("+idstring+","+temp_isbn+",'"+temp_name+"','"+current_date+"',0)");

                     qDebug()<<row;
                    if(!query.isActive()){
                        QMessageBox::critical(0,QObject::tr("error"),"the query isn't executed!");
                    }
                    else QMessageBox:: about(0,QObject::tr("success"),"borrow success!");
                }
        }else continue;
    }
    ui->lineEdit_17->clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_19->clear();
    QVector<QString>result_empty(100,"");
    update_tablewidget(ui->tableWidget, result_empty);
}

void Widget::on_insert_Button_clicked()
{//insert function
    if(user_type != administator) {
        QMessageBox:: about(0,QObject::tr("failure"),"no such grants!");
        return;
    }
    if(ui->isbnEdit->text().isEmpty()||ui->authorEdit->text().isEmpty()||ui->priceEdit->text().isEmpty()
            ||ui->nameEdit->text().isEmpty()||ui->numberEdit->text().isEmpty()||ui->typeEdit->text().isEmpty()
            ||ui->yearEdit->text().isEmpty()||ui->publisherEdit->text().isEmpty()){
        QMessageBox:: about(0,QObject::tr("failure"),"information not complete!");
        return;
    }
    QString idstring = QString::number(user_id, 10);//类型转换都是坑QAQ
    QSqlQuery query,query2,query3;
    query2.exec("select isbn from book where isbn="+ui->isbnEdit->text());
    QString str="";
   while(query2.next()){
       str = query2.value(0).toString();
   }

    if(str!=""){
        //update the book table if the book exists
       query3.exec("update book set storage=storage+"+ui->numberEdit->text()+" where isbn="+str);
       if(!query3.isActive())  QMessageBox:: about(0,QObject::tr("error"),"insert failuer2!");
         qDebug()<<ui->numberEdit->text();
       return;
   }

    //update the book table if not exists
    query.exec("insert into book values("+ui->isbnEdit->text()+",'"+ui->nameEdit->text()+"','"+ui->authorEdit->text()+"','"
               +ui->typeEdit->text()+"',"+ui->numberEdit->text()+","+ui->priceEdit->text()+",'"+ui->publisherEdit->text()+"',"
               +ui->yearEdit->text()+","+ui->numberEdit->text()+","+idstring+");");
    if(!query.isActive())  QMessageBox:: about(0,QObject::tr("error"),"insert failuer!");
    else QMessageBox:: about(0,QObject::tr("success"),"insert success!");

}


void Widget::on_check_button_clicked()
{
    //ui->tableWidget_4 is the record table
    QSqlQuery query;
    QVector<QString>result;
     QString idstring = QString::number(user_id, 10);
    //根据分类，在record表中进行检索
    query.exec("select * from record where user_id = '"+idstring+"' order by borrow_date desc");
    if(!query.isActive()){
        QMessageBox::critical(0,QObject::tr("error"),"the query isn't executed!");
    }

    //把搜索的结果暂存于结果容器中
    result.clear();
    while(query.next()){
        QString str = query.value(0).toString();

        for(int i=0;i<5;i++){
            result.push_back(query.value(i).toString());

        }
    }

    int row = ui->tableWidget_4->rowCount();
    int col = ui->tableWidget_4->columnCount();

    for (int i =0;i<row;i++){
        for (int j =0;j<col;j++){
            if(i*row+j<=result.size()){
                if (j==0){
                    ui->tableWidget_4->item(i,j)->setCheckState(Qt::Unchecked);
                }
                else if(j==5){
                    if(result[i*row+j-1]!='1')
                   ui->tableWidget_4->setItem(i,j,new QTableWidgetItem("no"));
                    else ui->tableWidget_4->setItem(i,j,new QTableWidgetItem("yes"));
                }
                else ui->tableWidget_4->setItem(i,j,new QTableWidgetItem(result[i*row+j-1]));
            }
            else if (j==0){
                ui->tableWidget_4->item(i,j)->setCheckState(Qt::Unchecked);
            }
            else  ui->tableWidget_4->setItem(i,j,new QTableWidgetItem(""));;
        }
    }
}


void Widget::on_return_button_clicked()
{
    QSqlQuery query;
    int row = ui->tableWidget_4->rowCount();
    int col = ui->tableWidget_4->columnCount();

    for (int i =0;i<row;i++){
            if(ui->tableWidget_4->item(i,0)->checkState()){
                if (ui->tableWidget_4->item(i,5)->text()=="yes"){
                     QMessageBox::about(0,QObject::tr("error"),"already return!");
                     return;
                }
                else {
                    QString temp_isbn = ui->tableWidget_4->item(i,2)->text();
                    QString temp_id = ui->tableWidget_4->item(i,1)->text();
                    QString temp_date = ui->tableWidget_4->item(i,4)->text();
                    query.exec("update record set state= 1 where  (isbn='"+temp_isbn
                                +"') and user_id = "+temp_id+" and state = 0 ");
                    query.exec("update book set storage= storage+1 where  (isbn='"+temp_isbn
                                +"')");
                    ui->tableWidget_4->item(i,5)->setText("yes");
                     qDebug()<<temp_id ;
                    if(!query.isActive()){
                        QMessageBox::critical(0,QObject::tr("error"),"the query isn't executed!");

                    }
                    else QMessageBox:: about(0,QObject::tr("success"),"retrun success!");
                }
        }else continue;
    }
}

void Widget::on_log_out_clicked()
{
    user_id = 0;
    user_type = tourist;
     QMessageBox:: about(0,QObject::tr("success"),"log out success!");
     ui->login_userid->setText("");
     ui->login_password->setText("");
     ui->login_userid->setEnabled(true);
     ui->login_password->setEnabled(true);
     ui->usertype_edit_label->setText("tourist");


}
