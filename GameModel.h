#pragma once

#include <QAbstractListModel>
#include <vector>

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimention READ getDimention CONSTANT)
    Q_PROPERTY(int hiddenValue READ getHiddenValue CONSTANT)
    Q_PROPERTY(bool isGameOver MEMBER m_isActive NOTIFY gameOver)

signals:
    void gameOver();

public:
    GameModel(QObject* parent = nullptr);

    int getDimention() const;
    int getHiddenValue() const;
    bool getIsActive() const;
    void setIsActive(bool isActive);

    Q_INVOKABLE void shuffleTiles();
    Q_INVOKABLE void move(int index);

    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private: //vars
    std::vector<int> m_gameField;
    int m_dimention;
    int m_tilesCount;
    int m_hiddenValue;
    bool m_isActive;

private: //methods
    bool VectorIndexIsValid(int index) const;
    bool isBoardValid() const;
    bool isGameOver();
};
