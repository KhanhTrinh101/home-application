#include "applicationsmodel.h"
#include <QDebug>

ApplicationItem::ApplicationItem(QString title, QString url, QString iconPath)
{
    m_title = title;
    m_url = url;
    m_iconPath = iconPath;
}

QString ApplicationItem::title() const
{
    return m_title;
}

QString ApplicationItem::url() const
{
    return m_url;
}

QString ApplicationItem::iconPath() const
{
    return m_iconPath;
}

ApplicationsModel::ApplicationsModel(QObject *parent)
{
    Q_UNUSED(parent)
}

int ApplicationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant ApplicationsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();
    const ApplicationItem &item = m_data[index.row()];
    if (role == TitleRole)
        return item.title();
    else if (role == UrlRole)
        return item.url();
    else if (role == IconPathRole)
        return item.iconPath();
    return QVariant();
}

void ApplicationsModel::addApplication(ApplicationItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data << item;
    endInsertRows();
}

ApplicationItem ApplicationsModel::getData(int index)
{
    return m_data.at(index);
}

void ApplicationsModel::preorder(int low, int hight)
{
    if(low != hight){
        // dich sang phai
        if(low > hight) {
            qDebug() << "goi vao preorder: " << low << " to " << hight;
            beginMoveRows(QModelIndex(), low, low, QModelIndex(), hight);
            m_data.move(low, hight);
            endMoveRows();
        }
        // dich sang trai
        else if(low < hight) {
            qDebug() << "goi vao preorder: " << hight << " to " << low;
            beginMoveRows(QModelIndex(), hight, hight, QModelIndex(), low);
            m_data.move(hight, low);
            endMoveRows();
        }
    }
}

QHash<int, QByteArray> ApplicationsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[UrlRole] = "url";
    roles[IconPathRole] = "iconPath";
    return roles;
}

