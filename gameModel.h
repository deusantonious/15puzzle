#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractListModel>
#include <vector>

class gameModel : public QAbstractListModel
{
    Q_OBJECT

public:
    static constexpr size_t tilesCount {16};

    gameModel(QObject* parent = nullptr);

    struct Tile{
        size_t value {};

        Tile& operator = (const size_t newValue) {
            value = newValue;
            return *this;
        }
        bool operator == (const size_t other) {
            return value == other;
        }

    };

private:
    std::vector<Tile> m_gameField;
    void shuffleTiles();
    bool VectorIndexIsValid(size_t index) const;
    bool isBoardValid() const;

    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

#endif // GAMEMODEL_H
