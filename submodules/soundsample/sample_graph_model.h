/**
 *
 * Copyright (C) 2021 Claudio Zopfi
 *
 * This file is part of the Looper project ( https://github.com/misuco/looper )
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
