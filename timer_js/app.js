function getSec() {
    if (document.getElementById("secondi").value == "") {
        return 0;
    } else {
        return parseInt(document.getElementById("secondi").value);
    }
}

function getMin() {
    if (document.getElementById("minuti").value == "") {
        return 0;
    } else {
        return parseInt(document.getElementById("minuti").value);
    }
}

function getHou() {
    if (document.getElementById("ore").value == "") {
        return 0;
    } else {
        return parseInt(document.getElementById("ore").value);
    }
}

function startTimer() {
    console.log("partito");

    document.getElementById("bottone").disabled = true;

    var s = getSec() + getMin()*60 + getHou()*3600;
    
    var x = setInterval(function() {
        document.getElementById("timer").innerHTML = s;
        s--;

        if (s == -1) {
            document.getElementById("timer").innerHTML = "timer finito";
            clearInterval(x);
            document.getElementById("bottone").disabled = false;
        }
    }, 1000);
}

function restart() {
    location.reload();
}


