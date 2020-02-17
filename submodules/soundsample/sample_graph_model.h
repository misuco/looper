#ifndef SAMPLEGRAPHMODEL_H
#define SAMPLEGRAPHMODEL_H

#include <QAbstractListModel>

class Sample_graph_model : public QAbstractListModel
{
    Q_OBJECT

public:
    Sample_graph_model(QObject * parent = nullptr);

    void append(double value);
    void replace(int index, double value);
    void update();
    void reset();
    int size();
    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QVariant> m_data;

};


#endif // SAMPLEGRAPHMODEL_H
