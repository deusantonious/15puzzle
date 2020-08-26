#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractListModel>
#include <vector>

class GameModel : public QAbstractListModel
{
    Q_OBJECT

public:
    static constexpr size_t tilesCount {16};

    GameModel(QObject* parent = nullptr);

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
};

#endif // GAMEMODEL_H
