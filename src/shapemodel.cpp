/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapemodel.h"
#include "shape.h"

ShapeModel::ShapeModel(ShapeList* shapes, QObject *parent) :
	QAbstractTableModel(parent), m_shapes(shapes)
{
	m_columns = 20;
	m_highlightRoot = true;
}

int ShapeModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	else return (m_shapes->count() + m_columns - 1) / m_columns;
}

int ShapeModel::columnCount(const QModelIndex &parent) const
{
	return parent.isValid() ? 0 : m_columns;
}

QVariant ShapeModel::data(const QModelIndex &index, int role) const
{
	const int Padding = 4;

	ShapeNode* node = nodeAt(index);
	if (!node)
		return QVariant();

	int darker = 100;
	if (m_highlightRoot)
		darker += (node->depth() - 1) * 10;

	switch (role) {
	case Qt::DecorationRole:
		return node->scaledPixmap(QSize(30 - 2 * Padding, 30 - 2 * Padding));
	case Qt::ToolTipRole:
		return node->toolTip();
	case Qt::BackgroundRole:
		if (m_selectedItems.contains(node))
			return QColor(Qt::green).darker(darker);
		else if (m_highlightRoot && node->depth() > 1)
			return QColor(Qt::white).darker(darker);
		else return QVariant();
	default:
		break;
	}
	return QVariant();
}

QModelIndex ShapeModel::indexOf(ShapeNode *node) const
{
	int position = m_shapes->indexOf(node);
	if (position == -1)
		return QModelIndex();
	else return index(position / columnCount(), position % columnCount());
}

void ShapeModel::setHighlightRoot(bool enabled)
{
	if (m_highlightRoot != enabled) {
		beginResetModel();
		m_highlightRoot = enabled;
		endResetModel();
	}
}

void ShapeModel::setVisibleColumnCount(int columns)
{
	beginResetModel();
	m_columns = columns;
	endResetModel();
}

ShapeNode *ShapeModel::nodeAt(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;
	int i = index.row() * m_columns + index.column();
	if (i >= m_shapes->count())
		return 0;
	return m_shapes->at(i);
}

void ShapeModel::selectItems(const ShapeList &list)
{
	QSet<ShapeNode*> newshapes;
	for (int i = 0; i < list.count(); i++)
		newshapes.insert(list[i]);
	qSwap(newshapes, m_selectedItems);

	for (int row = 0; row < rowCount(); row++)
		for (int column = 0; column < columnCount(); column++) {
			QModelIndex i = index(row, column);
			ShapeNode* node = nodeAt(i);
			if (node && (newshapes.contains(node) != m_selectedItems.contains(node)))
				emit dataChanged(i, i);
		}
}

ShapeList ShapeModel::selectedItems() const
{
	ShapeList items;
	foreach (ShapeNode* node, m_selectedItems)
		items.append(node);
	return items;
}
