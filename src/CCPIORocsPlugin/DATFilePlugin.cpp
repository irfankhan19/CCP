/*
    Rocs file plugin to handle DAT Files.
    Copyright (C) 2010  Wagner Reck <wagner.reck@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "DATFilePlugin.h"
#include "rocs/graphDocument.h"
#include "rocs/DataType.h"
#include <rocs/Data.h>
#include <KAboutData>
#include <QRectF>
#include <KGenericFactory>
#include <QFile>

static const KAboutData aboutdata("datfileplugin", 0, ki18n("Open and Save DAT files") , "0.1" );

K_PLUGIN_FACTORY( DATFilePLuginFactory, registerPlugin< Rocs::DATFilePlugin>(); )
K_EXPORT_PLUGIN( DATFilePLuginFactory(aboutdata) )


Rocs::DATFilePlugin::~DATFilePlugin()
{

}

Rocs::DATFilePlugin::DATFilePlugin(QObject* parent, const QList< QVariant >& ):
    FilePluginInterface(DATFilePLuginFactory::componentData(), parent)
{

}

const QStringList Rocs::DATFilePlugin::extensions() const
{
    return QStringList()
	<< i18n("*.dat|DAT Files") + '\n';
}


DataTypeDocument * Rocs::DATFilePlugin::readFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
	return 0;
    }

    int numPoints = 0;
    int count = 0;
    double capacity = 0.0;
    QString line;
    QStringList list;
    DataTypeDocument * graphDoc = new DataTypeDocument("Untitled");

    DataType * graph = graphDoc->addDataType(fileName);
    QTextStream input(&file);

    if (!input.atEnd()){
      line = input.readLine();
      list = line.split(' ', QString::SkipEmptyParts);
      if (list.size() != 2){
	  qDebug() << "Assertion Error. line 1 of file.";
	  delete graphDoc;
	  return 0;
      }
      numPoints = list[0].toUShort();
      graph->addDynamicProperty("NumCenters", list[1].toUShort());
//      inst->setName(name);
  }
//  pointsList = new  Point*[numPoints];

  while (!input.atEnd()){
      if (count >= numPoints){
	  break;
      }
      line = input.readLine();
      list = line.split (' ', QString::SkipEmptyParts);
      if (list.size() != 4){
	qDebug() << "Assertion error. Skiping line " << count+2;
	--count;
      }else {
	      Datum * n = graph->addDatum(QString::number(count));
	      n->addDynamicProperty("coordX", list[0].toDouble());
	      n->addDynamicProperty("coordY", list[1].toDouble());
	      n->addDynamicProperty("Demand", list[3].toDouble());
		//    pointsList[count] = new Point(inst, list[0].toDouble(), list[1].toDouble(), list[3].toDouble());
	if (capacity < list[2].toDouble())
	    capacity = list[2].toDouble();
      }
      ++count;
  }

    graph->addDynamicProperty("Capacity", capacity);


   QRectF outBox;
   outBox.setRect(graph->data()[0]->property("coordX").toDouble(), graph->data()[0]->property("coordY").toDouble(),
                 0.0,0.0);
  foreach(Datum * n, graph->data()){
      if (n->property("coordY").toDouble() < outBox.top()){
          outBox.setTop(n->property("coordY").toDouble());
      }
      if (n->property("coordY").toDouble() > outBox.bottom()){
          outBox.setBottom(n->property("coordY").toDouble());
      }
      if (n->property("coordX").toDouble() < outBox.left()){
          outBox.setLeft(n->property("coordX").toDouble());
      }
      if (n->property("coordX").toDouble() > outBox.right()){
          outBox.setRight(n->property("coordX").toDouble());
      }
  }
//  kDebug() << outBox.left() << outBox.top() << outBox.right() << outBox.bottom();
  qreal factorX = graphDoc->width()/(outBox.width());
  qreal factorY = graphDoc->height()/(outBox.height());
  qreal ratioX = 1.0;
  qreal ratioY = 1.0;
  if (outBox.height() > outBox.width()){
      ratioX = outBox.width() / outBox.height();
  }else {
      ratioY = outBox.height() / outBox.width();
  }
//  KDebug() << ratioX << ratioY;
//  kDebug() << factorX << factorY;

  foreach(Datum * n, graph->data()){
          n->setX((n->property("coordX").toDouble() - outBox.left()) * factorX * ratioX);
          n->setY((n->property("coordY").toDouble() - outBox.top()) * factorY * ratioY);
          n->setWidth(0.2);
  }

    return graphDoc;

}

bool Rocs::DATFilePlugin::writeFile(DataTypeDocument&/*graph*/ , const QString &filename) {
    QFile file (filename);
    if (file.open(QFile::WriteOnly))
    {
        return true;
    }
    return false;
}
