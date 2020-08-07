import QtQuick 2.0

ListModel {
    id:root
    property int count: 16
    property bool active: true
    signal win();
    signal restart();
    function onClicked(mouse) {
        shuffle();
    }
    //return 1 if swapped succesfully 0 if didnt swap
    function swap(id) {
        if(active === false) return 0
        //left
        if(id - 1 >= 0 && get(id - 1).display === "0" && id % 4 != 0) {
            move(id,id - 1,1);
            return 1;
        }//right
        else if(id + 1 <= count - 1 && get(id + 1).display === "0" && (id + 1) % 4 != 0) {
            move(id,id + 1,1);
            return 1;
        }//up
        else if(id - 4 >= 0 && get(id - 4).display === "0") {
            move(id,id-4,1);
            move(id-3,id - 2,1);
            move(id-2,id - 1,1);
            move(id-1,id,1);
            return 1;
        }//down
        else if(id + 4 <= count - 1 && get(id + 4).display === "0")  {
            move(id,id+4,1);
            move(id+3,id + 2,1);
            move(id+2,id + 1,1);
            move(id+1,id,1);
            return 1;
        }
        return 0;
    }
    function shuffle() {
        active = true;
        restart();
        var i=0;//i - succesfully swap counter
        while(i<500){
            i += swap(Math.floor(Math.random() * Math.floor(15)));
        } 
    }
    function isGameOver() {
        for(let i = 0; i < count - 2; i++) {
            if(get(i + 1).display - get(i).display !== 1) {
                return
            }
        }
        root.win();
        active = false;
    }
    ListElement{
        display: "1"
    }
    ListElement{
        display: "2"
    }
    ListElement{
        display: "3"
    }
    ListElement{
        display: "4"
    }
    ListElement{
        display: "5"
    }
    ListElement{
        display: "6"
    }
    ListElement{
        display: "7"
    }
    ListElement{
        display: "8"
    }
    ListElement{
        display: "9"
    }
    ListElement{
        display: "10"
    }
    ListElement{
        display: "11"
    }
    ListElement{
        display: "12"
    }
    ListElement{
        display: "13"
    }
    ListElement{
        display: "14"
    }
    ListElement{
        display: "0"
    }
    ListElement{
        display: "15"
    }
}
