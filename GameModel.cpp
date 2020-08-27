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
    beginResetModel();
    m_gameField.resize(m_tilesCount);
    std::iota(m_gameField.begin(), m_gameField.end(), 1);
    shuffleTiles();
    endResetModel();
    emit dataChanged(createIndex(0, 0), createIndex(m_tilesCount, 0), QVector<int> {Qt::DisplayRole});
}

void GameModel::shuffleTiles()
{
    m_isActive = true;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 randomGenerator(seed);
    beginResetModel();
    do {
        std::shuffle(m_gameField.begin(), m_gameField.end(), randomGenerator);
    }
    while (!isBoardValid());
    endResetModel();
    emit dataChanged(createIndex(0, 0), createIndex(m_tilesCount, 0), QVector<int> {Qt::DisplayRole});
}

void GameModel::move(int index)
{
    if(!VectorIndexIsValid(index) || m_isActive == false) {
        return;
    }
    //left
    if(index - 1 >= 0 &&
            m_gameField.at(index - 1) == m_hiddenValue &&
            index % 4 != 0) {
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index - 1);
        std::swap(m_gameField.at(index - 1), m_gameField.at(index));
        endMoveRows();
        emit dataChanged(createIndex(index - 1, 0), createIndex(index, 0), QVector<int> {Qt::DisplayRole});
    }//right
    else if(index + 1 < m_tilesCount &&
            m_gameField.at(index + 1) == m_hiddenValue &&
            (index + 1) % 4 != 0) {
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index + 2);
        std::swap(m_gameField.at(index + 1), m_gameField.at(index));
        endMoveRows();
        emit dataChanged(createIndex(index, 0), createIndex(index + 1, 0), QVector<int> {Qt::DisplayRole});
    }//up
    else if(index - 4 >= 0 &&
            m_gameField.at(index - 4) == m_hiddenValue) {
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index - 4);
        std::swap(m_gameField.at(index), m_gameField.at(index - 4));
        endMoveRows();
        emit dataChanged(createIndex(index - 4, 0), createIndex(index, 0), QVector<int> {Qt::DisplayRole});
    }//down
    else if(index + 4 < m_tilesCount &&
            m_gameField.at(index + 4) == m_hiddenValue) {
        beginMoveRows(QModelIndex(), index, index, QModelIndex(), index + 5);
        std::swap(m_gameField.at(index), m_gameField.at(index + 4));
        endMoveRows();
        emit dataChanged(createIndex(index, 0), createIndex(index + 4, 0), QVector<int> {Qt::DisplayRole});
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
        for (int j = i; j < m_tilesCount; ++j) {
            if (m_gameField[j].value < m_gameField[i].value && m_gameField[i].value != m_tilesCount) {
                ++inv;
            }
        }
    }
    const int start_point = 1;

    for (int i = 0; i < m_tilesCount; ++i) {
        if (m_gameField[i].value == m_tilesCount) {
            inv += start_point + i / m_dimention;
        }
    }

    return (inv % 2) == 0;
}

bool GameModel::isGameOver()
{
    int count  = m_tilesCount - 2;
    for(int i = 0; i < count; i++) {
        if(m_gameField.at(i + 1).value - m_gameField.at(i).value != 1) {
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
    if(!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const int rowNumber {index.row()};
    if(!VectorIndexIsValid(rowNumber)) {
        return {};
    }
    return QVariant::fromValue(m_gameField[rowNumber].value);
}
