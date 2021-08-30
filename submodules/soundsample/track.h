#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString  name     MEMBER m_name     NOTIFY QmlNameUpdated)
    Q_PROPERTY(double  play_pos MEMBER m_play_pos NOTIFY QmlPlayPosUpdated)

public:
    explicit Track(QObject *parent = nullptr);
    Track(QString name, QObject *parent = nullptr);

    void set_play_pos( double p );

signals:
    void QmlNameUpdated();
    void QmlPlayPosUpdated();

private:
    QString m_name;
    double m_play_pos;
    int m_length;

};

#endif // TRACK_H
