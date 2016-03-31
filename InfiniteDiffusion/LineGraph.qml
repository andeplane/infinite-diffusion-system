import QtQuick 2.5
import QtCharts 2.0
import DataSource 1.0
import QtQuick.Controls 1.4
LineSeries {
    id: lineSeriesRoot
    property DataSource dataSource
    property Figure figure

    function updateData() {
        clear()
        if(dataSource === undefined) {
            return;
        }

        for(var i in dataSource.xValues) {
            var x = dataSource.xValues[i]
            var y = dataSource.yValues[i]
            append(x,y)
        }

        if(figure != undefined) {
            figure.updateLimits()
        }

        var t = dataSource.xValues[dataSource.xValues.length-1]
        var msd = dataSource.yValues[dataSource.yValues.length-1]
        console.log("New point: "+t+" "+msd)
        var D = msd / (6*t)
        if(figure != null) figure.labelText = "D = "+D.toFixed(5)
    }

    onFigureChanged: {
        if(figure === undefined) return;
        axisX = figure.axisX
        axisY = figure.axisY
        figure.lineGraphs.push(this)
    }

    onDataSourceChanged: {
        dataSource.updated.connect(updateData)
        updateData()
    }
}
