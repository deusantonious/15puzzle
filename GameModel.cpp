#include <algorithm>
#include <chrono>
#include <random>
#include "GameModel.h"

GameModel::GameModel(QObject *parent)
    :QAbstractListModel {parent},
      m_dimention {4},
      m_tilesCount {m_dimention * m_dimention},
      m_isGameOver {true}
{
    m_gameField.resize(m_tilesCount);
    std::iota(m_gameField.begin(), m_gameField.end(), 1);
    shuffleTiles();
}

void GameModel::shuffleTiles()
{
    m_isGameOver = true;
    auto seed {std::chrono::system_clock::now().time_since_epoch().count()};
    static std::mt19937 randomGenerator {seed};

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
    int moveExtender {0}; // can be 0 or 1 need to beginMoveRows correct work

    if (index < 0 || index >= m_tilesCount || m_isGameOver == false) {
        return;
    }
    //left
    if (index - 1 >= 0 &&
            m_gameField[index - 1] == m_tilesCount && //m_tilesCount - hiddenvalue
            index % 4 != 0)
    {
        moveTo = index - 1;
    }//right
    else if (index + 1 < m_tilesCount && //m_tilesCount - size
             m_gameField[index + 1] == m_tilesCount && //m_tilesCount - hiddenvalue
             (index + 1) % 4 != 0)
    {
        moveExtender = 1;
        moveTo = index + 1;
    }//up
    else if (index - 4 >= 0 &&
             m_gameField[index - 4] == m_tilesCount) //m_tilesCount - hiddenvalue
    {
        moveTo = index - 4;
    }//down
    else if (index + 4 < m_tilesCount && //m_tilesCount - size
             m_gameField[index + 4] == m_tilesCount) //m_tilesCount - hiddenvalue
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

QHash<int, QByteArray> GameModel::roleNames() const
{
    QHash <int, QByteArray> roles;

    roles[roles::hiddenNumberValue] = "hiddenNumberValue";
    roles[Qt::DisplayRole] = "display";

    return roles;
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
    if (std::is_sorted(m_gameField.begin(), m_gameField.end())) {
        m_isGameOver = false;
        emit isGameOverChanged();

        return true;
    }
    return false;
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

QVariant GameModel::data (const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    switch (role) {
    case Qt::DisplayRole: {

        return QVariant::fromValue(m_gameField[index.row()]);
    }
    case roles::hiddenNumberValue: {
        return QVariant::fromValue(m_tilesCount);
    }
    default: {
        return {};
    }
    }

}
