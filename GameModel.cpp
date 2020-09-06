#include <algorithm>
#include <chrono>
#include <random>
#include "GameModel.h"

GameModel::GameModel(QObject *parent)
    :QAbstractListModel {parent},
      m_dimention {4},
      m_tilesCount {m_dimention * m_dimention},
      m_hiddenValue {m_tilesCount},
      m_isActive {true}
{
    m_gameField.resize(m_tilesCount);
    std::iota(m_gameField.begin(), m_gameField.end(), 1);
    shuffleTiles();
}

void GameModel::shuffleTiles()
{
    m_isActive = true;
    auto seed {std::chrono::system_clock::now().time_since_epoch().count()};
    static std::mt19937 randomGenerator{seed};
    beginResetModel();
    do {
        std::shuffle(m_gameField.begin(), m_gameField.end(), randomGenerator);
    }
    while (!isBoardValid());
    endResetModel();
}

void GameModel::move(int index)
{
    int moveFrom {index};
    int moveTo {-1};
    int moveExtender {0};
    if (!VectorIndexIsValid(index) || m_isActive == false) {
        return;
    }
    //left
    if (index - 1 >= 0 &&
            m_gameField[index - 1] == m_hiddenValue &&
            index % 4 != 0)
    {
        moveTo = index - 1;
    }//right
    else if (index + 1 < m_tilesCount &&
             m_gameField[index + 1] == m_hiddenValue &&
             (index + 1) % 4 != 0)
    {
        moveExtender = 1;
        moveTo = index + 1;
    }//up
    else if (index - 4 >= 0 &&
             m_gameField[index - 4] == m_hiddenValue)
    {
        moveTo = index - 4;
    }//down
    else if (index + 4 < m_tilesCount &&
             m_gameField[index + 4] == m_hiddenValue)
    {
        moveExtender = 1;
        moveTo = index + 4;
    }
    if (moveTo != -1)// if moveTo == -1 >>> nothing to move
    {
        beginMoveRows(QModelIndex(), moveFrom, moveFrom, QModelIndex(), moveTo + moveExtender);
        std::swap(m_gameField[moveFrom], m_gameField[moveTo]);
        endMoveRows();

        if (moveFrom < moveTo){
            emit dataChanged(createIndex(moveFrom, 0), createIndex(moveTo, 0), QVector<int> {Qt::DisplayRole});
        }
        else {
            emit dataChanged(createIndex(moveTo, 0), createIndex(moveFrom, 0), QVector<int> {Qt::DisplayRole});
        }
    }
    isGameOver();
}

bool GameModel::VectorIndexIsValid(int index) const
{
    return index < m_tilesCount;
}

bool GameModel::isBoardValid() const
{
    int inv {0};
    for (int i {0}; i < m_tilesCount; ++i) {
        for (int j {i}; j < m_tilesCount; ++j) {
            if (m_gameField[j] < m_gameField[i] && m_gameField[i] != m_tilesCount) {
                ++inv;
            }
        }
    }
    const int start_point = 1;

    for (int i {0}; i < m_tilesCount; ++i) {
        if (m_gameField[i] == m_tilesCount) {
            inv += start_point + i / m_dimention;
        }
    }

    return (inv % 2) == 0;
}

bool GameModel::isGameOver()
{
    int count {m_tilesCount - 2};
    for (int i {0}; i < count; i++) {
        if (m_gameField[i + 1] - m_gameField[i] != 1) {
            return false;
        }
    }
    m_isActive = false;
    emit gameOver();
    return true;
}

bool GameModel::getIsActive() const
{
    return m_isActive;
}

void GameModel::setIsActive(bool isActive)
{
    m_isActive = isActive;
}

int GameModel::getHiddenValue() const
{
    return m_hiddenValue;
}

int GameModel::getDimention() const
{
    return m_dimention;
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_tilesCount;
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const int rowNumber {index.row()};
    if (!VectorIndexIsValid(rowNumber)) {
        return {};
    }
    return QVariant::fromValue(m_gameField[rowNumber]);
}
