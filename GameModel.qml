import QtQuick 2.0

ListModel {
    id:root

    readonly property int count: 16
    property bool gameIsActive: true

    signal gameIsOver

    function swap(id) { 
        if(gameIsActive === false) return;
        //left

        if(id - 1 >= 0 && get(id - 1).display === "0" && id % 4 != 0) {
            move(id,id - 1,1);
        }//right
        else if(id + 1 <= count - 1 && get(id + 1).display === "0" && (id + 1) % 4 != 0) {
            move(id,id + 1,1);
        }//up
        else if(id - 4 >= 0 && get(id - 4).display === "0") {
            move(id,id-4,1);
            move(id-3,id - 2,1);
            move(id-2,id - 1,1);
            move(id-1,id,1);
        }//down
        else if(id + 4 <= count - 1 && get(id + 4).display === "0")  {
            move(id,id+4,1);
            move(id+3,id + 2,1);
            move(id+2,id + 1,1);
            move(id+1,id,1);
        }
        isGameOver();
    }

    // https://e-maxx.ru/algo/15_puzzle
    function shuffle() {
        gameIsActive = true;
        root.clear();
        var Order;
        let inv = 1;
        var i  = 0;
        while(inv % 2 != 0){
            Order = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0].sort(function() { return Math.random()-.5; });
            inv = 0;
            for (i = 0; i<16; ++i)
                if (Order[i] !== 0)
                    for (let j=0; j<i; ++j)
                        if (Order[j] > Order[i])
                            ++inv;

            for (i = 0; i<16; ++i)
                if (Order[i] === 0)
                    inv += 1 + i / 4;
        }
        //appent or set?
        for(i = 0;i<16;i++){
            append({"display": String(Order[i])});
        }
    }

    function isGameOver() {
        for(let i = 0; i < count - 2; i++) {
            if(get(i + 1).display - get(i).display !== 1) {
                return;
            }
        }
        root.gameIsOver();
        gameIsActive = false;
    }
    //constructor or idk:)

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
