/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapeextractor.h"
#include "config.h"
#include <libdjvu/DjVuImage.h>
#include <libdjvu/DjVuDocument.h>
#include <libdjvu/JB2Image.h>
#include <libdjvu/ByteStream.h>
#include <libdjvu/GBitmap.h>
#include <libdjvu/ddjvuapi.h>
#include <libdjvu/miniexp.h>

namespace DJVU
{
struct ddjvu_page_s;
}

GP<DjVuImage> ddjvu_get_DjVuImage(DJVU::ddjvu_page_s *page);


ShapeExtractor::ShapeExtractor(QObject* parent) : QObject(parent)
{
	m_document = 0;
}

void ShapeExtractor::open(QDjVuDocument *document)
{
	m_document = document;
}

ShapeList ShapeExtractor::extract(int pageno, ShapeNode *root)
{
	ShapeList shapes;

	if (!m_document)
		return shapes;

	struct DJVU::ddjvu_page_s* page = reinterpret_cast<DJVU::ddjvu_page_s *>(
				ddjvu_page_create_by_pageno(*m_document, pageno));
	if (!page) {
		qWarning("Cound not render djvupage, page %d", pageno);
		return shapes;
	}

	GP<DjVuImage> img = ddjvu_get_DjVuImage(page);
	if (!img) {
		qWarning("Cound not render djvuimage, page %d", pageno);
		return shapes;
	}

	if (!img->wait_for_complete_decode())
		return shapes;

	GP<JB2Image> jimg = img->get_fgjb();
	if (!jimg) {
		qWarning("Cound not get fbjb, page %d", pageno);
		return shapes;
	}


	int shapesCount = jimg->get_shape_count();
	for (int i = 0; i < shapesCount; i++) {
		JB2Shape shape = jimg->get_shape(i);

		ShapeNode* parent = 0;
		if (shape.parent >= 0 && shape.parent < shapes.count())
			parent = shapes[shape.parent];
		else parent = root;

		GP<GBitmap> bits = shape.bits;
		if (!bits)
			continue;
		GP<ByteStream> bs = ByteStream::create();
		bits->save_pbm(*bs);
		TArray<char> array = bs->get_data();

		QPixmap pixmap;
		pixmap.loadFromData(reinterpret_cast<const uchar*>((char*)array), array.size());
		pixmap.setMask(pixmap.createMaskFromColor(Qt::white, Qt::MaskInColor)); //add transparency
		//boundingShapeSize = boundingShapeSize.expandedTo(node->getPixmap().size());
		shapes.append(new ShapeNode(parent, pixmap));
	}

	// now put blits
	int blitCount = jimg->get_blit_count();
	for (int i = 0; i < blitCount; i++) {
		JB2Blit *blit = jimg->get_blit(i);
		if (blit && int(blit->shapeno) < shapes.count())
			shapes[blit->shapeno]->addBlit(blit->left, blit->bottom);
	}

	qDebug("Grabed %d shapes for page %d", shapesCount, pageno);
	return shapes;
}




