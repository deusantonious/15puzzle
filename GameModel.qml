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
            move(id, id - 1, 1);
        }//right
        else if(id + 1 <= count - 1 && get(id + 1).display === "0" && (id + 1) % 4 != 0) {
            move(id, id + 1, 1);
        }//up
        else if(id - 4 >= 0 && get(id - 4).display === "0") {
            move(id, id - 4, 1);
            move(id - 3, id - 2, 1);
            move(id - 2, id - 1, 1);
            move(id - 1, id, 1);
        }//down
        else if(id + 4 <= count - 1 && get(id + 4).display === "0")  {
            move(id, id + 4, 1);
            move(id + 3, id + 2, 1);
            move(id + 2, id + 1, 1);
            move(id + 1, id, 1);
        }
        isGameOver();
    }

    // https://e-maxx.ru/algo/15_puzzle
    function shuffle() {
        let inv = 1;
        var i  = 0;
        var order;

        gameIsActive = true;
        root.clear();

        while(inv % 2 != 0){
            order = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0].sort(function() { return Math.random() -.5; });
            inv = 0;
            for (i = 0; i < 16; ++i)
                if (order[i] !== 0)
                    for (let j = 0; j < i; ++j)
                        if (order[j] > order[i])
                            ++inv;

            for (i = 0; i < 16; ++i)
                if (order[i] === 0)
                    inv += 1 + i / 4;
        }
        createModel(order);

    }
    function createModel(array){
        for(let i = 0; i < 16; i++){
            append({"display": String(array[i])});
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

    Component.onCompleted: createModel([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15])
}
