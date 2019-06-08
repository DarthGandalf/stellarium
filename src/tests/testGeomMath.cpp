/*
 * Stellarium 
 * Copyright (C) 2019 Alexander Wolf
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#include <QObject>
#include <QtDebug>
#include <QVariantList>
#include <QtTest>

#include "tests/testGeomMath.hpp"

QTEST_GUILESS_MAIN(TestGeomMath)

void TestGeomMath::initTestCase()
{
	data << 0.f << 1.f << 1.f;
	data << 0.f << 2.f << 8.f;
	data << 0.f << 5.f << 125.f;
	data << 0.f << 10.f << 1000.f;
}

void TestGeomMath::testAABBox()
{
	while(data.count() >= 3)
	{
		float minf = data.takeFirst().toFloat();
		float maxf = data.takeFirst().toFloat();
		float res = data.takeFirst().toFloat();

		Vec3f min = Vec3f(minf,minf,minf);
		Vec3f max = Vec3f(maxf,maxf,maxf);

		Vec3f minMinMax = Vec3f(minf,minf,maxf);
		Vec3f minMaxMin = Vec3f(minf,maxf,minf);
		Vec3f minMaxMax = Vec3f(minf,maxf,maxf);
		Vec3f maxMinMin = Vec3f(maxf,minf,minf);
		Vec3f maxMinMax = Vec3f(maxf,minf,maxf);
		Vec3f maxMaxMin = Vec3f(maxf,maxf,minf);

		Vec4f mFront = Vec4f(0.0f, -1.0f, 0.0f, -min.v[1]);
		Vec4f mBack = Vec4f(0.0f, 1.0f, 0.0f, max.v[1]);
		Vec4f mBottom = Vec4f(0.0f, 0.0f, -1.0f, -min.v[2]);
		Vec4f mTop = Vec4f(0.0f, 0.0f, 1.0f, max.v[2]);
		Vec4f mLeft = Vec4f(-1.0f, 0.0f, 0.0f, -min.v[0]);
		Vec4f mRight = Vec4f(1.0f, 0.0f, 0.0f, max.v[0]);

		AABBox* aabox = new AABBox(min, max);

		QVERIFY(aabox->isValid());
		QVERIFY(aabox->getVolume()==res);
		QVERIFY(aabox->getCorner(AABBox::MinMinMin)==min);
		QVERIFY(aabox->getCorner(AABBox::MinMinMax)==minMinMax);
		QVERIFY(aabox->getCorner(AABBox::MinMaxMin)==minMaxMin);
		QVERIFY(aabox->getCorner(AABBox::MinMaxMax)==minMaxMax);
		QVERIFY(aabox->getCorner(AABBox::MaxMinMin)==maxMinMin);
		QVERIFY(aabox->getCorner(AABBox::MaxMinMax)==maxMinMax);
		QVERIFY(aabox->getCorner(AABBox::MaxMaxMin)==maxMaxMin);
		QVERIFY(aabox->getCorner(AABBox::MaxMaxMax)==max);
		QVERIFY(aabox->getPlane(AABBox::Front)==mFront);
		QVERIFY(aabox->getPlane(AABBox::Back)==mBack);
		QVERIFY(aabox->getPlane(AABBox::Bottom)==mBottom);
		QVERIFY(aabox->getPlane(AABBox::Top)==mTop);
		QVERIFY(aabox->getPlane(AABBox::Left)==mLeft);
		QVERIFY(aabox->getPlane(AABBox::Right)==mRight);
		QVERIFY(aabox->positiveVertex(max)==max);
		QVERIFY(aabox->negativeVertex(max)==min);
	}
}
