#include <algorithm>
#include <chrono>
#include <random>
#include "gameModel.h"

gameModel::gameModel(QObject *parent)
    :QAbstractListModel {parent}
{
    m_gameField.resize(tilesCount);
    std::iota(m_gameField.begin() + 1, m_gameField.end(), 1);
    shuffleTiles();
}

void gameModel::shuffleTiles()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 randomGenerator(seed);

    do {
        std::shuffle(m_gameField.begin(), m_gameField.end(), randomGenerator);
    }
    while (!isBoardValid());
}

bool gameModel::VectorIndexIsValid(size_t index) const
{
    return index < tilesCount;
}

bool gameModel::isBoardValid() const
{
    int inv {0};
    for (size_t i {0}; i < tilesCount; ++i) {
        for (size_t j = i; j < tilesCount; ++j) {
            if (m_gameField[j].value < m_gameField[i].value && m_gameField[i].value != tilesCount){
                ++inv;
            }
        }
    }
    const size_t start_point = 1;

    for (size_t i = 0; i < tilesCount; ++i) {
        if (m_gameField[i].value == tilesCount){
            inv += start_point + i / sqrt(tilesCount);
        }
    }

    return (inv % 2) == 0;
}

int gameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return tilesCount;
}

QVariant gameModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const int rowNumber {index.row()};
    if(!VectorIndexIsValid(rowNumber)){
        return {};
    }
    return QVariant::fromValue(m_gameField[rowNumber].value);
}
