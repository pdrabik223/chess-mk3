import QtQuick
// import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    id: mainWindow
    width: 700
    height: 700
    title: "Chess mk3"


    Grid {
        id:square_matrix;
        // x:30
        // y:30
        rows: 8;
        columns: 8;
        anchors.fill: parent;
        // for (let i=0;i < 64;i++)
        // {
        //     Square {id : i; onClicked: grid.itemAt(i/8, i%8).squareColor = "yellow";squareColor:"red"}
        // }
    }



}
// ListModel {
//     id:chessBoard

// }
// Component {
//     class:square
//     width: 20
//     height:20


// }