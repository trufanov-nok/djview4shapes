/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEMODEL_H
#define SHAPEMODEL_H

#include <QtCore>

class ShapeList;
class ShapeNode;

class ShapeModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit ShapeModel(ShapeList* shapes, QObject *parent = 0);

	// Functions subclassing QAbstractTableModel
	/** @return number of shapes in one row. This is based on number of columns. */
	int rowCount(const QModelIndex &parent) const;
	/** @return number of shapes in one column. This is set by user. */
	int columnCount(const QModelIndex &parent) const;
	/** @return data for given cell. */
	QVariant data(const QModelIndex &index, int role) const;

	/** Set number of columns. */
	void setColumnCount(int columns);
	/** @return a shape at given index or 0 if there is no such index. */
	ShapeNode* nodeAt(const QModelIndex& index) const;
private:
	int m_columns;
	ShapeList* m_shapes;
};

#endif // SHAPEMODEL_H
