#include "sample_graph_model.h"
#include <QDebug>

Sample_graph_model::Sample_graph_model(QObject *parent) : QAbstractListModel(parent) {}

void Sample_graph_model::append(double value) {
    beginInsertRows(QModelIndex(), m_data.size(),m_data.size()+1);
    m_data.append(QVariant(value));
    endInsertRows();
}

void Sample_graph_model::replace(int index, double value) {
    m_data[index] = QVariant(value);
}

void Sample_graph_model::update() {
    beginRemoveRows(QModelIndex(), 0, m_data.size()-1);
    endRemoveRows();
    beginInsertRows(QModelIndex(), 0, m_data.size()-1);
    endInsertRows();
}

void Sample_graph_model::reset()
{
    m_data.clear();
    beginRemoveRows(QModelIndex(), 0, m_data.size()-1);
    endRemoveRows();
}

int Sample_graph_model::size()
{
    //qDebug() << "SampleGraphModel::size " << m_data.size();
    return m_data.size();
}

int Sample_graph_model::rowCount(const QModelIndex &) const
{
    //qDebug() << "SampleGraphModel::rowCount " << m_data.size();
    return m_data.size();
}

int Sample_graph_model::columnCount(const QModelIndex &) const {
    //qDebug() << "SampleGraphModel::columnCount " << m_data.size();
    return 1;
}

QVariant Sample_graph_model::data(const QModelIndex &index, int role) const {
    Q_UNUSED(role)

    //qDebug() << "SampleGraphModel::data " << index.row();
    return m_data.at(index.row());
}

QHash<int, QByteArray> Sample_graph_model::roleNames() const {
    //qDebug() << "SampleGraphModel::roleNames";
    QHash<int, QByteArray> roles;
    roles[0] = "sample";
    return roles;
}
