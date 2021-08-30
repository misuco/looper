#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString  name    MEMBER m_name     NOTIFY QmlNameUpdated)
    Q_PROPERTY(double  play_pos MEMBER m_play_pos NOTIFY QmlPlayPosUpdated)
    Q_PROPERTY(bool    muted    MEMBER m_muted    NOTIFY QmlMutedUpdated)

public:
    Q_INVOKABLE void click(double x, double y);

    explicit Track(QObject *parent = nullptr);
    Track(QString name, QObject *parent = nullptr);

    void set_play_pos( double p );
    bool get_muted();

signals:
    void QmlNameUpdated();
    void QmlPlayPosUpdated();
    void QmlMutedUpdated();

private:
    QString m_name;
    double m_play_pos;
    int m_length;
    bool m_muted;

};

#endif // TRACK_H
