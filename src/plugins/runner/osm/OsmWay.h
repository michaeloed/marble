//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2015      Dennis Nienhüser <nienhueser@kde.org>
//

#ifndef MARBLE_OSMWAY
#define MARBLE_OSMWAY

#include "OsmNode.h"
#include <osm/OsmPlacemarkData.h>
#include <StyleBuilder.h>
#include <GeoDataDocument.h>

#include <QSet>
#include <QString>

namespace Marble {

class GeoDataDocument;

class OsmWay
{
public:
    OsmPlacemarkData & osmData();
    void addReference(qint64 id);

    const OsmPlacemarkData & osmData() const;
    const QVector<qint64> &references() const;

    void create(GeoDataDocument* document, DocumentRole role, const OsmNodes &nodes, QSet<qint64> &usedNodes) const;

private:
    struct NamedEntry {
        GeoDataCoordinates coordinates;
        QString label;
        OsmPlacemarkData osmData;
    };

    bool isArea() const;

    static bool isAreaTag(const StyleBuilder::OsmTag &keyValue);

    static double extractBuildingHeight(const OsmPlacemarkData &osmData);
    static QVector<NamedEntry> extractNamedEntries(const OsmPlacemarkData &osmData);

    OsmPlacemarkData m_osmData;
    QVector<qint64> m_references;

    static QSet<StyleBuilder::OsmTag> s_areaTags;
};

typedef QHash<qint64,OsmWay> OsmWays;

}

#endif
