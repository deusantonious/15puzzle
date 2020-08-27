#ifndef GameModel_H
#define GameModel_H

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

    struct Tile {
        int value {};

        Tile& operator = (const int newValue) {
            value = newValue;
            return *this;
        }
        bool operator == (const int other) {
            return value == other;
        }

    };

    int getDimention() const;
    int getHiddenValue() const;
    bool getIsActive() const;
    void setIsActive(bool isActive);

    Q_INVOKABLE void shuffleTiles();
    Q_INVOKABLE void move(int index);

private: //vars
    std::vector<Tile> m_gameField;
    int m_dimention;
    int m_tilesCount;
    int m_hiddenValue;
    bool m_isActive;

private: //methods
    bool VectorIndexIsValid(int index) const;
    bool isBoardValid() const;
    bool isGameOver();

    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

#endif // GameModel_H
