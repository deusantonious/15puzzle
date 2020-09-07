#pragma once

#include <QAbstractListModel>

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimention READ getDimention CONSTANT)
    Q_PROPERTY(bool isGameOver MEMBER m_isGameOver NOTIFY isGameOverChanged)

signals:
    void isGameOverChanged();

public:
    GameModel(QObject* parent = nullptr);

    int getDimention() const;

    Q_INVOKABLE void shuffleTiles(); //data????
    Q_INVOKABLE void move(int index);

    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role) const override; //?
    QHash <int, QByteArray> roleNames() const override;

    enum roles {
        hiddenNumberValue = Qt::UserRole + 1,
    };

private: //vars
    QVector<int> m_gameField;
    int m_dimention;
    int m_tilesCount;
    bool m_isGameOver;

private: //methods
    bool isBoardValid() const;
    bool isGameOver();
};
