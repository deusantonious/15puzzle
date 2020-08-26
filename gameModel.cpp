#include <algorithm>
#include "gameModel.h"

GameModel::GameModel(QObject *parent)
    :QAbstractListModel {parent}
{
   m_gameField.resize(tilesCount);
   std::iota(m_gameField.begin(), m_gameField.end(), 1);
   shuffleTiles();
}
